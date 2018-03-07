'use strict';

var Tile = require("../Types/Tile.js");
var Coord2d = require("../Coords/Coord2d.js");
var SquareTile = require("./Tiles/SquareTile.js");
var SimpleBoard = require("../Types/SimpleBoard.js");

var include = SimpleBoard.FromTile(Tile.FromSimple([
          /* Coord2d */[
            Coord2d.offset,
            Coord2d.compare
          ],
          SquareTile.adjacents,
          SquareTile.adjacent_coord,
          SquareTile.direction_to_border,
          SquareTile.shape
        ]));

function coordinates(param) {
  var h = param[1];
  var v = /* [] */0;
  for(var x = 0 ,x_finish = param[0] - 1 | 0; x <= x_finish; ++x){
    for(var y = 0 ,y_finish = h - 1 | 0; y <= y_finish; ++y){
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
  var dim = cwidth < cheight ? cwidth : cheight;
  var size = dim / hint_num;
  var width = cwidth / size | 0;
  var height = cheight / size | 0;
  return /* tuple */[
          /* tuple */[
            width,
            height
          ],
          size,
          /* tuple */[
            width * size,
            height * size
          ]
        ];
}

function offset(_, scale, param) {
  return /* tuple */[
          (param[0] + 0.5) * scale,
          (param[1] + 0.5) * scale
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
