'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");

var pi = (Math.PI);

var tau = pi * 2.0;

function fi(prim) {
  return prim;
}

function ring_counts(n) {
  if (n === 1) {
    return /* :: */[
            2,
            /* [] */0
          ];
  } else if (n === 2) {
    return /* :: */[
            4,
            /* :: */[
              2,
              /* [] */0
            ]
          ];
  } else {
    var match = ring_counts(n - 1 | 0);
    if (match) {
      var rest = match[1];
      var x = match[0];
      if (n * tau / x > 2.0) {
        return /* :: */[
                (x << 1),
                /* :: */[
                  x,
                  rest
                ]
              ];
      } else {
        return /* :: */[
                x,
                /* :: */[
                  x,
                  rest
                ]
              ];
      }
    } else {
      return /* [] */0;
    }
  }
}

var counts = $$Array.of_list(List.rev(ring_counts(1000)));

function adjacents(_, param) {
  var y = param[1];
  if (y) {
    var $$this = Caml_array.caml_array_get(counts, y);
    var next = Caml_array.caml_array_get(counts, y + 1 | 0);
    if (next > $$this) {
      return /* :: */[
              /* UpLeft */4,
              /* :: */[
                /* UpRight */5,
                /* :: */[
                  /* Left */0,
                  /* :: */[
                    /* Right */1,
                    /* :: */[
                      /* Down */2,
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ];
    } else {
      return /* :: */[
              /* Up */3,
              /* :: */[
                /* Left */0,
                /* :: */[
                  /* Right */1,
                  /* :: */[
                    /* Down */2,
                    /* [] */0
                  ]
                ]
              ]
            ];
    }
  } else {
    return /* :: */[
            /* Down */2,
            /* :: */[
              /* UpLeft */4,
              /* :: */[
                /* UpRight */5,
                /* [] */0
              ]
            ]
          ];
  }
}

function adjacent_coord(_, param, direction) {
  var y = param[1];
  var x = param[0];
  switch (direction) {
    case 0 : 
        var match = +(x > 0);
        if (match !== 0) {
          return /* tuple */[
                  x - 1 | 0,
                  y
                ];
        } else {
          return /* tuple */[
                  Caml_array.caml_array_get(counts, y) - 1 | 0,
                  y
                ];
        }
    case 1 : 
        var match$1 = +((x + 1 | 0) < Caml_array.caml_array_get(counts, y));
        return /* tuple */[
                match$1 !== 0 ? x + 1 | 0 : 0,
                y
              ];
    case 2 : 
        var match$2 = +(y === 0);
        if (match$2 !== 0) {
          return /* tuple */[
                  (x + 1 | 0) % 2,
                  y
                ];
        } else {
          var match$3 = +(Caml_array.caml_array_get(counts, y) === Caml_array.caml_array_get(counts, y - 1 | 0));
          if (match$3 !== 0) {
            return /* tuple */[
                    x,
                    y - 1 | 0
                  ];
          } else {
            return /* tuple */[
                    x / 2 | 0,
                    y - 1 | 0
                  ];
          }
        }
        break;
    case 3 : 
        return /* tuple */[
                x,
                y + 1 | 0
              ];
    case 4 : 
        return /* tuple */[
                (x << 1),
                y + 1 | 0
              ];
    case 5 : 
        return /* tuple */[
                (x << 1) + 1 | 0,
                y + 1 | 0
              ];
    
  }
}

function polar(x, y, count) {
  var theta = x / count * tau;
  return /* tuple */[
          y * Math.cos(theta),
          y * Math.sin(theta)
        ];
}

function polarf(x, y, count) {
  var theta = x / count * tau;
  return /* tuple */[
          y * Math.cos(theta),
          y * Math.sin(theta)
        ];
}

function direction_to_border(_, param, direction) {
  var y = param[1];
  var x = param[0];
  switch (direction) {
    case 0 : 
        var count = Caml_array.caml_array_get(counts, y);
        return /* Line */Block.__(1, [/* tuple */[
                    polar(x, y, count),
                    polar(x, y + 1 | 0, count)
                  ]]);
    case 1 : 
        var count$1 = Caml_array.caml_array_get(counts, y);
        return /* Line */Block.__(1, [/* tuple */[
                    polar(x + 1 | 0, y, count$1),
                    polar(x + 1 | 0, y + 1 | 0, count$1)
                  ]]);
    case 2 : 
        if (y) {
          var count$2 = Caml_array.caml_array_get(counts, y);
          return /* Arc */Block.__(0, [/* tuple */[
                      0.0,
                      0.0,
                      y,
                      x / count$2 * tau,
                      (x + 1 | 0) / count$2 * tau
                    ]]);
        } else {
          return /* Line */Block.__(1, [/* tuple */[
                      polar(0, 1, 2),
                      polar(1, 1, 2)
                    ]]);
        }
        break;
    case 3 : 
        var count$3 = Caml_array.caml_array_get(counts, y);
        return /* Arc */Block.__(0, [/* tuple */[
                    0.0,
                    0.0,
                    y + 1 | 0,
                    x / count$3 * tau,
                    (x + 1 | 0) / count$3 * tau
                  ]]);
    case 4 : 
        var count$4 = Caml_array.caml_array_get(counts, y);
        return /* Arc */Block.__(0, [/* tuple */[
                    0.0,
                    0.0,
                    y + 1 | 0,
                    x / count$4 * tau,
                    (0.5 + x) / count$4 * tau
                  ]]);
    case 5 : 
        var count$5 = Caml_array.caml_array_get(counts, y);
        return /* Arc */Block.__(0, [/* tuple */[
                    0.0,
                    0.0,
                    y + 1 | 0,
                    (0.5 + x) / count$5 * tau,
                    (x + 1 | 0) / count$5 * tau
                  ]]);
    
  }
}

function str_pos(param) {
  return "(" + (Pervasives.string_of_int(param[0]) + (", " + (Pervasives.string_of_int(param[1]) + ")")));
}

function coordinates(size) {
  var v = /* [] */0;
  for(var y = 0 ,y_finish = size - 1 | 0; y <= y_finish; ++y){
    var count = Caml_array.caml_array_get(counts, y);
    for(var x = 0 ,x_finish = count - 1 | 0; x <= x_finish; ++x){
      v = /* :: */[
        /* tuple */[
          x,
          y
        ],
        v
      ];
    }
  }
  return v;
}

function auto_size(param, size) {
  var dim = Caml_primitive.caml_float_min(param[0], param[1]);
  var rad = size / 2 | 0;
  var match = +(rad < 1);
  var rad$1 = match !== 0 ? 1 : rad;
  var scale = dim / (rad$1 << 1);
  return /* tuple */[
          rad$1,
          scale,
          /* tuple */[
            dim,
            dim
          ]
        ];
}

function offset(size, scale, _) {
  var dim = (size << 1) * scale;
  var rad = dim / 2.0;
  return /* tuple */[
          rad,
          rad
        ];
}

function tile_center(size, scale, param) {
  var y = param[1];
  var x = param[0];
  var match = offset(size, scale, /* () */0);
  var match$1 = y ? polarf(x + 0.5, scale * (y + 0.5), Caml_array.caml_array_get(counts, y)) : polarf(x + 0.5, scale * 0.5, 2);
  return /* tuple */[
          match$1[0] + match[0],
          match$1[1] + match[1]
        ];
}

function tile_at_coord(_, param) {
  var y = param[1];
  var x = param[0];
  var count = Caml_array.caml_array_get(counts, y);
  return /* Arc */Block.__(2, [/* tuple */[
              /* tuple */[
                0.0,
                0.0
              ],
              y,
              y + 1 | 0,
              tau * x / count,
              tau * (x + 1 | 0) / count
            ]]);
}

function from_point(_, _$1, _$2) {
  return /* tuple */[
          0,
          0
        ];
}

var Coord = 0;

exports.Coord = Coord;
exports.pi = pi;
exports.tau = tau;
exports.fi = fi;
exports.ring_counts = ring_counts;
exports.counts = counts;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.polar = polar;
exports.polarf = polarf;
exports.direction_to_border = direction_to_border;
exports.str_pos = str_pos;
exports.coordinates = coordinates;
exports.auto_size = auto_size;
exports.offset = offset;
exports.tile_center = tile_center;
exports.tile_at_coord = tile_at_coord;
exports.from_point = from_point;
/* pi Not a pure module */
