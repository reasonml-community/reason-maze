'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");

var Edge = /* module */[];

function optmap(fn, lst) {
  return List.fold_left((function (res, v) {
                var match = Curry._1(fn, v);
                if (match) {
                  return /* :: */[
                          match[0],
                          res
                        ];
                } else {
                  return res;
                }
              }), /* [] */0, lst);
}

function transform_wall(wall, scale, param) {
  var match = wall[0];
  var match$1 = match[1];
  var match$2 = match[0];
  var dy = param[1];
  var dx = param[0];
  return /* Line */[/* tuple */[
            /* tuple */[
              Utils.Float[/* + */0](Utils.Float[/* * */3](match$2[0], scale), dx),
              Utils.Float[/* + */0](Utils.Float[/* * */3](match$2[1], scale), dy)
            ],
            /* tuple */[
              Utils.Float[/* + */0](Utils.Float[/* * */3](match$1[0], scale), dx),
              Utils.Float[/* + */0](Utils.Float[/* * */3](match$1[1], scale), dy)
            ]
          ]];
}

function Board(Shape) {
  var border_walls = function (shape, size) {
    return List.map((function (param) {
                  var match = param[0];
                  var wall = Curry._1(Shape[/* Tile */0][/* wall_in_direction */1], param[1]);
                  var scale = Curry._2(Shape[/* scale */6], shape, size);
                  var offset = Curry._3(Shape[/* coord_to_board */5], shape, size, /* tuple */[
                        match[0],
                        match[1]
                      ]);
                  return transform_wall(wall, scale, offset);
                }), Curry._1(Shape[/* border_walls */7], shape));
  };
  var adjacency_list = function (shape) {
    var res = Caml_array.caml_make_vect(Curry._1(Shape[/* vertex_count */3], shape), /* [] */0);
    $$Array.iteri((function (i, param) {
            var y = param[1];
            var x = param[0];
            return Caml_array.caml_array_set(res, i, optmap((function (param) {
                              return Curry._2(Shape[/* to_vertex */1], shape, /* tuple */[
                                          x + param[0] | 0,
                                          y + param[1] | 0
                                        ]);
                            }), Curry._1(Shape[/* Tile */0][/* adjacent */2], /* tuple */[
                                x,
                                y
                              ])));
          }), Curry._1(Shape[/* all_coordinates */4], shape));
    return res;
  };
  var $pipe$unknown$less = function (a, b) {
    if (b) {
      return /* Some */[Curry._1(a, b[0])];
    } else {
      return /* None */0;
    }
  };
  var vertex_pos = function (v, shape, size) {
    return Curry._3(Shape[/* coord_to_board */5], shape, size, Curry._2(Shape[/* from_vertex */2], shape, v));
  };
  var drawable_wall = function (param, shape, size) {
    var match = Curry._2(Shape[/* from_vertex */2], shape, param[0]);
    var y = match[1];
    var x = match[0];
    var match$1 = Curry._2(Shape[/* from_vertex */2], shape, param[1]);
    var match$2 = Curry._1(Shape[/* Tile */0][/* to_direction */0], /* tuple */[
          match$1[0] - x | 0,
          match$1[1] - y | 0
        ]);
    if (match$2) {
      var wall = Curry._1(Shape[/* Tile */0][/* wall_in_direction */1], match$2[0]);
      var scale = Curry._2(Shape[/* scale */6], shape, size);
      var offset = Curry._3(Shape[/* coord_to_board */5], shape, size, /* tuple */[
            x,
            y
          ]);
      return /* Some */[transform_wall(wall, scale, offset)];
    } else {
      return /* None */0;
    }
  };
  return /* module */[
          /* Shape */Shape,
          /* border_walls */border_walls,
          /* adjacency_list */adjacency_list,
          /* |?< */$pipe$unknown$less,
          /* vertex_pos */vertex_pos,
          /* drawable_wall */drawable_wall
        ];
}

exports.Edge = Edge;
exports.optmap = optmap;
exports.transform_wall = transform_wall;
exports.Board = Board;
/* No side effect */
