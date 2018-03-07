'use strict';

var Block = require("bs-platform/lib/js/block.js");

function adjacent_coord(direction) {
  switch (direction) {
    case 0 : 
        return /* tuple */[
                0,
                -1
              ];
    case 1 : 
        return /* tuple */[
                0,
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

function direction_to_border(direction) {
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
    
  }
}

var Coord = 0;

var adjacents = /* :: */[
  /* Up */0,
  /* :: */[
    /* Down */1,
    /* :: */[
      /* Left */2,
      /* :: */[
        /* Right */3,
        /* [] */0
      ]
    ]
  ]
];

var shape = /* Rect */Block.__(1, [/* tuple */[
      -0.5,
      -0.5,
      1.0,
      1.0
    ]]);

exports.Coord = Coord;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.topleft = topleft;
exports.topright = topright;
exports.bottomleft = bottomleft;
exports.bottomright = bottomright;
exports.direction_to_border = direction_to_border;
exports.shape = shape;
/* No side effect */
