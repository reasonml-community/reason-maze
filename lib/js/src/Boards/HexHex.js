'use strict';

var Tile = require("../Types/Tile.js");
var Utils = require("../Maze/Utils.js");
var Coord2d = require("../Coords/Coord2d.js");
var HexTile = require("./Tiles/HexTile.js");
var SimpleBoard = require("../Types/SimpleBoard.js");

var include = SimpleBoard.FromTile(Tile.FromSimple([
          /* Coord2d */[
            Coord2d.offset,
            Coord2d.compare
          ],
          HexTile.adjacents,
          HexTile.adjacent_coord,
          HexTile.direction_to_border,
          HexTile.shape
        ]));

function coordinates(shape) {
  var v = /* [] */0;
  for(var y = 0 ,y_finish = shape - 1 | 0; y <= y_finish; ++y){
    for(var x = 0 ,x_finish = (shape - y | 0) - 1 | 0; x <= x_finish; ++x){
      v = /* :: */[
        /* tuple */[
          x,
          y
        ],
        v
      ];
    }
  }
  for(var y$1 = 0 ,y_finish$1 = shape - 2 | 0; y$1 <= y_finish$1; ++y$1){
    for(var x$1 = y$1 ,x_finish$1 = shape - 2 | 0; x$1 <= x_finish$1; ++x$1){
      v = /* :: */[
        /* tuple */[
          (-x$1 | 0) - 1 | 0,
          y$1
        ],
        v
      ];
    }
  }
  for(var y$2 = 0 ,y_finish$2 = shape - 2 | 0; y$2 <= y_finish$2; ++y$2){
    for(var x$2 = y$2 ,x_finish$2 = shape - 2 | 0; x$2 <= x_finish$2; ++x$2){
      v = /* :: */[
        /* tuple */[
          x$2 + 1 | 0,
          (-y$2 | 0) - 1 | 0
        ],
        v
      ];
    }
  }
  for(var y$3 = 0 ,y_finish$3 = shape - 2 | 0; y$3 <= y_finish$3; ++y$3){
    for(var x$3 = 0 ,x_finish$3 = (shape - y$3 | 0) - 2 | 0; x$3 <= x_finish$3; ++x$3){
      v = /* :: */[
        /* tuple */[
          -x$3 | 0,
          (-y$3 | 0) - 1 | 0
        ],
        v
      ];
    }
  }
  for(var x$4 = 0 ,x_finish$4 = shape - 2 | 0; x$4 <= x_finish$4; ++x$4){
    for(var y$4 = x$4 ,y_finish$4 = shape - 2 | 0; y$4 <= y_finish$4; ++y$4){
      v = /* :: */[
        /* tuple */[
          (-x$4 | 0) - 1 | 0,
          y$4 + 1 | 0
        ],
        v
      ];
    }
  }
  for(var x$5 = 0 ,x_finish$5 = shape - 2 | 0; x$5 <= x_finish$5; ++x$5){
    for(var y$5 = x$5 ,y_finish$5 = shape - 3 | 0; y$5 <= y_finish$5; ++y$5){
      v = /* :: */[
        /* tuple */[
          x$5 + 1 | 0,
          (-y$5 | 0) - 2 | 0
        ],
        v
      ];
    }
  }
  return v;
}

function fi(prim) {
  return prim;
}

function iof(prim) {
  return prim | 0;
}

var width_to_height_ratio = 1.0 / 2.0 * Math.sqrt(3.0);

function auto_size(param, hint_num) {
  var cheight = param[1];
  var cwidth = param[0];
  var hint_num$1 = hint_num / 2 | 0;
  var across = (hint_num$1 << 1) - 1 | 0;
  if (Utils.Float[/* * */3](cwidth, width_to_height_ratio) < cheight) {
    var size = Utils.Float[/* / */2](cwidth, across);
    var height = Utils.Float[/* * */3](cwidth, width_to_height_ratio);
    return /* tuple */[
            hint_num$1,
            size,
            /* tuple */[
              cwidth,
              height
            ]
          ];
  } else {
    var width = Utils.Float[/* / */2](cheight, width_to_height_ratio);
    var size$1 = Utils.Float[/* / */2](width, across);
    return /* tuple */[
            hint_num$1,
            size$1,
            /* tuple */[
              width,
              cheight
            ]
          ];
  }
}

function offset(shape, scale, param) {
  var fx = param[0];
  var fy = param[1];
  var across = (shape << 1) - 1 | 0;
  var cx = Utils.Float[/* / */2](Utils.Float[/* * */3](scale, across), 2.0);
  var vsize = Utils.Float[/* / */2](Utils.Float[/* * */3](scale, 2.0), Math.sqrt(3.0));
  var vertical = Utils.Float[/* * */3](vsize, 0.75);
  var cy = Utils.Float[/* / */2](Utils.Float[/* * */3](vertical, across), 2.0);
  return /* tuple */[
          Utils.Float[/* + */0](Utils.Float[/* - */1](Utils.Float[/* / */2](Utils.Float[/* * */3](fx, scale), 2.0), Utils.Float[/* / */2](Utils.Float[/* * */3](fy, scale), 2.0)), cx),
          Utils.Float[/* + */0](Utils.Float[/* + */0](Utils.Float[/* * */3](fx, vertical), Utils.Float[/* * */3](fy, vertical)), cy)
        ];
}

function from_point(_, _$1, _$2) {
  return /* tuple */[
          0,
          0
        ];
}

var Coord = include[0];

var adjacents = include[1];

var adjacent_coord = include[2];

var direction_to_border = include[3];

var tile_at_coord = include[4];

var tile_center = offset;

exports.Coord = Coord;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.direction_to_border = direction_to_border;
exports.tile_at_coord = tile_at_coord;
exports.coordinates = coordinates;
exports.fi = fi;
exports.iof = iof;
exports.width_to_height_ratio = width_to_height_ratio;
exports.auto_size = auto_size;
exports.offset = offset;
exports.tile_center = tile_center;
exports.from_point = from_point;
/* include Not a pure module */
