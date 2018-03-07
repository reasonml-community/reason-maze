'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Canvas = require("../FFI/Canvas.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function hsl(h, s, l) {
  return "hsl(" + (Pervasives.string_of_int(h) + (", " + (Pervasives.string_of_int(s) + ("%, " + (Pervasives.string_of_int(l) + "%)")))));
}

function hslf(h, s, l) {
  return "hsl(" + (String(h) + (", " + (String(s) + ("%, " + (String(l) + "%)")))));
}

function F() {
  return (function () {
      var draw_wall = function (ctx, param, wall) {
        var ym = param[1];
        var xm = param[0];
        if (wall.tag) {
          var match = wall[0];
          var match$1 = match[1];
          var match$2 = match[0];
          return Canvas.Ctx[/* line */3](ctx, /* tuple */[
                      match$2[0] + xm,
                      match$2[1] + ym
                    ], /* tuple */[
                      match$1[0] + xm,
                      match$1[1] + ym
                    ]);
        } else {
          var match$3 = wall[0];
          ctx.beginPath();
          ctx.arc(match$3[0] + xm, match$3[1] + ym, match$3[2], match$3[3], match$3[4]);
          ctx.stroke();
          return /* () */0;
        }
      };
      var draw_walli = function (ctx, param, i, wall) {
        var ym = param[1];
        var xm = param[0];
        draw_wall(ctx, /* tuple */[
              xm,
              ym
            ], wall);
        var txt = Pervasives.string_of_int(i);
        if (wall.tag) {
          var match = wall[0];
          var match$1 = match[1];
          var match$2 = match[0];
          var cx = (match$1[0] + match$2[0]) * 0.5 + xm;
          var cy = (match$1[1] + match$2[1]) * 0.5 + ym;
          ctx.fillStyle = "black";
          ctx.fillText(txt, cx, cy);
          return /* () */0;
        } else {
          var match$3 = wall[0];
          var r = match$3[2];
          var ct = (match$3[3] + match$3[4]) / 2.0;
          var dx = r * Math.cos(ct);
          var dy = r * Math.sin(ct);
          ctx.fillStyle = "black";
          ctx.fillText(txt, match$3[0] + dx + xm, match$3[1] + dy + ym);
          return /* () */0;
        }
      };
      var center = function (pts) {
        var tx = [0.0];
        var ty = [0.0];
        var c = [0];
        Belt_List.forEach(pts, (function (param) {
                tx[0] += param[0];
                ty[0] += param[1];
                c[0] = c[0] + 1 | 0;
                return /* () */0;
              }));
        return /* tuple */[
                tx[0] / c[0],
                ty[0] / c[0]
              ];
      };
      var $pipe$pipe$great = function (param, b) {
        return Curry._2(b, param[0], param[1]);
      };
      var polar = function (r, t) {
        return /* tuple */[
                r * Math.cos(t),
                r * Math.sin(t)
              ];
      };
      var offset = function (param, a, b) {
        return /* tuple */[
                param[0] + a,
                param[1] + b
              ];
      };
      var draw_shape = function (ctx, param, get_color, current_age, max_age, param$1) {
        var age = param$1[1];
        var shape = param$1[0];
        var ym = param[1];
        var xm = param[0];
        if (age) {
          ctx.fillStyle = Curry._2(get_color, age / current_age, age / max_age);
        } else {
          ctx.fillStyle = "white";
        }
        switch (shape.tag | 0) {
          case 0 : 
              var pts = shape[0];
              if (pts) {
                var match = pts[0];
                ctx.beginPath();
                ctx.moveTo(match[0] + xm, match[1] + ym);
                Belt_List.forEach(pts[1], (function (param) {
                        ctx.lineTo(param[0] + xm, param[1] + ym);
                        return /* () */0;
                      }));
                ctx.fill();
                return /* () */0;
              } else {
                return /* () */0;
              }
              break;
          case 1 : 
              var match$1 = shape[0];
              ctx.fillRect(match$1[0] + xm, match$1[1] + ym, match$1[2], match$1[3]);
              return /* () */0;
          case 2 : 
              var match$2 = shape[0];
              var t2 = match$2[4];
              var t1 = match$2[3];
              var y2 = match$2[2];
              var y1 = match$2[1];
              var match$3 = match$2[0];
              var cy = match$3[1];
              var cx = match$3[0];
              ctx.beginPath();
              var partial_arg_000 = cx + xm;
              var partial_arg_001 = cy + ym;
              var partial_arg = /* tuple */[
                partial_arg_000,
                partial_arg_001
              ];
              $pipe$pipe$great($pipe$pipe$great(polar(y1, t1), (function (param, param$1) {
                          return offset(partial_arg, param, param$1);
                        })), (function (param, param$1) {
                      ctx.moveTo(param, param$1);
                      return /* () */0;
                    }));
              ctx.arc(cx + xm, cy + ym, y1, t1, t2);
              var partial_arg_000$1 = cx + xm;
              var partial_arg_001$1 = cy + ym;
              var partial_arg$1 = /* tuple */[
                partial_arg_000$1,
                partial_arg_001$1
              ];
              $pipe$pipe$great($pipe$pipe$great(polar(y2, t2), (function (param, param$1) {
                          return offset(partial_arg$1, param, param$1);
                        })), (function (param, param$1) {
                      ctx.lineTo(param, param$1);
                      return /* () */0;
                    }));
              ctx.arc(cx + xm, cy + ym, y2, t2, t1, true);
              ctx.fill();
              return /* () */0;
          case 3 : 
              var match$4 = shape[0];
              var match$5 = match$4[0];
              return Canvas.Ctx[/* circle */0](ctx, match$5[0] + xm, match$5[1] + ym, match$4[1]);
          
        }
      };
      var draw_shapei = function (ctx, param, get_color, current_age, max_age, i, param$1) {
        var shape = param$1[0];
        var ym = param[1];
        var xm = param[0];
        draw_shape(ctx, /* tuple */[
              xm,
              ym
            ], get_color, current_age, max_age, /* tuple */[
              shape,
              param$1[1]
            ]);
        ctx.fillStyle = "black";
        var txt = Pervasives.string_of_int(i);
        switch (shape.tag | 0) {
          case 0 : 
              var match = center(shape[0]);
              ctx.fillText(txt, match[0] + xm, match[1] + ym);
              return /* () */0;
          case 1 : 
              var match$1 = shape[0];
              ctx.fillText(txt, match$1[0] + xm + match$1[2] / 2.0, match$1[1] + ym + match$1[3] / 2.0);
              return /* () */0;
          case 2 : 
              var match$2 = shape[0];
              var match$3 = match$2[0];
              var r = (match$2[1] + match$2[2]) / 2.0;
              var ct = (match$2[3] + match$2[4]) / 2.0;
              var dx = r * Math.cos(ct);
              var dy = r * Math.sin(ct);
              ctx.fillStyle = "black";
              ctx.fillText(txt, match$3[0] + dx + xm, match$3[1] + dy + ym);
              return /* () */0;
          case 3 : 
              var match$4 = shape[0][0];
              ctx.fillText(txt, match$4[0] + xm, match$4[1] + ym);
              return /* () */0;
          
        }
      };
      var draw_edge = function (ctx, param, param$1) {
        var match = param$1[1];
        var match$1 = param$1[0];
        var ym = param[1];
        var xm = param[0];
        return Canvas.Ctx[/* line */3](ctx, /* tuple */[
                    match$1[0] + xm,
                    match$1[1] + ym
                  ], /* tuple */[
                    match[0] + xm,
                    match[1] + ym
                  ]);
      };
      return /* module */[
              /* draw_wall */draw_wall,
              /* draw_walli */draw_walli,
              /* center */center,
              /* ||> */$pipe$pipe$great,
              /* polar */polar,
              /* offset */offset,
              /* draw_shape */draw_shape,
              /* draw_shapei */draw_shapei,
              /* draw_edge */draw_edge
            ];
    });
}

var Ctx = 0;

exports.Ctx = Ctx;
exports.hsl = hsl;
exports.hslf = hslf;
exports.F = F;
/* Canvas Not a pure module */
