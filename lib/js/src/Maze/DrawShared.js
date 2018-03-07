'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var Canvas = require("../FFI/Canvas.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function hsla(h, s, l, a) {
  return "hsla(" + (Pervasives.string_of_int(h) + (", " + (Pervasives.string_of_int(s) + ("%, " + (Pervasives.string_of_int(l) + ("%, " + (Pervasives.string_of_float(a) + ")")))))));
}

function draw_point(ctx, count, age, dot_color, size, param) {
  ctx.fillStyle = Curry._2(dot_color, age, count);
  ctx.beginPath();
  Canvas.Ctx[/* circle */0](ctx, param[0], param[1], size);
  ctx.fill();
  return /* () */0;
}

function dotColor(age, total_age) {
  return hsla(0, 100, Caml_int32.div(Caml_int32.imul(100, total_age - age | 0), total_age), 0.3);
}

var Default = /* module */[
  /* unvisitedFill : None */0,
  /* showTrails : true */1,
  /* batch */1,
  /* wallColor */"rgb(100, 100, 100)",
  /* showEdge : true */1,
  /* showWalls : true */1,
  /* showAge : false */0,
  /* dotColor */dotColor,
  /* dotSize */15.0,
  /* edgeDotSize */5.0
];

function Draw(Board) {
  return (function (Config) {
      var draw_wall = function (ctx, wall) {
        var match = wall[0];
        return Canvas.Ctx[/* line */3](ctx, match[0], match[1]);
      };
      var draw_walls = function (ctx, bsize, csize, walls) {
        return Belt_List.forEach(walls, (function (wall) {
                      Utils.maybe((function (param) {
                              return draw_wall(ctx, param);
                            }), Curry._3(Board[/* drawable_wall */3], wall, bsize, csize));
                      return /* () */0;
                    }));
      };
      var vertex_dots = function (ctx, bsize, csize, vertices, size) {
        return Belt_List.forEach(vertices, (function (vertex) {
                      var match = Curry._3(Board[/* vertex_pos */2], vertex, bsize, csize);
                      ctx.beginPath();
                      Canvas.Ctx[/* circle */0](ctx, match[0], match[1], size);
                      ctx.fill();
                      return /* () */0;
                    }));
      };
      var dots = function (ctx, bsize, csize, traveled, total_age, dot_color, size) {
        return Belt_List.forEach(traveled, (function (param) {
                      return draw_point(ctx, total_age, param[/* age */2], dot_color, size, Curry._3(Board[/* vertex_pos */2], param[/* dest */1], bsize, csize));
                    }));
      };
      var paths = function (ctx, bsize, csize, traveled) {
        return Belt_List.forEach(traveled, (function (param) {
                      var a = Curry._3(Board[/* vertex_pos */2], param[/* src */0], bsize, csize);
                      var b = Curry._3(Board[/* vertex_pos */2], param[/* dest */1], bsize, csize);
                      return Canvas.Ctx[/* line */3](ctx, a, b);
                    }));
      };
      var connections = function (ctx, bsize, csize, adjacent) {
        return Belt_List.forEach(adjacent, (function (param) {
                      var a = Curry._3(Board[/* vertex_pos */2], param[0], bsize, csize);
                      var b = Curry._3(Board[/* vertex_pos */2], param[1], bsize, csize);
                      return Canvas.Ctx[/* line */3](ctx, a, b);
                    }));
      };
      var draw = function (ctx, bsize, csize, walls, traveled, current, next) {
        var hsize = csize[1];
        var wsize = csize[0];
        ctx.clearRect(0.0, 0.0, wsize, hsize);
        if (Config[/* showWalls */5]) {
          ctx.strokeStyle = Config[/* wallColor */2];
          ctx.strokeRect(0.0, 0.0, wsize, hsize);
          draw_walls(ctx, bsize, csize, walls);
          var __x = Curry._2(Board[/* border_walls */4], bsize, csize);
          Belt_List.forEach(__x, (function (param) {
                  return draw_wall(ctx, param);
                }));
        }
        if (Config[/* showTrails */1]) {
          ctx.strokeStyle = "rgb(200, 200, 200)";
          paths(ctx, bsize, csize, traveled);
        }
        if (Config[/* showAge */6]) {
          dots(ctx, bsize, csize, traveled, Curry._1(Board[/* Shape */0][/* vertex_count */3], bsize), Config[/* dotColor */7], Config[/* dotSize */8]);
        }
        if (Config[/* showEdge */4]) {
          ctx.fillStyle = "green";
          vertex_dots(ctx, bsize, csize, current, Config[/* edgeDotSize */9]);
          ctx.fillStyle = "blue";
          return vertex_dots(ctx, bsize, csize, next, Config[/* edgeDotSize */9]);
        } else {
          return 0;
        }
      };
      return /* module */[
              /* draw_wall */draw_wall,
              /* draw_walls */draw_walls,
              /* vertex_dots */vertex_dots,
              /* dots */dots,
              /* paths */paths,
              /* connections */connections,
              /* draw */draw
            ];
    });
}

var Ctx = 0;

var sf = Pervasives.string_of_float;

var si = Pervasives.string_of_int;

exports.Ctx = Ctx;
exports.sf = sf;
exports.si = si;
exports.hsla = hsla;
exports.draw_point = draw_point;
exports.Default = Default;
exports.Draw = Draw;
/* Canvas Not a pure module */
