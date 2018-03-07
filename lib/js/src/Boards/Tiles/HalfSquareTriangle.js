'use strict';

var Block = require("bs-platform/lib/js/block.js");

var topleft = /* tuple */[
  -0.5,
  -0.5
];

var topright = /* tuple */[
  0.5,
  -0.5
];

var bottomleft = /* tuple */[
  -0.5,
  0.5
];

var bottomright = /* tuple */[
  0.5,
  0.5
];

var shape = /* Polyline */Block.__(0, [/* :: */[
      topleft,
      /* :: */[
        topright,
        /* :: */[
          bottomleft,
          /* [] */0
        ]
      ]
    ]]);

var flipped_shape = /* Polyline */Block.__(0, [/* :: */[
      topright,
      /* :: */[
        bottomright,
        /* :: */[
          bottomleft,
          /* [] */0
        ]
      ]
    ]]);

function adjacents_simple(is_flipped) {
  if (is_flipped !== 0) {
    return /* :: */[
            /* Right */3,
            /* :: */[
              /* Down */1,
              /* :: */[
                /* TopHalf */4,
                /* [] */0
              ]
            ]
          ];
  } else {
    return /* :: */[
            /* Up */0,
            /* :: */[
              /* Left */2,
              /* :: */[
                /* BottomHalf */5,
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
                1,
                -1
              ];
    case 1 : 
        return /* tuple */[
                -1,
                1
              ];
    case 2 : 
    case 4 : 
        return /* tuple */[
                -1,
                0
              ];
    case 3 : 
    case 5 : 
        return /* tuple */[
                1,
                0
              ];
    
  }
}

function direction_to_border(_, direction) {
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
        return /* Line */Block.__(1, [/* tuple */[
                    topleft,
                    bottomleft
                  ]]);
    case 3 : 
        return /* Line */Block.__(1, [/* tuple */[
                    topright,
                    bottomright
                  ]]);
    case 4 : 
    case 5 : 
        return /* Line */Block.__(1, [/* tuple */[
                    topright,
                    bottomleft
                  ]]);
    
  }
}

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

function to_shape(pos) {
  return to_shape_simple(is_flipped(pos));
}

var Coord = 0;

exports.Coord = Coord;
exports.topleft = topleft;
exports.topright = topright;
exports.bottomleft = bottomleft;
exports.bottomright = bottomright;
exports.shape = shape;
exports.flipped_shape = flipped_shape;
exports.adjacents_simple = adjacents_simple;
exports.adjacent_coord_simple = adjacent_coord_simple;
exports.direction_to_border = direction_to_border;
exports.to_shape_simple = to_shape_simple;
exports.is_flipped = is_flipped;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.to_shape = to_shape;
/* No side effect */
