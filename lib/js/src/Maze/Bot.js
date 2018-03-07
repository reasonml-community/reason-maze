'use strict';

var Fs = require("fs");
var Canvas = require("canvas");
var RandomMaze = require("./RandomMaze.js");

function main() {
  var canvas = new Canvas(1000, 1000);
  var ctx = canvas.getContext("2d");
  RandomMaze.run(ctx, /* tuple */[
        1000.0,
        1000.0
      ]);
  Fs.writeFileSync("./out.png", canvas.toBuffer());
  return /* () */0;
}

main(/* () */0);

exports.main = main;
/*  Not a pure module */
