'use strict';

var Show = require("./Maze/Show.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Paint = require("./Maze/Paint.js");
var Canvas = require("./FFI/Canvas.js");
var HexBox = require("./Boards/HexBox.js");
var Builder = require("./UI/Builder.js");
var Random2 = require("./Algorithms/Random2.js");
var Presenter = require("./Maze/Presenter.js");
var RandomMaze = require("./Maze/RandomMaze.js");

function free_hand() {
  var options_000 = /* canvas_size : tuple */[
    1000.0,
    1000.0
  ];
  var options_004 = /* draw_walls : Some */[/* tuple */[
      1.0,
      "#ccc"
    ]];
  var options_005 = /* draw_shapes : Some */[(function (current, _) {
        return Presenter.hslf(0.0, 100.0, current * 100.0);
      })];
  var options = /* record */[
    options_000,
    /* min_margin */50.0,
    /* size_hint */40,
    /* draw_edges : None */0,
    options_004,
    options_005
  ];
  var Paint$prime = Paint.F([
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
        ])([
        Random2.edges,
        Random2.visited,
        Random2.max_age,
        Random2.run,
        Random2.init,
        Random2.step,
        Random2.loop_to_end,
        Random2.finished
      ]);
  Show.F([
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
        ])([
        Random2.edges,
        Random2.visited,
        Random2.max_age,
        Random2.run,
        Random2.init,
        Random2.step,
        Random2.loop_to_end,
        Random2.finished
      ]);
  return Curry._1(Paint$prime[/* paint */6], options);
}

function generate_random() {
  var canvas = Curry._2(Canvas.createOnBody, 1000, 1000);
  var ctx = canvas.getContext("2d");
  return RandomMaze.run(ctx, /* tuple */[
              1000.0,
              1000.0
            ]);
}

Builder.run(/* () */0);

exports.free_hand = free_hand;
exports.generate_random = generate_random;
/*  Not a pure module */
