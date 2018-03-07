'use strict';

var Utils = require("./Maze/Utils.js");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function get_walls(full, clear) {
  return Belt_Array.reduce(full, /* tuple */[
                0,
                /* [] */0
              ], (function (param, ends) {
                  var src = param[0];
                  return /* tuple */[
                          src + 1 | 0,
                          Pervasives.$at(Belt_List.reduce(ends, /* [] */0, (function (walls, vend) {
                                      var match = +(vend < src);
                                      if (match !== 0) {
                                        return walls;
                                      } else {
                                        var match$1 = Belt_Set.has(clear, /* tuple */[
                                              src,
                                              vend
                                            ]);
                                        if (match$1 !== 0) {
                                          return walls;
                                        } else {
                                          return /* :: */[
                                                  /* tuple */[
                                                    src,
                                                    vend
                                                  ],
                                                  walls
                                                ];
                                        }
                                      }
                                    })), param[1])
                        ];
                }))[1];
}

function wall_set(traveled) {
  var __x = Belt_List.toArray(traveled);
  return (function (param) {
              return Belt_Set.fromArray(param, Utils.IntPairComparator);
            })(Belt_Array.map(__x, (function (param) {
                    var dest = param[/* dest */1];
                    var src = param[/* src */0];
                    var match = +(src > dest);
                    if (match !== 0) {
                      return /* tuple */[
                              dest,
                              src
                            ];
                    } else {
                      return /* tuple */[
                              src,
                              dest
                            ];
                    }
                  })));
}

function walls_remaining(full, traveled) {
  var clear = wall_set(traveled);
  return get_walls(full, clear);
}

exports.get_walls = get_walls;
exports.wall_set = wall_set;
exports.walls_remaining = walls_remaining;
/* Utils Not a pure module */
