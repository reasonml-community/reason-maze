'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("../Maze/Utils.js");
var Random = require("bs-platform/lib/js/random.js");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function RandomConfig() {
  var maxHits = 1 + Random.$$int(20) | 0;
  var joinOnHit = Random.$$float(1.0);
  return /* module */[
          /* maxHits */maxHits,
          /* joinOnHit */joinOnHit
        ];
}

function F(Config) {
  var init = function (size) {
    var start = Random.$$int(size);
    return /* record */[
            /* visited */Belt_Array.make(size, 0),
            /* edges */Utils.intPairSet,
            /* frontier : array */[],
            /* step */0,
            /* active : Some */[/* tuple */[
                /* tuple */[
                  start,
                  start
                ],
                0
              ]]
          ];
  };
  var edges = function (state) {
    return state[/* edges */1];
  };
  var visited = function (state) {
    return state[/* visited */0];
  };
  var max_age = function (state) {
    return state[/* step */3];
  };
  var finished = function (state) {
    return +(state[/* active */4] === /* None */0);
  };
  var sortpair = function (a, b) {
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
  };
  var add_edge = function (edges, src, dest) {
    return Belt_Set.add(edges, sortpair(src, dest));
  };
  var shouldHit = function (prob) {
    if (prob !== 0.0) {
      if (prob !== 1.0) {
        return +(Random.$$float(1.0) < prob);
      } else {
        return /* true */1;
      }
    } else {
      return /* false */0;
    }
  };
  var get_new = function (state) {
    var frontier = state[/* frontier */2];
    if (frontier.length === 0) {
      return /* record */[
              /* visited */state[/* visited */0],
              /* edges */state[/* edges */1],
              /* frontier */state[/* frontier */2],
              /* step */state[/* step */3],
              /* active : None */0
            ];
    } else {
      var match = frontier.splice(Random.$$int(frontier.length), 1);
      if (match.length !== 1) {
        return /* record */[
                /* visited */state[/* visited */0],
                /* edges */state[/* edges */1],
                /* frontier */frontier,
                /* step */state[/* step */3],
                /* active */state[/* active */4]
              ];
      } else {
        var item = match[0];
        return /* record */[
                /* visited */state[/* visited */0],
                /* edges */state[/* edges */1],
                /* frontier */frontier,
                /* step */state[/* step */3],
                /* active : Some */[/* tuple */[
                    item,
                    0
                  ]]
              ];
      }
    }
  };
  var step = function (get_adjacent, _state) {
    while(true) {
      var state = _state;
      var step_count = state[/* step */3];
      var match = state[/* active */4];
      if (match) {
        var match$1 = match[0];
        var hits = match$1[1];
        var match$2 = match$1[0];
        var dest = match$2[1];
        var src = match$2[0];
        if (Belt_Array.getExn(state[/* visited */0], dest) > 0) {
          _state = get_new(state);
          continue ;
          
        } else {
          var __x = Utils.shuffle(Curry._1(get_adjacent, dest));
          var others = Belt_List.keepMap(__x, (function(src,dest){
              return function (x) {
                if (x === src) {
                  return /* None */0;
                } else {
                  return /* Some */[/* tuple */[
                            dest,
                            x
                          ]];
                }
              }
              }(src,dest)));
          var step_count$1 = step_count + 1 | 0;
          Belt_Array.set(state[/* visited */0], dest, step_count$1);
          var edges = add_edge(state[/* edges */1], src, dest);
          var _adjacents = others;
          var _hit = /* false */0;
          while(true) {
            var hit = _hit;
            var adjacents = _adjacents;
            if (adjacents) {
              var rest = adjacents[1];
              var match$3 = adjacents[0];
              var edest = match$3[1];
              var esrc = match$3[0];
              if (Belt_Array.getExn(state[/* visited */0], edest) > 0) {
                if (hits > Config[/* maxHits */0]) {
                  var match$4 = shouldHit(Config[/* joinOnHit */1]);
                  var edges$1 = match$4 !== 0 ? add_edge(edges, esrc, edest) : edges;
                  return get_new(/* record */[
                              /* visited */state[/* visited */0],
                              /* edges */edges$1,
                              /* frontier */state[/* frontier */2],
                              /* step */step_count$1,
                              /* active */state[/* active */4]
                            ]);
                } else {
                  _hit = /* true */1;
                  _adjacents = rest;
                  continue ;
                  
                }
              } else {
                var frontier = Belt_Array.concat(Belt_List.toArray(rest), state[/* frontier */2]);
                return /* record */[
                        /* visited */state[/* visited */0],
                        /* edges */edges,
                        /* frontier */frontier,
                        /* step */step_count$1,
                        /* active : Some */[/* tuple */[
                            /* tuple */[
                              esrc,
                              edest
                            ],
                            hit !== 0 ? hits + 1 | 0 : hits
                          ]]
                      ];
              }
            } else {
              return get_new(/* record */[
                          /* visited */state[/* visited */0],
                          /* edges */edges,
                          /* frontier */state[/* frontier */2],
                          /* step */step_count$1,
                          /* active */state[/* active */4]
                        ]);
            }
          };
        }
      } else {
        return state;
      }
    };
  };
  var step__ = function (get_adjacent, state) {
    var nonEmptyArray = state[/* frontier */2];
    if (nonEmptyArray.length !== 0) {
      var match = nonEmptyArray.splice(Random.$$int(nonEmptyArray.length), 1);
      if (match.length !== 1) {
        throw [
              Caml_builtin_exceptions.assert_failure,
              [
                "NewDepth.re",
                154,
                13
              ]
            ];
      } else {
        var match$1 = match[0];
        var dest = match$1[1];
        if (Belt_Array.getExn(state[/* visited */0], dest) > 0) {
          return step(get_adjacent, state);
        } else {
          Belt_Array.set(state[/* visited */0], dest, state[/* step */3] + 1 | 0);
          var __x = Curry._1(get_adjacent, dest);
          var others = Belt_List.keepMap(__x, (function (x) {
                  if (Belt_Array.getExn(state[/* visited */0], x) === 0) {
                    return /* Some */[/* tuple */[
                              dest,
                              x
                            ]];
                  } else {
                    return /* None */0;
                  }
                }));
          return /* record */[
                  /* visited */state[/* visited */0],
                  /* edges */Belt_Set.add(state[/* edges */1], sortpair(match$1[0], dest)),
                  /* frontier */Belt_Array.concat(Belt_List.toArray(others), nonEmptyArray),
                  /* step */state[/* step */3] + 1 | 0,
                  /* active */state[/* active */4]
                ];
        }
      }
    } else {
      return state;
    }
  };
  var loop_to_end = function (get_adjacent, _state) {
    while(true) {
      var state = _state;
      if (state[/* active */4] !== /* None */0) {
        _state = step(get_adjacent, state);
        continue ;
        
      } else {
        return state;
      }
    };
  };
  var run = function (size, get_adjacent) {
    return loop_to_end(get_adjacent, init(size));
  };
  return /* module */[
          /* init */init,
          /* edges */edges,
          /* visited */visited,
          /* max_age */max_age,
          /* finished */finished,
          /* sortpair */sortpair,
          /* add_edge */add_edge,
          /* shouldHit */shouldHit,
          /* get_new */get_new,
          /* step */step,
          /* step__ */step__,
          /* loop_to_end */loop_to_end,
          /* run */run
        ];
}

exports.RandomConfig = RandomConfig;
exports.F = F;
/* Utils Not a pure module */
