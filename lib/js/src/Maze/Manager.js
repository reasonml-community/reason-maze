'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Shape = require("../Types/Shape.js");
var Border = require("../Types/Border.js");
var Belt_Id = require("bs-platform/lib/js/belt_Id.js");
var Belt_Map = require("bs-platform/lib/js/belt_Map.js");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

var State = /* module */[];

function F(Board) {
  return (function (Gen) {
      var cmp = Board[/* Coord */0][/* compare */1];
      var BoardCoordComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp]);
      var boardCoord = Belt_Map.make(BoardCoordComparator);
      var create_index_map = function (coords) {
        return Belt_Array.reduce(coords, /* tuple */[
                      0,
                      boardCoord
                    ], (function (param, c) {
                        var i = param[0];
                        return /* tuple */[
                                i + 1 | 0,
                                Belt_Map.set(param[1], c, i)
                              ];
                      }))[1];
      };
      var get_adjacent = function (shape, clist, cmap, i) {
        var coord = Belt_Array.getExn(clist, i);
        var __x = Curry._2(Board[/* adjacents */1], shape, coord);
        var __x$1 = Belt_List.map(__x, Curry._2(Board[/* adjacent_coord */2], shape, coord));
        return Belt_List.reduce(__x$1, /* [] */0, (function (adjacents, coord) {
                      var match = Belt_Map.has(cmap, coord);
                      if (match !== 0) {
                        return /* :: */[
                                Belt_Map.getExn(cmap, coord),
                                adjacents
                              ];
                      } else {
                        return adjacents;
                      }
                    }));
      };
      var init = function (param, hint_size) {
        var match = Curry._2(Board[/* auto_size */5], /* tuple */[
              param[0],
              param[1]
            ], hint_size);
        var shape = match[0];
        var coords = Belt_List.toArray(Curry._1(Board[/* coordinates */4], shape));
        var coord_map = create_index_map(coords);
        var count = coords.length;
        var gen_state = Curry._1(Gen[/* init */4], count);
        var get_adjacent$1 = function (param) {
          return get_adjacent(shape, coords, coord_map, param);
        };
        return /* record */[
                /* count */count,
                /* shape */shape,
                /* scale */match[1],
                /* outsize */match[2],
                /* gen_state */gen_state,
                /* get_adjacent */get_adjacent$1,
                /* coords */coords,
                /* coord_map */coord_map
              ];
      };
      var step = function (state) {
        var newrecord = state.slice();
        newrecord[/* gen_state */4] = Curry._2(Gen[/* step */5], state[/* get_adjacent */5], state[/* gen_state */4]);
        return newrecord;
      };
      var loop_to_end = function (state) {
        var newrecord = state.slice();
        newrecord[/* gen_state */4] = Curry._2(Gen[/* loop_to_end */6], state[/* get_adjacent */5], state[/* gen_state */4]);
        return newrecord;
      };
      var finished = function (param) {
        return Curry._1(Gen[/* finished */7], param[/* gen_state */4]);
      };
      var edges = function (param) {
        return Curry._1(Gen[/* edges */0], param[/* gen_state */4]);
      };
      var max_age = function (param) {
        return param[/* count */0];
      };
      var current_age = function (param) {
        return Curry._1(Gen[/* max_age */2], param[/* gen_state */4]);
      };
      var all_edges = function (param) {
        var coords = param[/* coords */6];
        var scale = param[/* scale */2];
        var shape = param[/* shape */1];
        var to_points = function (param) {
          return /* tuple */[
                  Curry._3(Board[/* tile_center */7], shape, scale, Belt_Array.getExn(coords, param[0])),
                  Curry._3(Board[/* tile_center */7], shape, scale, Belt_Array.getExn(coords, param[1]))
                ];
        };
        return Belt_Set.reduce(Curry._1(Gen[/* edges */0], param[/* gen_state */4]), /* [] */0, (function (coll, pair) {
                      return /* :: */[
                              to_points(pair),
                              coll
                            ];
                    }));
      };
      var all_shapes = function (param) {
        var gen_state = param[/* gen_state */4];
        var scale = param[/* scale */2];
        var shape = param[/* shape */1];
        return Belt_Array.mapWithIndex(param[/* coords */6], (function (i, coord) {
                      var offset = Curry._3(Board[/* offset */6], shape, scale, coord);
                      var shape$1 = Curry._2(Board[/* tile_at_coord */8], shape, coord);
                      var visited = Belt_Array.getExn(Curry._1(Gen[/* visited */1], gen_state), i);
                      return /* tuple */[
                              Shape.transform(offset, scale, shape$1),
                              visited
                            ];
                    }));
      };
      var all_walls = function (param) {
        var coord_map = param[/* coord_map */7];
        var coords = param[/* coords */6];
        var scale = param[/* scale */2];
        var shape = param[/* shape */1];
        var edges = Curry._1(Gen[/* edges */0], param[/* gen_state */4]);
        return Belt_Array.reduce(coords, /* tuple */[
                      0,
                      /* [] */0
                    ], (function (param, _) {
                        var i = param[0];
                        var coord = Belt_Array.getExn(coords, i);
                        var __x = Belt_List.keep(Curry._2(Board[/* adjacents */1], shape, coord), (function (d) {
                                var next = Curry._3(Board[/* adjacent_coord */2], shape, coord, d);
                                if (Belt_Map.has(coord_map, next)) {
                                  var nexti = Belt_Map.getExn(coord_map, next);
                                  if (nexti < i) {
                                    return /* false */0;
                                  } else {
                                    return 1 - Belt_Set.has(edges, /* tuple */[
                                                i,
                                                nexti
                                              ]);
                                  }
                                } else {
                                  return /* true */1;
                                }
                              }));
                        var borders = Belt_List.map(__x, (function (direction) {
                                return Border.transform(scale, Curry._3(Board[/* offset */6], shape, scale, coord), Curry._3(Board[/* direction_to_border */3], shape, coord, direction));
                              }));
                        return /* tuple */[
                                i + 1 | 0,
                                Pervasives.$at(borders, param[1])
                              ];
                      }))[1];
      };
      return /* module */[
              /* BoardCoordComparator */BoardCoordComparator,
              /* boardCoord */boardCoord,
              /* create_index_map */create_index_map,
              /* get_adjacent */get_adjacent,
              /* init */init,
              /* step */step,
              /* loop_to_end */loop_to_end,
              /* finished */finished,
              /* edges */edges,
              /* max_age */max_age,
              /* current_age */current_age,
              /* all_edges */all_edges,
              /* all_shapes */all_shapes,
              /* all_walls */all_walls
            ];
    });
}

exports.State = State;
exports.F = F;
/* Shape Not a pure module */
