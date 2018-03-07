'use strict';

var $$Set = require("bs-platform/lib/js/set.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function compare(param, param$1) {
  var v = Caml_obj.caml_compare(param[0], param$1[0]);
  if (v !== 0) {
    return v;
  } else {
    return Caml_obj.caml_compare(param[1], param$1[1]);
  }
}

var Wall = /* module */[/* compare */compare];

var WallSet = $$Set.Make(Wall);

function get_walls(full, clear) {
  return $$Array.fold_left((function (param, ends) {
                  var src = param[0];
                  return /* tuple */[
                          src + 1 | 0,
                          Pervasives.$at(List.fold_left((function (walls, vend) {
                                      var match = +(vend < src);
                                      if (match !== 0) {
                                        return walls;
                                      } else {
                                        var match$1 = Curry._2(WallSet[/* mem */2], /* tuple */[
                                              src,
                                              vend
                                            ], clear);
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
                                    }), /* [] */0, ends), param[1])
                        ];
                }), /* tuple */[
                0,
                /* [] */0
              ], full)[1];
}

function wall_set(traveled) {
  return Curry._1(WallSet[/* of_list */25], List.map((function (param) {
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
                  }), traveled));
}

function walls_remaining(full, traveled) {
  var clear = wall_set(traveled);
  return get_walls(full, clear);
}

exports.Wall = Wall;
exports.WallSet = WallSet;
exports.get_walls = get_walls;
exports.wall_set = wall_set;
exports.walls_remaining = walls_remaining;
/* WallSet Not a pure module */
