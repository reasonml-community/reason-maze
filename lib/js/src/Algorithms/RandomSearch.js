'use strict';

var Utils = require("../Maze/Utils.js");
var Random = require("bs-platform/lib/js/random.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function traveled(t) {
  return t[/* traveled */4];
}

function current(t) {
  return Belt_List.map(t[/* current */2], (function (param) {
                return param[/* dest */1];
              }));
}

function next() {
  return /* [] */0;
}

function age(t) {
  return t[/* age */3];
}

function finished(t) {
  return +(t[/* current */2] === /* [] */0);
}

var State = /* module */[
  /* traveled */traveled,
  /* current */current,
  /* next */next,
  /* age */age,
  /* finished */finished
];

function adjacent_edges(visited, src, adjacents) {
  return Belt_List.reduce(adjacents, /* [] */0, (function (arr, dest) {
                if (Belt_Array.getExn(visited, dest)) {
                  return arr;
                } else {
                  return /* :: */[
                          /* record */[
                            /* src */src,
                            /* dest */dest,
                            /* age */0
                          ],
                          arr
                        ];
                }
              }));
}

function step(state) {
  var current = state[/* current */2];
  if (current) {
    var rest = current[1];
    var src = current[0];
    var visited = state[/* visited */1];
    if (Belt_Array.getExn(visited, src[/* dest */1])) {
      return /* record */[
              /* adjacency_list */state[/* adjacency_list */0],
              /* visited */state[/* visited */1],
              /* current */rest,
              /* age */state[/* age */3],
              /* traveled */state[/* traveled */4]
            ];
    } else {
      var adjacents = Belt_Array.getExn(state[/* adjacency_list */0], src[/* dest */1]);
      Belt_Array.set(visited, src[/* dest */1], /* true */1);
      var age = state[/* age */3] + 1 | 0;
      var traveled_000 = /* record */[
        /* src */src[/* src */0],
        /* dest */src[/* dest */1],
        /* age */age
      ];
      var traveled_001 = state[/* traveled */4];
      var traveled = /* :: */[
        traveled_000,
        traveled_001
      ];
      var next = Pervasives.$at(rest, adjacent_edges(visited, src[/* dest */1], adjacents));
      return /* record */[
              /* adjacency_list */state[/* adjacency_list */0],
              /* visited */state[/* visited */1],
              /* current */Utils.shuffle(next),
              /* age */age,
              /* traveled */traveled
            ];
    }
  } else {
    return state;
  }
}

function loop(_state) {
  while(true) {
    var state = _state;
    var state$1 = step(state);
    if (state$1[/* current */2]) {
      _state = state$1;
      continue ;
      
    } else {
      return state$1[/* traveled */4];
    }
  };
}

function init(vertices, adjacency_list) {
  var visited = Belt_Array.make(vertices, /* false */0);
  var initial = Random.$$int(vertices);
  return /* record */[
          /* adjacency_list */adjacency_list,
          /* visited */visited,
          /* current : :: */[
            /* record */[
              /* src */initial,
              /* dest */initial,
              /* age */0
            ],
            /* [] */0
          ],
          /* age */0,
          /* traveled : [] */0
        ];
}

function spanning_tree(vertices, adjacency_list) {
  return loop(init(vertices, adjacency_list));
}

exports.State = State;
exports.adjacent_edges = adjacent_edges;
exports.step = step;
exports.loop = loop;
exports.init = init;
exports.spanning_tree = spanning_tree;
/* Utils Not a pure module */
