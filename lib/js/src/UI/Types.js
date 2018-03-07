'use strict';

var Circle = require("../Boards/Circle.js");
var HexBox = require("../Boards/HexBox.js");
var HexHex = require("../Boards/HexHex.js");
var NewBFS = require("../Algorithms/NewBFS.js");
var Coord2d = require("../Coords/Coord2d.js");
var NewRect = require("../Boards/NewRect.js");
var Random2 = require("../Algorithms/Random2.js");
var NewDepth = require("../Algorithms/NewDepth.js");
var FourSquare = require("../Boards/FourSquare.js");
var TriangleBoard = require("../Boards/TriangleBoard.js");
var NewHexTriangle = require("../Boards/NewHexTriangle.js");
var SquareTriangle = require("../Boards/SquareTriangle.js");

var all = /* array */[
  /* Circle */0,
  /* HexBox */1,
  /* Hexagon */2,
  /* Triangle */3,
  /* HexTriangle */4,
  /* Rect */7,
  /* SquareTriangle */5,
  /* FourSquare */6
];

function tomod(board) {
  switch (board) {
    case 0 : 
        return [
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
              ];
    case 1 : 
        return [
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
              ];
    case 2 : 
        return [
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
              ];
    case 3 : 
        return [
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
              ];
    case 4 : 
        return [
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
              ];
    case 5 : 
        return [
                SquareTriangle.Coord,
                SquareTriangle.adjacents,
                SquareTriangle.adjacent_coord,
                SquareTriangle.direction_to_border,
                SquareTriangle.coordinates,
                SquareTriangle.auto_size,
                SquareTriangle.offset,
                SquareTriangle.tile_center,
                SquareTriangle.tile_at_coord,
                SquareTriangle.from_point
              ];
    case 6 : 
        return [
                FourSquare.Coord,
                FourSquare.adjacents,
                FourSquare.adjacent_coord,
                FourSquare.direction_to_border,
                FourSquare.coordinates,
                FourSquare.auto_size,
                FourSquare.offset,
                FourSquare.tile_center,
                FourSquare.tile_at_coord,
                FourSquare.from_point
              ];
    case 7 : 
        return [
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
              ];
    
  }
}

function name(board) {
  switch (board) {
    case 0 : 
        return "Circle";
    case 1 : 
        return "HexBox";
    case 2 : 
        return "Hexagon";
    case 3 : 
        return "Triangle";
    case 4 : 
        return "HexTriangle";
    case 5 : 
        return "SquareTriangle";
    case 6 : 
        return "FourSquare";
    case 7 : 
        return "Rect";
    
  }
}

function by_name(name) {
  switch (name) {
    case "Circle" : 
        return /* Some */[/* Circle */0];
    case "FourSquare" : 
        return /* Some */[/* FourSquare */6];
    case "HexBox" : 
        return /* Some */[/* HexBox */1];
    case "HexTriangle" : 
        return /* Some */[/* HexTriangle */4];
    case "Hexagon" : 
        return /* Some */[/* Hexagon */2];
    case "Rect" : 
        return /* Some */[/* Rect */7];
    case "SquareTriangle" : 
        return /* Some */[/* SquareTriangle */5];
    case "Triangle" : 
        return /* Some */[/* Triangle */3];
    default:
      return /* None */0;
  }
}

var Board = /* module */[
  /* all */all,
  /* tomod */tomod,
  /* name */name,
  /* by_name */by_name
];

var all$1 = /* int array */[
  /* DFS */0,
  /* BFS */1,
  /* Random */2
];

function tomod$1(alg) {
  switch (alg) {
    case 0 : 
        var $$let = NewDepth.F(NewDepth.RandomConfig(/* module */[]));
        return [
                $$let[1],
                $$let[2],
                $$let[3],
                $$let[12],
                $$let[0],
                $$let[9],
                $$let[11],
                $$let[4]
              ];
    case 1 : 
        return [
                NewBFS.edges,
                NewBFS.visited,
                NewBFS.max_age,
                NewBFS.run,
                NewBFS.init,
                NewBFS.step,
                NewBFS.loop_to_end,
                NewBFS.finished
              ];
    case 2 : 
        return [
                Random2.edges,
                Random2.visited,
                Random2.max_age,
                Random2.run,
                Random2.init,
                Random2.step,
                Random2.loop_to_end,
                Random2.finished
              ];
    
  }
}

function name$1(alg) {
  switch (alg) {
    case 0 : 
        return "DFS";
    case 1 : 
        return "BFS";
    case 2 : 
        return "Random";
    
  }
}

function by_name$1(name) {
  switch (name) {
    case "BFS" : 
        return /* Some */[/* BFS */1];
    case "DFS" : 
        return /* Some */[/* DFS */0];
    case "Random" : 
        return /* Some */[/* Random */2];
    default:
      return /* None */0;
  }
}

var Alg = /* module */[
  /* all */all$1,
  /* tomod */tomod$1,
  /* name */name$1,
  /* by_name */by_name$1
];

exports.Board = Board;
exports.Alg = Alg;
/* Circle Not a pure module */
