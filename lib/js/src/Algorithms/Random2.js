'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("../Maze/Utils.js");
var Random = require("bs-platform/lib/js/random.js");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

function init(size) {
  var start = Random.$$int(size);
  return /* record */[
          /* visited */Belt_Array.make(size, 0),
          /* edges */Utils.intPairSet,
          /* frontier : array */[/* tuple */[
              start,
              start
            ]],
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
  return state[/* step */3];
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

function choose(arr) {
  return Belt_Array.getExn(arr, Random.$$int(arr.length));
}

function jump_to_new_block(state) {
  var remaining = ([]);
  Belt_Array.forEachWithIndex(state[/* visited */0], (function (i, age) {
          if (age === 0) {
            remaining.push(i);
            return /* () */0;
          } else {
            return 0;
          }
        }));
  if (remaining.length !== 0) {
    var start = choose(remaining);
    return /* record */[
            /* visited */state[/* visited */0],
            /* edges */state[/* edges */1],
            /* frontier : array */[/* tuple */[
                start,
                start
              ]],
            /* step */state[/* step */3]
          ];
  } else {
    return state;
  }
}

function step(get_adjacent, _state) {
  while(true) {
    var state = _state;
    var match = state[/* frontier */2];
    if (match.length !== 0) {
      var match$1 = state[/* frontier */2].splice(Random.$$int(state[/* frontier */2].length), 1);
      if (match$1.length !== 1) {
        return state;
      } else {
        var match$2 = match$1[0];
        var dest = match$2[1];
        if (Belt_Array.getExn(state[/* visited */0], dest) > 0) {
          var match$3 = state[/* frontier */2].length;
          _state = match$3 !== 0 ? state : jump_to_new_block(state);
          continue ;
          
        } else {
          Belt_Array.set(state[/* visited */0], dest, state[/* step */3] + 1 | 0);
          var __x = Curry._1(get_adjacent, dest);
          var others = Belt_List.keepMap(__x, (function(state,dest){
              return function (x) {
                if (Belt_Array.getExn(state[/* visited */0], x) === 0) {
                  return /* Some */[/* tuple */[
                            dest,
                            x
                          ]];
                } else {
                  return /* None */0;
                }
              }
              }(state,dest)));
          var frontier = Belt_Array.concat(Belt_List.toArray(others), state[/* frontier */2]);
          var state_000 = /* visited */state[/* visited */0];
          var state_001 = /* edges */Belt_Set.add(state[/* edges */1], sortpair(match$2[0], dest));
          var state_003 = /* step */state[/* step */3] + 1 | 0;
          var state$1 = /* record */[
            state_000,
            state_001,
            /* frontier */frontier,
            state_003
          ];
          var match$4 = frontier.length;
          if (match$4 !== 0) {
            return state$1;
          } else {
            return jump_to_new_block(state$1);
          }
        }
      }
    } else {
      return state;
    }
  };
}

function finished(state) {
  var match = state[/* frontier */2];
  if (match.length !== 0) {
    return /* false */0;
  } else {
    return /* true */1;
  }
}

function loop_to_end(get_adjacent, _state) {
  while(true) {
    var state = _state;
    if (finished(state)) {
      return state;
    } else {
      _state = step(get_adjacent, state);
      continue ;
      
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
exports.choose = choose;
exports.jump_to_new_block = jump_to_new_block;
exports.step = step;
exports.finished = finished;
exports.loop_to_end = loop_to_end;
exports.run = run;
/* Utils Not a pure module */
