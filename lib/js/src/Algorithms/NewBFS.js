'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("../Maze/Utils.js");
var Random = require("bs-platform/lib/js/random.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Generator = require("../Types/Generator.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

function init(size) {
  return /* record */[
          /* visited */Belt_Array.make(size, 0),
          /* edges */Generator.PairSet[/* empty */0],
          /* frontier : :: */[
            Random.$$int(size),
            /* [] */0
          ],
          /* next : [] */0,
          /* step */0
        ];
}

function edges(state) {
  return state[/* edges */1];
}

function visited(state) {
  return state[/* visited */0];
}

function max_age(state) {
  return state[/* step */4];
}

function sortpair(a, b) {
  var match = Caml_obj.caml_greaterthan(a, b);
  if (match !== 0) {
    return /* tuple */[
            b,
            a
          ];
  } else {
    return /* tuple */[
            a,
            b
          ];
  }
}

function add_edges(adjacents, state, src) {
  return Belt_List.reduce(adjacents, /* tuple */[
              state[/* next */3],
              state[/* edges */1],
              state[/* step */4]
            ], (function (param, dest) {
                var step = param[2];
                var edges = param[1];
                var next = param[0];
                if (Belt_Array.getExn(state[/* visited */0], dest) > 0) {
                  return /* tuple */[
                          next,
                          edges,
                          step
                        ];
                } else {
                  Belt_Array.set(state[/* visited */0], dest, step + 1 | 0);
                  return /* tuple */[
                          /* :: */[
                            dest,
                            next
                          ],
                          Curry._2(Generator.PairSet[/* add */3], sortpair(src, dest), edges),
                          step + 1 | 0
                        ];
                }
              }));
}

function step(get_adjacent, state) {
  var match = state[/* frontier */2];
  if (match) {
    var rest = match[1];
    var src = match[0];
    if (rest) {
      var match$1 = add_edges(Curry._1(get_adjacent, src), state, src);
      return /* record */[
              /* visited */state[/* visited */0],
              /* edges */match$1[1],
              /* frontier */rest,
              /* next */match$1[0],
              /* step */match$1[2]
            ];
    } else {
      var match$2 = add_edges(Curry._1(get_adjacent, src), state, src);
      return /* record */[
              /* visited */state[/* visited */0],
              /* edges */match$2[1],
              /* frontier */Utils.shuffle(match$2[0]),
              /* next : [] */0,
              /* step */match$2[2]
            ];
    }
  } else {
    return state;
  }
}

function finished(state) {
  return +(state[/* frontier */2] === /* [] */0);
}

function loop_to_end(get_adjacent, _state) {
  while(true) {
    var state = _state;
    if (state[/* frontier */2] !== /* [] */0) {
      _state = step(get_adjacent, state);
      continue ;
      
    } else {
      return state;
    }
  };
}

function run(size, get_adjacent) {
  return loop_to_end(get_adjacent, init(size));
}

exports.init = init;
exports.edges = edges;
exports.visited = visited;
exports.max_age = max_age;
exports.sortpair = sortpair;
exports.add_edges = add_edges;
exports.step = step;
exports.finished = finished;
exports.loop_to_end = loop_to_end;
exports.run = run;
/* Generator Not a pure module */
