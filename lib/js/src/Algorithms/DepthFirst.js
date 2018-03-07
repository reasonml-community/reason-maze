'use strict';

var Utils = require("../Maze/Utils.js");
var Random = require("bs-platform/lib/js/random.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

function shouldHit(prob) {
  if (prob !== 0.0) {
    if (prob !== 1.0) {
      return +(Random.$$float(1.0) < prob);
    } else {
      return /* true */1;
    }
  } else {
    return /* false */0;
  }
}

function F(Config) {
  var traveled = function (t) {
    return t[/* traveled */4];
  };
  var current = function (t) {
    return Belt_List.map(Belt_List.ofArray(t[/* current */2]), (function (param) {
                  return param[/* dest */1];
                }));
  };
  var next = function (t) {
    var match = t[/* active */5];
    if (match) {
      return /* :: */[
              match[0][0][/* dest */1],
              /* [] */0
            ];
    } else {
      return /* [] */0;
    }
  };
  var age = function (t) {
    return t[/* age */3];
  };
  var finished = function (t) {
    return +(t[/* active */5] === /* None */0);
  };
  var State = /* module */[
    /* traveled */traveled,
    /* current */current,
    /* next */next,
    /* age */age,
    /* finished */finished
  ];
  var adjacent_edges = function (visited, src, adjacents) {
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
  };
  var get_new = function (state) {
    var current = state[/* current */2];
    if (current.length) {
      var match = current.splice(Random.$$int(current.length), 1);
      if (match.length !== 1) {
        var newrecord = state.slice();
        newrecord[/* current */2] = current;
        return newrecord;
      } else {
        var item = match[0];
        return /* record */[
                /* adjacency_list */state[/* adjacency_list */0],
                /* visited */state[/* visited */1],
                /* current */current,
                /* age */state[/* age */3],
                /* traveled */state[/* traveled */4],
                /* active : Some */[/* tuple */[
                    item,
                    0
                  ]]
              ];
      }
    } else {
      var newrecord$1 = state.slice();
      newrecord$1[/* active */5] = /* None */0;
      return newrecord$1;
    }
  };
  var step = function (state) {
    var active = state[/* active */5];
    if (active) {
      var match = active[0];
      var hits = match[1];
      var src = match[0];
      var traveled = state[/* traveled */4];
      var current = state[/* current */2];
      var visited = state[/* visited */1];
      if (Belt_Array.getExn(visited, src[/* dest */1])) {
        var newrecord = state.slice();
        return get_new((newrecord[/* traveled */4] = traveled, newrecord));
      } else {
        var adjacents = Utils.shuffle(Belt_Array.getExn(state[/* adjacency_list */0], src[/* dest */1]));
        var edges = Belt_List.map(adjacents, (function (dest) {
                return /* record */[
                        /* src */src[/* dest */1],
                        /* dest */dest,
                        /* age */0
                      ];
              }));
        var edges$1 = Belt_List.keep(edges, (function (x) {
                return +(x[/* dest */1] !== src[/* src */0]);
              }));
        var age = state[/* age */3] + 1 | 0;
        Belt_Array.set(visited, src[/* dest */1], /* true */1);
        var traveled_000 = /* record */[
          /* src */src[/* src */0],
          /* dest */src[/* dest */1],
          /* age */age
        ];
        var traveled$1 = /* :: */[
          traveled_000,
          traveled
        ];
        var _edges = edges$1;
        var state$1 = state;
        var _hit = /* false */0;
        while(true) {
          var hit = _hit;
          var edges$2 = _edges;
          if (edges$2) {
            var others = edges$2[1];
            var edge = edges$2[0];
            if (Belt_Array.getExn(visited, edge[/* dest */1])) {
              if (hits > Config[/* maxHits */0]) {
                var match$1 = shouldHit(Config[/* joinOnHit */1]);
                var traveled$2 = match$1 !== 0 ? /* :: */[
                    /* record */[
                      /* src */edge[/* src */0],
                      /* dest */edge[/* dest */1],
                      /* age */age
                    ],
                    traveled$1
                  ] : traveled$1;
                return get_new(/* record */[
                            /* adjacency_list */state$1[/* adjacency_list */0],
                            /* visited */state$1[/* visited */1],
                            /* current */state$1[/* current */2],
                            /* age */age,
                            /* traveled */traveled$2,
                            /* active */state$1[/* active */5]
                          ]);
              } else {
                _hit = /* true */1;
                _edges = others;
                continue ;
                
              }
            } else {
              var current$1 = Belt_Array.concat(Belt_List.toArray(others), current);
              return /* record */[
                      /* adjacency_list */state$1[/* adjacency_list */0],
                      /* visited */state$1[/* visited */1],
                      /* current */current$1,
                      /* age */age,
                      /* traveled */traveled$1,
                      /* active : Some */[/* tuple */[
                          edge,
                          hit !== 0 ? hits + 1 | 0 : hits
                        ]]
                    ];
            }
          } else {
            console.log("ran out of edges");
            console.log(Belt_List.length(edges$2));
            return get_new(/* record */[
                        /* adjacency_list */state$1[/* adjacency_list */0],
                        /* visited */state$1[/* visited */1],
                        /* current */state$1[/* current */2],
                        /* age */age,
                        /* traveled */traveled$1,
                        /* active */state$1[/* active */5]
                      ]);
          }
        };
      }
    } else {
      return state;
    }
  };
  var loop = function (_state) {
    while(true) {
      var state = _state;
      var state$1 = step(state);
      if (state$1[/* active */5]) {
        _state = state$1;
        continue ;
        
      } else {
        return state$1[/* traveled */4];
      }
    };
  };
  var init = function (vertices, adjacency_list) {
    var visited = Belt_Array.make(vertices, /* false */0);
    var initial = Random.$$int(vertices);
    return /* record */[
            /* adjacency_list */adjacency_list,
            /* visited */visited,
            /* current : array */[],
            /* age */0,
            /* traveled : [] */0,
            /* active : Some */[/* tuple */[
                /* record */[
                  /* src */initial,
                  /* dest */initial,
                  /* age */0
                ],
                0
              ]]
          ];
  };
  var spanning_tree = function (vertices, adjacency_list) {
    return loop(init(vertices, adjacency_list));
  };
  return /* module */[
          /* State */State,
          /* adjacent_edges */adjacent_edges,
          /* get_new */get_new,
          /* step */step,
          /* loop */loop,
          /* init */init,
          /* spanning_tree */spanning_tree
        ];
}

exports.shouldHit = shouldHit;
exports.F = F;
/* No side effect */
