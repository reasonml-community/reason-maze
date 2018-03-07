'use strict';

var Tile = require("../Types/Tile.js");
var Utils = require("../Maze/Utils.js");
var Coord2d = require("../Coords/Coord2d.js");
var HexTile = require("./Tiles/HexTile.js");
var SimpleBoard = require("../Types/SimpleBoard.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");

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
  for(var x = 0 ,x_finish = shape - 1 | 0; x <= x_finish; ++x){
    for(var y = -x | 0 ,y_finish = Caml_primitive.caml_int_min((shape - x | 0) - 1 | 0, x); y <= y_finish; ++y){
      v = /* :: */[
        /* tuple */[
          x,
          y
        ],
        v
      ];
    }
  }
  for(var x$1 = shape ,x_finish$1 = (shape << 1); x$1 <= x_finish$1; ++x$1){
    for(var y$1 = (x$1 - (shape << 1) | 0) + 2 | 0 ,y_finish$1 = (shape - x$1 | 0) - 1 | 0; y$1 <= y_finish$1; ++y$1){
      v = /* :: */[
        /* tuple */[
          x$1,
          y$1
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
  var across = hint_num;
  if (Utils.Float[/* * */3](cwidth, width_to_height_ratio) < cheight) {
    var size = Utils.Float[/* / */2](cwidth, across);
    var height = Utils.Float[/* * */3](Utils.Float[/* * */3](size, width_to_height_ratio), Utils.Float[/* + */0](across, 0.25));
    console.log(/* tuple */[
          cwidth,
          height
        ]);
    return /* tuple */[
            hint_num,
            size,
            /* tuple */[
              cwidth,
              height
            ]
          ];
  } else {
    var width = Utils.Float[/* / */2](cheight, width_to_height_ratio);
    var size$1 = Utils.Float[/* / */2](width, Utils.Float[/* + */0](across, 0.25));
    return /* tuple */[
            hint_num,
            size$1,
            /* tuple */[
              width,
              cheight
            ]
          ];
  }
}

function offset(_, scale, param) {
  var fx = param[0];
  var fy = param[1];
  var vsize = Utils.Float[/* / */2](Utils.Float[/* * */3](scale, 2.0), Math.sqrt(3.0));
  var vertical = Utils.Float[/* * */3](vsize, 0.75);
  return /* tuple */[
          Utils.Float[/* + */0](Utils.Float[/* - */1](Utils.Float[/* / */2](Utils.Float[/* * */3](fx, scale), 2.0), Utils.Float[/* / */2](Utils.Float[/* * */3](fy, scale), 2.0)), Utils.Float[/* / */2](Utils.Float[/* * */3](scale, width_to_height_ratio), 2.0)),
          Utils.Float[/* + */0](Utils.Float[/* + */0](Utils.Float[/* * */3](fx, vertical), Utils.Float[/* * */3](fy, vertical)), Utils.Float[/* / */2](vsize, 2.0))
        ];
}

function from_point(_, scale, param) {
  var vsize = Utils.Float[/* / */2](Utils.Float[/* * */3](scale, 2.0), Math.sqrt(3.0));
  var vertical = Utils.Float[/* * */3](vsize, 0.75);
  var x$prime = Utils.Float[/* - */1](Utils.Float[/* / */2](Utils.Float[/* * */3](param[0], 2.0), scale), width_to_height_ratio);
  var y$prime = Utils.Float[/* / */2](Utils.Float[/* - */1](param[1], Utils.Float[/* / */2](vsize, 2.0)), vertical);
  var fy = Utils.Float[/* / */2](Utils.Float[/* - */1](y$prime, x$prime), 2.0);
  var fx = Utils.Float[/* + */0](x$prime, fy);
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
