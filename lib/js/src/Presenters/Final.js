'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Walls = require("../Walls.js");
var DrawShared = require("../Maze/DrawShared.js");

function Draw(Board) {
  return (function (Generator) {
      return (function (DrawConfig) {
          var Draw = DrawShared.Draw(Board)(DrawConfig);
          var draw = function (ctx, bsize, csize) {
            var full = Curry._1(Board[/* adjacency_list */1], bsize);
            var traveled = Curry._2(Generator[/* spanning_tree */4], Curry._1(Board[/* Shape */0][/* vertex_count */3], bsize), full);
            var walls = Walls.walls_remaining(full, traveled);
            return Curry._7(Draw[/* draw */6], ctx, bsize, csize, walls, traveled, /* [] */0, /* [] */0);
          };
          return /* module */[
                  /* Draw */Draw,
                  /* draw */draw
                ];
        });
    });
}

exports.Draw = Draw;
/* Walls Not a pure module */
