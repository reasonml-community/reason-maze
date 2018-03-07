'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");

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

function shape(tile) {
  switch (tile) {
    case 0 : 
        return /* :: */[
                topleft,
                /* :: */[
                  topright,
                  /* :: */[
                    bottomleft,
                    /* [] */0
                  ]
                ]
              ];
    case 1 : 
        return /* :: */[
                topleft,
                /* :: */[
                  topright,
                  /* :: */[
                    bottomright,
                    /* [] */0
                  ]
                ]
              ];
    case 2 : 
        return /* :: */[
                bottomleft,
                /* :: */[
                  bottomright,
                  /* :: */[
                    topleft,
                    /* [] */0
                  ]
                ]
              ];
    case 3 : 
        return /* :: */[
                bottomleft,
                /* :: */[
                  bottomright,
                  /* :: */[
                    topright,
                    /* [] */0
                  ]
                ]
              ];
    
  }
}

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
    case 4 : 
    case 6 : 
        return /* tuple */[
                -1,
                0
              ];
    case 3 : 
    case 5 : 
    case 7 : 
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
    case 5 : 
    case 6 : 
        return /* Line */Block.__(1, [/* tuple */[
                    topleft,
                    bottomright
                  ]]);
    case 4 : 
    case 7 : 
        return /* Line */Block.__(1, [/* tuple */[
                    topright,
                    bottomleft
                  ]]);
    
  }
}

var Unreachable = Caml_exceptions.create("FourSquareTriangle.Unreachable");

function tile(param) {
  var x = param[0];
  var match = x % 2;
  var match$1 = (param[1] + (x / 2 | 0) | 0) % 2;
  if (match !== 0) {
    if (match !== 1) {
      throw Unreachable;
    } else if (match$1 !== 0) {
      if (match$1 !== 1) {
        throw Unreachable;
      } else {
        return /* TR */1;
      }
    } else {
      return /* BR */3;
    }
  } else if (match$1 !== 0) {
    if (match$1 !== 1) {
      throw Unreachable;
    } else {
      return /* BL */2;
    }
  } else {
    return /* TL */0;
  }
}

function adjacents(pos) {
  var tile$1 = tile(pos);
  switch (tile$1) {
    case 0 : 
        return /* :: */[
                /* Up */0,
                /* :: */[
                  /* Left */2,
                  /* :: */[
                    /* DownRight */7,
                    /* [] */0
                  ]
                ]
              ];
    case 1 : 
        return /* :: */[
                /* Up */0,
                /* :: */[
                  /* Right */3,
                  /* :: */[
                    /* DownLeft */6,
                    /* [] */0
                  ]
                ]
              ];
    case 2 : 
        return /* :: */[
                /* Down */1,
                /* :: */[
                  /* Left */2,
                  /* :: */[
                    /* UpRight */5,
                    /* [] */0
                  ]
                ]
              ];
    case 3 : 
        return /* :: */[
                /* Down */1,
                /* :: */[
                  /* Right */3,
                  /* :: */[
                    /* UpLeft */4,
                    /* [] */0
                  ]
                ]
              ];
    
  }
}

function adjacent_coord$1(param, direction) {
  var match = adjacent_coord(direction);
  return /* tuple */[
          param[0] + match[0] | 0,
          param[1] + match[1] | 0
        ];
}

function to_shape(pos) {
  return /* Polyline */Block.__(0, [shape(tile(pos))]);
}

var Coord = 0;

exports.Coord = Coord;
exports.topleft = topleft;
exports.topright = topright;
exports.bottomleft = bottomleft;
exports.bottomright = bottomright;
exports.shape = shape;
exports.direction_to_border = direction_to_border;
exports.Unreachable = Unreachable;
exports.tile = tile;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord$1;
exports.to_shape = to_shape;
/* No side effect */
