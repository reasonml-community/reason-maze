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
                -1,
                0
              ];
    case 2 : 
        return /* tuple */[
                1,
                0
              ];
    case 3 : 
        return /* tuple */[
                0,
                1
              ];
    case 4 : 
        return /* tuple */[
                -1,
                1
              ];
    case 5 : 
        return /* tuple */[
                1,
                -1
              ];
    
  }
}

var hsq3 = Math.sqrt(3.0) / 2.0;

var isq3 = 1.0 / Math.sqrt(3.0);

var top_001 = -isq3;

var top = /* tuple */[
  0.0,
  top_001
];

var bottom = /* tuple */[
  0.0,
  isq3
];

var tl_001 = -hsq3 + isq3;

var tl = /* tuple */[
  -0.5,
  tl_001
];

var tr_001 = -hsq3 + isq3;

var tr = /* tuple */[
  0.5,
  tr_001
];

var bl_001 = hsq3 - isq3;

var bl = /* tuple */[
  -0.5,
  bl_001
];

var br_001 = hsq3 - isq3;

var br = /* tuple */[
  0.5,
  br_001
];

function direction_to_border(direction) {
  var tmp;
  switch (direction) {
    case 0 : 
        tmp = /* tuple */[
          top,
          tr
        ];
        break;
    case 1 : 
        tmp = /* tuple */[
          top,
          tl
        ];
        break;
    case 2 : 
        tmp = /* tuple */[
          bottom,
          br
        ];
        break;
    case 3 : 
        tmp = /* tuple */[
          bottom,
          bl
        ];
        break;
    case 4 : 
        tmp = /* tuple */[
          tl,
          bl
        ];
        break;
    case 5 : 
        tmp = /* tuple */[
          tr,
          br
        ];
        break;
    
  }
  return /* Line */Block.__(1, [tmp]);
}

var shape = /* Polyline */Block.__(0, [/* :: */[
      top,
      /* :: */[
        tr,
        /* :: */[
          br,
          /* :: */[
            bottom,
            /* :: */[
              bl,
              /* :: */[
                tl,
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]]);

var Coord = 0;

var adjacents = /* :: */[
  /* UpRight */0,
  /* :: */[
    /* UpLeft */1,
    /* :: */[
      /* DownRight */2,
      /* :: */[
        /* DownLeft */3,
        /* :: */[
          /* Left */4,
          /* :: */[
            /* Right */5,
            /* [] */0
          ]
        ]
      ]
    ]
  ]
];

exports.Coord = Coord;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.hsq3 = hsq3;
exports.isq3 = isq3;
exports.top = top;
exports.bottom = bottom;
exports.tl = tl;
exports.tr = tr;
exports.bl = bl;
exports.br = br;
exports.direction_to_border = direction_to_border;
exports.shape = shape;
/* hsq3 Not a pure module */
