'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Shape = require("../Types/Shape.js");
var Belt_Id = require("bs-platform/lib/js/belt_Id.js");
var Manager = require("./Manager.js");
var Belt_Map = require("bs-platform/lib/js/belt_Map.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

var State = /* module */[];

function F(Board) {
  return (function (Gen) {
      var include = Manager.F(Board)(Gen);
      var create_index_map = include[2];
      var get_adjacent = include[3];
      var all_walls = include[13];
      var cmp = Board[/* Coord */0][/* compare */1];
      var BoardCoordComparator2 = Belt_Id.MakeComparable(/* module */[/* cmp */cmp]);
      var boardCoord2 = Belt_Map.make(BoardCoordComparator2);
      var create_enabled_map = function (coords) {
        return Belt_Array.reduce(coords, boardCoord2, (function (map, c) {
                      return Belt_Map.set(map, c, /* false */0);
                    }));
      };
      var paint_init = function (param, hint_size) {
        var match = Curry._2(Board[/* auto_size */5], /* tuple */[
              param[0],
              param[1]
            ], hint_size);
        var shape = match[0];
        var coords = Belt_List.toArray(Curry._1(Board[/* coordinates */4], shape));
        var enabled = create_enabled_map(coords);
        return /* record */[
                /* shape */shape,
                /* scale */match[1],
                /* outsize */match[2],
                /* coords */coords,
                /* enabled */enabled
              ];
      };
      var toggle_all = function (state, coord) {
        var __x = Curry._2(Board[/* adjacents */1], state[/* shape */0], coord);
        var __x$1 = Belt_List.map(__x, Curry._2(Board[/* adjacent_coord */2], state[/* shape */0], coord));
        var enabled = Belt_List.reduce(__x$1, state[/* enabled */4], (function (enabled, coord) {
                var match = Belt_Map.has(enabled, coord);
                if (match !== 0) {
                  return Belt_Map.set(enabled, coord, /* true */1);
                } else {
                  return enabled;
                }
              }));
        return /* record */[
                /* shape */state[/* shape */0],
                /* scale */state[/* scale */1],
                /* outsize */state[/* outsize */2],
                /* coords */state[/* coords */3],
                /* enabled */enabled
              ];
      };
      var toggle_point = function (state, param) {
        var coord = Curry._3(Board[/* from_point */9], state[/* shape */0], state[/* scale */1], /* tuple */[
              param[0],
              param[1]
            ]);
        if (Belt_Map.has(state[/* enabled */4], coord)) {
          var state$1 = toggle_all(state, coord);
          var enabled = Belt_Map.set(state$1[/* enabled */4], coord, /* true */1);
          return /* record */[
                  /* shape */state$1[/* shape */0],
                  /* scale */state$1[/* scale */1],
                  /* outsize */state$1[/* outsize */2],
                  /* coords */state$1[/* coords */3],
                  /* enabled */enabled
                ];
        } else {
          return state;
        }
      };
      var realize_state = function (param) {
        var enabled = param[/* enabled */4];
        var shape = param[/* shape */0];
        var coords = Belt_Array.keep(param[/* coords */3], (function (coord) {
                return Belt_Map.getExn(enabled, coord);
              }));
        if (coords.length !== 0) {
          var coord_map = Curry._1(create_index_map, coords);
          var count = coords.length;
          var gen_state = Curry._1(Gen[/* init */4], count);
          var get_adjacent$1 = Curry._3(get_adjacent, shape, coords, coord_map);
          return /* Some */[/* record */[
                    /* count */count,
                    /* shape */shape,
                    /* scale */param[/* scale */1],
                    /* outsize */param[/* outsize */2],
                    /* gen_state */gen_state,
                    /* get_adjacent */get_adjacent$1,
                    /* coords */coords,
                    /* coord_map */coord_map
                  ]];
        } else {
          return /* None */0;
        }
      };
      var paint_walls = function (state) {
        var match = realize_state(state);
        if (match) {
          return Curry._1(all_walls, match[0]);
        } else {
          return /* [] */0;
        }
      };
      var paint_shapes = function (param) {
        var enabled = param[/* enabled */4];
        var scale = param[/* scale */1];
        var shape = param[/* shape */0];
        var __x = Belt_Array.keep(param[/* coords */3], (function (coord) {
                return Belt_Map.getExn(enabled, coord);
              }));
        return Belt_Array.map(__x, (function (coord) {
                      var offset = Curry._3(Board[/* offset */6], shape, scale, coord);
                      var shape$1 = Curry._2(Board[/* tile_at_coord */8], shape, coord);
                      var match = Belt_Map.getExn(enabled, coord);
                      return /* tuple */[
                              Shape.transform(offset, scale, shape$1),
                              match !== 0 ? 8 : 2
                            ];
                    }));
      };
      return /* module */[
              /* BoardCoordComparator */include[0],
              /* boardCoord */include[1],
              /* create_index_map */create_index_map,
              /* get_adjacent */get_adjacent,
              /* init */include[4],
              /* step */include[5],
              /* loop_to_end */include[6],
              /* finished */include[7],
              /* edges */include[8],
              /* max_age */include[9],
              /* current_age */include[10],
              /* all_edges */include[11],
              /* all_shapes */include[12],
              /* all_walls */all_walls,
              /* BoardCoordComparator2 */BoardCoordComparator2,
              /* boardCoord2 */boardCoord2,
              /* create_enabled_map */create_enabled_map,
              /* paint_init */paint_init,
              /* toggle_all */toggle_all,
              /* toggle_point */toggle_point,
              /* realize_state */realize_state,
              /* paint_walls */paint_walls,
              /* paint_shapes */paint_shapes
            ];
    });
}

exports.State = State;
exports.F = F;
/* Shape Not a pure module */
