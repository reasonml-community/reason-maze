'use strict';

var Show = require("./Show.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Paint = require("./Paint.js");
var Circle = require("../Boards/Circle.js");
var HexBox = require("../Boards/HexBox.js");
var HexHex = require("../Boards/HexHex.js");
var Random = require("bs-platform/lib/js/random.js");
var Coord2d = require("../Coords/Coord2d.js");
var NewRect = require("../Boards/NewRect.js");
var Random2 = require("../Algorithms/Random2.js");
var NewDepth = require("../Algorithms/NewDepth.js");
var Presenter = require("./Presenter.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var TriangleBoard = require("../Boards/TriangleBoard.js");
var NewHexTriangle = require("../Boards/NewHexTriangle.js");

function random_line() {
  return /* tuple */[
          1.0 + Random.$$int(10),
          Presenter.hsl(0, 0, Random.$$int(80))
        ];
}

function random_options(canvas_size) {
  var match = Random.bool(/* () */0);
  var match$1 = Random.bool(/* () */0);
  var match$2 = Random.bool(/* () */0);
  var tmp;
  if (match$2 !== 0) {
    var hue = Random.$$float(360.0);
    var saturation = 70.0 + Random.$$float(30.0);
    tmp = /* Some */[(function (current, _) {
          return Presenter.hslf(hue, saturation, current * 100.0);
        })];
  } else {
    tmp = /* None */0;
  }
  var options_002 = /* size_hint */6 + Random.$$int(10) | 0;
  var options_003 = /* draw_edges */match !== 0 ? /* Some */[random_line(/* () */0)] : /* None */0;
  var options_004 = /* draw_walls */match$1 !== 0 ? /* Some */[random_line(/* () */0)] : /* None */0;
  var options = /* record */[
    /* canvas_size */canvas_size,
    /* min_margin */50.0,
    options_002,
    options_003,
    options_004,
    /* draw_shapes */tmp
  ];
  var match$3 = +(options_003 === /* None */0 && /* draw_shapes */tmp === /* None */0 && options_004 === /* None */0);
  if (match$3 !== 0) {
    var newrecord = options.slice();
    newrecord[/* draw_walls */4] = /* Some */[random_line(/* () */0)];
    return newrecord;
  } else {
    return options;
  }
}

function run(ctx, canvas_size) {
  var seed = (parseInt(Math.random() * Number.MAX_SAFE_INTEGER));
  Random.init(seed);
  console.log(/* tuple */[
        "Seed",
        seed
      ]);
  var options = random_options(canvas_size);
  var choose = function (arr) {
    return Belt_Array.getExn(arr, Random.$$int(arr.length));
  };
  var random_board = function () {
    return choose(/* array */[
                [
                  /* Coord2d */[
                    Coord2d.offset,
                    Coord2d.compare
                  ],
                  Circle.adjacents,
                  Circle.adjacent_coord,
                  Circle.direction_to_border,
                  Circle.coordinates,
                  Circle.auto_size,
                  Circle.offset,
                  Circle.tile_center,
                  Circle.tile_at_coord,
                  Circle.from_point
                ],
                [
                  HexBox.Coord,
                  HexBox.adjacents,
                  HexBox.adjacent_coord,
                  HexBox.direction_to_border,
                  HexBox.coordinates,
                  HexBox.auto_size,
                  HexBox.offset,
                  HexBox.tile_center,
                  HexBox.tile_at_coord,
                  HexBox.from_point
                ],
                [
                  HexHex.Coord,
                  HexHex.adjacents,
                  HexHex.adjacent_coord,
                  HexHex.direction_to_border,
                  HexHex.coordinates,
                  HexHex.auto_size,
                  HexHex.offset,
                  HexHex.tile_center,
                  HexHex.tile_at_coord,
                  HexHex.from_point
                ],
                [
                  TriangleBoard.Coord,
                  TriangleBoard.adjacents,
                  TriangleBoard.adjacent_coord,
                  TriangleBoard.direction_to_border,
                  TriangleBoard.coordinates,
                  TriangleBoard.auto_size,
                  TriangleBoard.offset,
                  TriangleBoard.tile_center,
                  TriangleBoard.tile_at_coord,
                  TriangleBoard.from_point
                ],
                [
                  NewHexTriangle.Coord,
                  NewHexTriangle.adjacents,
                  NewHexTriangle.adjacent_coord,
                  NewHexTriangle.direction_to_border,
                  NewHexTriangle.coordinates,
                  NewHexTriangle.auto_size,
                  NewHexTriangle.offset,
                  NewHexTriangle.tile_center,
                  NewHexTriangle.tile_at_coord,
                  NewHexTriangle.from_point
                ],
                [
                  NewRect.Coord,
                  NewRect.adjacents,
                  NewRect.adjacent_coord,
                  NewRect.direction_to_border,
                  NewRect.coordinates,
                  NewRect.auto_size,
                  NewRect.offset,
                  NewRect.tile_center,
                  NewRect.tile_at_coord,
                  NewRect.from_point
                ]
              ]);
  };
  var random_alg = function () {
    var $$let = NewDepth.F(NewDepth.RandomConfig(/* module */[]));
    return choose(/* array */[
                [
                  $$let[1],
                  $$let[2],
                  $$let[3],
                  $$let[12],
                  $$let[0],
                  $$let[9],
                  $$let[11],
                  $$let[4]
                ],
                [
                  Random2.edges,
                  Random2.visited,
                  Random2.max_age,
                  Random2.run,
                  Random2.init,
                  Random2.step,
                  Random2.loop_to_end,
                  Random2.finished
                ]
              ]);
  };
  var Board = random_board(/* () */0);
  var Gen = random_alg(/* () */0);
  Paint.F(Board)(Gen);
  var Show$prime = Show.F(Board)(Gen);
  var state = Curry._1(Show$prime[/* init_state */6], options);
  Curry._3(Show$prime[/* loop */8], options, ctx, state);
  ctx.font = "32px monospace";
  ctx.fillStyle = "black";
  ctx.fillText((seed.toString(16)), 5.0, 30.0);
  return seed;
}

exports.random_line = random_line;
exports.random_options = random_options;
exports.run = run;
/* Show Not a pure module */
