'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Shape = require("../Types/Shape.js");
var Manager = require("./Manager.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

var State = /* module */[];

function F(Board) {
  return (function (Gen) {
      var include = Manager.F(Board)(Gen);
      var CoordMap = include[0];
      var create_index_map = include[1];
      var get_adjacent = include[2];
      var all_walls = include[12];
      var create_enabled_map = function (coords) {
        return Belt_Array.reduce(coords, CoordMap[/* empty */0], (function (map, c) {
                      return Curry._3(CoordMap[/* add */3], c, /* false */0, map);
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
                var match = Curry._2(CoordMap[/* mem */2], coord, enabled);
                if (match !== 0) {
                  return Curry._3(CoordMap[/* add */3], coord, /* true */1, enabled);
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
        if (Curry._2(CoordMap[/* mem */2], coord, state[/* enabled */4])) {
          var state$1 = toggle_all(state, coord);
          var enabled = Curry._3(CoordMap[/* add */3], coord, /* true */1, state$1[/* enabled */4]);
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
                return Curry._2(CoordMap[/* find */21], coord, enabled);
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
                return Curry._2(CoordMap[/* find */21], coord, enabled);
              }));
        return Belt_Array.map(__x, (function (coord) {
                      var offset = Curry._3(Board[/* offset */6], shape, scale, coord);
                      var shape$1 = Curry._2(Board[/* tile_at_coord */8], shape, coord);
                      var match = Curry._2(CoordMap[/* find */21], coord, enabled);
                      return /* tuple */[
                              Shape.transform(offset, scale, shape$1),
                              match !== 0 ? 8 : 2
                            ];
                    }));
      };
      return /* module */[
              /* CoordMap */CoordMap,
              /* create_index_map */create_index_map,
              /* get_adjacent */get_adjacent,
              /* init */include[3],
              /* step */include[4],
              /* loop_to_end */include[5],
              /* finished */include[6],
              /* edges */include[7],
              /* max_age */include[8],
              /* current_age */include[9],
              /* all_edges */include[10],
              /* all_shapes */include[11],
              /* all_walls */all_walls,
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
/* Manager Not a pure module */
