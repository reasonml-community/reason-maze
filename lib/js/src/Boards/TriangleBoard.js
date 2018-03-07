'use strict';

var Utils = require("../Maze/Utils.js");
var Coord2d = require("../Coords/Coord2d.js");
var SimpleBoard = require("../Types/SimpleBoard.js");
var EquilateralTriangle = require("./Tiles/EquilateralTriangle.js");

var include = SimpleBoard.FromTile([
      /* Coord2d */[
        Coord2d.offset,
        Coord2d.compare
      ],
      EquilateralTriangle.adjacents,
      EquilateralTriangle.adjacent_coord,
      EquilateralTriangle.direction_to_border,
      EquilateralTriangle.to_shape
    ]);

function coordinates(size) {
  var v = /* [] */0;
  for(var y = 0 ,y_finish = size - 1 | 0; y <= y_finish; ++y){
    for(var x = 0 ,x_finish = (y << 1); x <= x_finish; ++x){
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

function auto_size(param, hint_num) {
  var cwidth = param[0];
  var size = cwidth / hint_num;
  return /* tuple */[
          hint_num,
          size,
          /* tuple */[
            cwidth,
            cwidth * Math.sqrt(3.0) / 2.0
          ]
        ];
}

var hsq3 = Math.sqrt(3.0) / 2.0;

function fi(prim) {
  return prim;
}

function offset(shape, scale, param) {
  var fx = param[0];
  var fy = param[1];
  return /* tuple */[
          Utils.Float[/* * */3](Utils.Float[/* / */2](Utils.Float[/* + */0](Utils.Float[/* - */1](fx, fy), shape), 2.0), scale),
          Utils.Float[/* * */3](Utils.Float[/* * */3](Utils.Float[/* + */0](fy, 0.5), hsq3), scale)
        ];
}

var offcenter = 0.5 - 0.5 / Math.sqrt(3.0);

function tile_center(shape, scale, param) {
  var y = param[1];
  var x = param[0];
  var match = offset(shape, scale, /* tuple */[
        x,
        y
      ]);
  var dy = EquilateralTriangle.is_flipped(/* tuple */[
        x,
        y
      ]) ? -scale * offcenter / 1.5 : scale * offcenter / 1.5;
  return /* tuple */[
          match[0],
          match[1] + dy
        ];
}

function from_point(shape, scale, param) {
  var fshape = shape;
  var fy = Utils.Float[/* - */1](Utils.Float[/* / */2](Utils.Float[/* / */2](param[1], hsq3), scale), 0.5);
  var fx = Utils.Float[/* + */0](Utils.Float[/* - */1](Utils.Float[/* / */2](Utils.Float[/* * */3](param[0], 2.0), scale), fshape), fy);
  return /* tuple */[
          fx | 0,
          fy | 0
        ];
}

var Coord = include[0];

var adjacents = include[1];

var adjacent_coord = include[2];

var direction_to_border = include[3];

var tile_at_coord = include[4];

exports.Coord = Coord;
exports.adjacents = adjacents;
exports.adjacent_coord = adjacent_coord;
exports.direction_to_border = direction_to_border;
exports.tile_at_coord = tile_at_coord;
exports.coordinates = coordinates;
exports.auto_size = auto_size;
exports.hsq3 = hsq3;
exports.fi = fi;
exports.offset = offset;
exports.offcenter = offcenter;
exports.tile_center = tile_center;
exports.from_point = from_point;
/* include Not a pure module */
