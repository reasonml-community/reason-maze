'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Walls = require("../Walls.js");
var DrawShared = require("../Maze/DrawShared.js");

var Default = /* module */[/* batch */10];

function Draw(Config) {
  return (function (Board) {
      return (function (Generator) {
          return (function (DrawConfig) {
              var Draw = DrawShared.Draw(Board)(DrawConfig);
              var draw = function (ctx, bsize, csize) {
                var adjacency = Curry._1(Board[/* adjacency_list */1], bsize);
                var state = Curry._2(Generator[/* init */1], Curry._1(Board[/* Shape */0][/* vertex_count */3], bsize), adjacency);
                var loop = function (state) {
                  var walls = Walls.walls_remaining(adjacency, Curry._1(Generator[/* State */0][/* traveled */1], state));
                  Curry._7(Draw[/* draw */6], ctx, bsize, csize, walls, Curry._1(Generator[/* State */0][/* traveled */1], state), Curry._1(Generator[/* State */0][/* current */2], state), Curry._1(Generator[/* State */0][/* next */3], state));
                  if (Curry._1(Generator[/* State */0][/* finished */0], state)) {
                    return /* () */0;
                  } else {
                    var tmp = [state];
                    for(var _for = 0 ,_for_finish = Config[/* batch */0] - 1 | 0; _for <= _for_finish; ++_for){
                      tmp[0] = Curry._1(Generator[/* step */3], tmp[0]);
                    }
                    setTimeout((function () {
                            return loop(tmp[0]);
                          }), 100);
                    return /* () */0;
                  }
                };
                return loop(state);
              };
              return /* module */[
                      /* Draw */Draw,
                      /* draw */draw
                    ];
            });
        });
    });
}

exports.Default = Default;
exports.Draw = Draw;
/* Walls Not a pure module */
