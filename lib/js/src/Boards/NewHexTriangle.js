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
  return v;
}

function fi(prim) {
  return prim;
}

function iof(prim) {
  return prim | 0;
}

function auto_size(param, hint_num) {
  var cheight = param[1];
  var cwidth = param[0];
  if (cwidth < Utils.Float[/* * */3](Utils.Float[/* / */2](cheight, Math.sqrt(3.0)), 2.0)) {
    var size = Utils.Float[/* / */2](cwidth, hint_num);
    var height = Utils.Float[/* / */2](Utils.Float[/* * */3](cwidth, Math.sqrt(3.0)), 2.0);
    return /* tuple */[
            hint_num,
            size,
            /* tuple */[
              cwidth,
              height
            ]
          ];
  } else {
    var width = Utils.Float[/* * */3](Utils.Float[/* / */2](cheight, Math.sqrt(3.0)), 2.0);
    var size$1 = Utils.Float[/* / */2](width, hint_num);
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

function offset(shape, scale, param) {
  var fx = param[0];
  var fy = param[1];
  var vsize = Utils.Float[/* / */2](Utils.Float[/* * */3](scale, 2.0), Math.sqrt(3.0));
  var vertical = Utils.Float[/* * */3](vsize, 0.75);
  return /* tuple */[
          Utils.Float[/* + */0](Utils.Float[/* - */1](Utils.Float[/* / */2](Utils.Float[/* * */3](fx, scale), 2.0), Utils.Float[/* / */2](Utils.Float[/* * */3](fy, scale), 2.0)), Utils.Float[/* * */3](Utils.Float[/* / */2](shape, 2.0), scale)),
          Utils.Float[/* + */0](Utils.Float[/* + */0](Utils.Float[/* * */3](fx, vertical), Utils.Float[/* * */3](fy, vertical)), Utils.Float[/* / */2](vsize, 2.0))
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
exports.auto_size = auto_size;
exports.offset = offset;
exports.tile_center = tile_center;
exports.from_point = from_point;
/* include Not a pure module */
