'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Canvas = require("../FFI/Canvas.js");
var Manager = require("./Manager.js");
var Generator = require("../Types/Generator.js");
var Presenter = require("./Presenter.js");

function iof(prim) {
  return prim | 0;
}

var Options = /* module */[];

function F(Board) {
  return (function (Gen) {
      var Man = Manager.F(Board)(Gen);
      var Presenter$1 = Presenter.F(Board)(Gen);
      var show = function (ctx, options, state) {
        var match = options[/* canvas_size */0];
        var height = match[1];
        var width = match[0];
        ctx.lineCap = "round";
        ctx.fillStyle = "white";
        ctx.fillRect(0.0, 0.0, width, height);
        var match$1 = state[/* outsize */3];
        var xm = (width - match$1[0]) / 2.0;
        var ym = (height - match$1[1]) / 2.0;
        var match$2 = options[/* draw_shapes */5];
        if (match$2) {
          $$Array.iter(Curry._5(Presenter$1[/* draw_shape */6], ctx, /* tuple */[
                    xm,
                    ym
                  ], match$2[0], Curry._1(Man[/* current_age */9], state), Curry._1(Man[/* max_age */8], state)), Curry._1(Man[/* all_shapes */11], state));
        }
        var match$3 = options[/* draw_edges */3];
        if (match$3) {
          var match$4 = match$3[0];
          ctx.lineWidth = match$4[0];
          ctx.strokeStyle = match$4[1];
          var edges = Curry._1(Man[/* all_edges */10], state);
          List.iter(Curry._2(Presenter$1[/* draw_edge */8], ctx, /* tuple */[
                    xm,
                    ym
                  ]), edges);
        }
        var match$5 = options[/* draw_walls */4];
        if (match$5) {
          var match$6 = match$5[0];
          ctx.lineWidth = match$6[0];
          ctx.strokeStyle = match$6[1];
          var walls = Curry._1(Man[/* all_walls */12], state);
          return List.iter(Curry._2(Presenter$1[/* draw_wall */0], ctx, /* tuple */[
                          xm,
                          ym
                        ]), walls);
        } else {
          return /* () */0;
        }
      };
      var show_debug = function (ctx, options, state) {
        var match = options[/* canvas_size */0];
        var height = match[1];
        var width = match[0];
        console.log(state);
        ctx.lineCap = "round";
        ctx.clearRect(0.0, 0.0, width, height);
        var match$1 = state[/* outsize */3];
        var h = match$1[1];
        var w = match$1[0];
        var xm = (width - w) / 2.0;
        var ym = (height - h) / 2.0;
        console.log(/* tuple */[
              w,
              h,
              width,
              height,
              xm,
              ym
            ]);
        var edges = Curry._1(Man[/* edges */7], state);
        Curry._2(Generator.PairSet[/* iter */12], (function (param) {
                console.log(/* tuple */[
                      param[0],
                      param[1]
                    ]);
                return /* () */0;
              }), edges);
        var walls = Curry._1(Man[/* all_walls */12], state);
        console.log(/* tuple */[
              "walls",
              $$Array.of_list(walls)
            ]);
        var match$2 = options[/* draw_shapes */5];
        if (match$2) {
          $$Array.iteri(Curry._5(Presenter$1[/* draw_shapei */7], ctx, /* tuple */[
                    xm,
                    ym
                  ], match$2[0], Curry._1(Man[/* current_age */9], state), Curry._1(Man[/* max_age */8], state)), Curry._1(Man[/* all_shapes */11], state));
        }
        var match$3 = options[/* draw_edges */3];
        if (match$3) {
          var match$4 = match$3[0];
          ctx.lineWidth = match$4[0];
          ctx.strokeStyle = match$4[1];
          List.iter(Curry._2(Presenter$1[/* draw_edge */8], ctx, /* tuple */[
                    xm,
                    ym
                  ]), Curry._1(Man[/* all_edges */10], state));
        }
        var match$5 = options[/* draw_walls */4];
        if (match$5) {
          var match$6 = match$5[0];
          ctx.lineWidth = match$6[0];
          ctx.strokeStyle = match$6[1];
          var walls$1 = Curry._1(Man[/* all_walls */12], state);
          console.log(walls$1);
          console.log("hi");
          return List.iteri(Curry._2(Presenter$1[/* draw_walli */1], ctx, /* tuple */[
                          xm,
                          ym
                        ]), walls$1);
        } else {
          return /* () */0;
        }
      };
      var batch = function (_state, _n) {
        while(true) {
          var n = _n;
          var state = _state;
          if (n) {
            _n = n - 1 | 0;
            _state = Curry._1(Man[/* step */4], state);
            continue ;
            
          } else {
            return state;
          }
        };
      };
      var animate = function (ctx, batch_size, interval, options, state, onStop) {
        console.log("animate");
        var id = [0];
        var inner = function (state) {
          var state$1 = batch(state, batch_size);
          show(ctx, options, state$1);
          var match = Curry._1(Man[/* finished */6], state$1);
          if (match !== 0) {
            return Curry._1(onStop, /* () */0);
          } else {
            id[0] = setTimeout((function () {
                    return inner(state$1);
                  }), interval);
            return /* () */0;
          }
        };
        inner(state);
        return id;
      };
      var init_state = function (param) {
        var canvas_size = param[/* canvas_size */0];
        var min_margin = param[/* min_margin */1];
        var with_margins_000 = canvas_size[0] - min_margin * 2.0;
        var with_margins_001 = canvas_size[1] - min_margin * 2.0;
        var with_margins = /* tuple */[
          with_margins_000,
          with_margins_001
        ];
        return Curry._2(Man[/* init */3], with_margins, param[/* size_hint */2]);
      };
      var init = function (options) {
        var match = options[/* canvas_size */0];
        var canvas = Curry._2(Canvas.createOnBody, match[0] | 0, match[1] | 0);
        var ctx = canvas.getContext("2d");
        return /* tuple */[
                canvas,
                ctx,
                init_state(options)
              ];
      };
      var loop = function (options, ctx, state) {
        return show(ctx, options, Curry._1(Man[/* loop_to_end */5], state));
      };
      var loop_debug = function (options, ctx, state) {
        return show_debug(ctx, options, Curry._1(Man[/* loop_to_end */5], state));
      };
      return /* module */[
              /* Man */Man,
              /* Presenter */Presenter$1,
              /* show */show,
              /* show_debug */show_debug,
              /* batch */batch,
              /* animate */animate,
              /* init_state */init_state,
              /* init */init,
              /* loop */loop,
              /* loop_debug */loop_debug
            ];
    });
}

exports.iof = iof;
exports.Options = Options;
exports.F = F;
/* Canvas Not a pure module */
