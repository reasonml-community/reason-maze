'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var DrawShared = require("../Maze/DrawShared.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function all_walls(full) {
  return Belt_Array.reduce(full, /* tuple */[
                0,
                /* [] */0
              ], (function (param, item) {
                  var i = param[0];
                  return /* tuple */[
                          i + 1 | 0,
                          Pervasives.$at(Belt_List.map(item, (function (d) {
                                      return /* tuple */[
                                              i,
                                              d
                                            ];
                                    })), param[1])
                        ];
                }))[1];
}

function range(i, n) {
  var _n = n - 1 | 0;
  var _acc = /* [] */0;
  while(true) {
    var acc = _acc;
    var n$1 = _n;
    if (n$1 < i) {
      return acc;
    } else {
      _acc = /* :: */[
        n$1,
        acc
      ];
      _n = n$1 - 1 | 0;
      continue ;
      
    }
  };
}

function Draw(Board) {
  return (function (Generator) {
      return (function (DrawConfig) {
          var Draw = DrawShared.Draw(Board)(DrawConfig);
          var walls = function (ctx, bsize, csize) {
            var full = Curry._1(Board[/* adjacency_list */1], bsize);
            return Curry._4(Draw[/* draw_walls */1], ctx, bsize, csize, all_walls(full));
          };
          var dots = function (ctx, bsize, csize) {
            var vertices = Curry._1(Board[/* Shape */0][/* vertex_count */3], bsize);
            return Curry._5(Draw[/* vertex_dots */2], ctx, bsize, csize, range(0, vertices), 10.0);
          };
          var paths = function (ctx, bsize, csize) {
            var full = Curry._1(Board[/* adjacency_list */1], bsize);
            var traveled = Curry._2(Generator[/* spanning_tree */4], Curry._1(Board[/* Shape */0][/* vertex_count */3], bsize), full);
            ctx.strokeStyle = "rgba(100, 100, 100, 0.1)";
            return Curry._4(Draw[/* paths */4], ctx, bsize, csize, traveled);
          };
          var connections = function (ctx, bsize, csize) {
            var full = Curry._1(Board[/* adjacency_list */1], bsize);
            console.log(Belt_Array.map(full, Belt_List.toArray));
            ctx.strokeStyle = "rgba(100, 100, 100, 0.1)";
            return Curry._4(Draw[/* connections */5], ctx, bsize, csize, all_walls(full));
          };
          return /* module */[
                  /* Draw */Draw,
                  /* walls */walls,
                  /* dots */dots,
                  /* paths */paths,
                  /* connections */connections
                ];
        });
    });
}

exports.all_walls = all_walls;
exports.range = range;
exports.Draw = Draw;
/* DrawShared Not a pure module */
