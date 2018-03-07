'use strict';

var Block = require("bs-platform/lib/js/block.js");

var sq3 = Math.sqrt(3.0);

var qsq3 = sq3 / 4.0;

function adjacents_simple(is_flipped) {
  if (is_flipped !== 0) {
    return /* :: */[
            /* Left */2,
            /* :: */[
              /* Right */3,
              /* :: */[
                /* Up */0,
                /* [] */0
              ]
            ]
          ];
  } else {
    return /* :: */[
            /* Left */2,
            /* :: */[
              /* Right */3,
              /* :: */[
                /* Down */1,
                /* [] */0
              ]
            ]
          ];
  }
}

function adjacent_coord_simple(direction) {
  switch (direction) {
    case 0 : 
        return /* tuple */[
                -1,
                -1
              ];
    case 1 : 
        return /* tuple */[
                1,
                1
              ];
    case 2 : 
        return /* tuple */[
                -1,
                0
              ];
    case 3 : 
        return /* tuple */[
                1,
                0
              ];
    
  }
}

var topleft_001 = -qsq3;

var topleft = /* tuple */[
  -0.5,
  topleft_001
];

var topright_001 = -qsq3;

var topright = /* tuple */[
  0.5,
  topright_001
];

var bottomcenter = /* tuple */[
  0.0,
  qsq3
];

var topcenter_001 = -qsq3;

var topcenter = /* tuple */[
  0.0,
  topcenter_001
];

var bottomleft = /* tuple */[
  -0.5,
  qsq3
];

var bottomright = /* tuple */[
  0.5,
  qsq3
];

function direction_to_border_simple(is_flipped, direction) {
  switch (direction) {
    case 0 : 
        return /* Line */Block.__(1, [/* tuple */[
                    topleft,
                    topright
                  ]]);
    case 1 : 
        return /* Line */Block.__(1, [/* tuple */[
                    bottomleft,
                    bottomright
                  ]]);
    case 2 : 
        if (is_flipped !== 0) {
          return /* Line */Block.__(1, [/* tuple */[
                      bottomcenter,
                      topleft
                    ]]);
        } else {
          return /* Line */Block.__(1, [/* tuple */[
                      topcenter,
                      bottomleft
                    ]]);
        }
    case 3 : 
        if (is_flipped !== 0) {
          return /* Line */Block.__(1, [/* tuple */[
                      bottomcenter,
                      topright
                    ]]);
        } else {
          return /* Line */Block.__(1, [/* tuple */[
                      topcenter,
                      bottomright
                    ]]);
        }
    
  }
}

var shape = /* Polyline */Block.__(0, [/* :: */[
      topcenter,
      /* :: */[
        bottomleft,
        /* :: */[
          bottomright,
          /* [] */0
        ]
      ]
    ]]);

var flipped_shape = /* Polyline */Block.__(0, [/* :: */[
      topleft,
      /* :: */[
        topright,
        /* :: */[
          bottomcenter,
          /* [] */0
        ]
      ]
    ]]);

function to_shape_simple(is_flipped) {
  if (is_flipped !== 0) {
    return flipped_shape;
  } else {
    return shape;
  }
}

function is_flipped(param) {
  return +(param[0] % 2 !== 0);
}

function adjacents(pos) {
  return adjacents_simple(is_flipped(pos));
}

function adjacent_coord(param, direction) {
  var match = adjacent_coord_simple(direction);
  return /* tuple */[
          param[0] + match[0] | 0,
          param[1] + match[1] | 0
        ];
}

function direction_to_border(pos) {
  var partial_arg = is_flipped(pos);
  return (function (param) {
      return direction_to_border_simple(partial_arg, param);
    });
}

function to_shape(pos) {
  return to_shape_simple(is_flipped(pos));
}

var Coord = 0;

exports.Coord = Coord;
exports.sq3 = sq3;
exports.qsq3 = qsq3;
exports.adjacents_simple = adjacents_simple;
exports.adjacent_coord_simple = adjacent_coord_simple;
exports.topleft = topleft;
exports.topright = topright;
exports.bottomcenter = bottomcenter;
exports.topcenter = topcenter;
exports.bottomleft = bottomleft;
exports.bottomright = bottomright;
exports.direction_to_border_simple = direction_to_border_simple;
exports.shape = shape;
exports.flipped_shape = flipped_shape;
exports.to_shape_simple = to_shape_simple;
exports.is_flipped = is_flipped;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.direction_to_border = direction_to_border;
exports.to_shape = to_shape;
/* sq3 Not a pure module */
