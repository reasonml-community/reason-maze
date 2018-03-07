'use strict';

var Utils = require("../Maze/Utils.js");
var Random = require("bs-platform/lib/js/random.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function traveled(t) {
  return t[/* traveled */5];
}

function current(t) {
  return t[/* current */2];
}

function next(t) {
  return t[/* next */3];
}

function age(t) {
  return t[/* age */4];
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

function add_adjacent_edges(state, _adjacents, _next, _traveled, _age) {
  while(true) {
    var age = _age;
    var traveled = _traveled;
    var next = _next;
    var adjacents = _adjacents;
    if (adjacents) {
      var rest = adjacents[1];
      var dest = adjacents[0];
      var visited = state[0];
      if (Belt_Array.getExn(visited, dest)) {
        _adjacents = rest;
        continue ;
        
      } else {
        Belt_Array.set(visited, dest, /* true */1);
        _age = age + 1 | 0;
        _traveled = /* :: */[
          /* record */[
            /* src */state[1],
            /* dest */dest,
            /* age */age
          ],
          traveled
        ];
        _next = /* :: */[
          dest,
          next
        ];
        _adjacents = rest;
        continue ;
        
      }
    } else {
      return /* tuple */[
              next,
              traveled,
              age
            ];
    }
  };
}

function step(state) {
  var current = state[/* current */2];
  if (current) {
    var rest = current[1];
    var src = current[0];
    var traveled = state[/* traveled */5];
    var age = state[/* age */4];
    var next = state[/* next */3];
    var visited = state[/* visited */1];
    var adjacency_list = state[/* adjacency_list */0];
    if (rest) {
      var adjacents = Belt_Array.getExn(adjacency_list, src);
      var match = add_adjacent_edges(/* tuple */[
            visited,
            src
          ], adjacents, next, traveled, age);
      return /* record */[
              /* adjacency_list */state[/* adjacency_list */0],
              /* visited */state[/* visited */1],
              /* current */Utils.shuffle(Pervasives.$at(rest, match[0])),
              /* next */state[/* next */3],
              /* age */match[2],
              /* traveled */match[1]
            ];
    } else {
      var adjacents$1 = Belt_Array.getExn(adjacency_list, src);
      var match$1 = add_adjacent_edges(/* tuple */[
            visited,
            src
          ], adjacents$1, next, traveled, age);
      return /* record */[
              /* adjacency_list */state[/* adjacency_list */0],
              /* visited */state[/* visited */1],
              /* current */Utils.shuffle(match$1[0]),
              /* next : [] */0,
              /* age */match$1[2],
              /* traveled */match$1[1]
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
      return state$1[/* traveled */5];
    }
  };
}

function init(vertices, adjacency_list) {
  var visited = Belt_Array.make(vertices, /* false */0);
  var initial = Random.$$int(vertices);
  Belt_Array.set(visited, initial, /* true */1);
  return /* record */[
          /* adjacency_list */adjacency_list,
          /* visited */visited,
          /* current : :: */[
            initial,
            /* [] */0
          ],
          /* next : [] */0,
          /* age */0,
          /* traveled : [] */0
        ];
}

function spanning_tree(vertices, adjacency_list) {
  return loop(init(vertices, adjacency_list));
}

exports.State = State;
exports.add_adjacent_edges = add_adjacent_edges;
exports.step = step;
exports.loop = loop;
exports.init = init;
exports.spanning_tree = spanning_tree;
/* Utils Not a pure module */
