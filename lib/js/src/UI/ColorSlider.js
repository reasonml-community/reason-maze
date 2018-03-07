'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Presenter = require("../Maze/Presenter.js");
var ReactDOMRe = require("reason-react/lib/js/src/ReactDOMRe.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

function refToContext(canv) {
  return canv.getContext("2d");
}

function si(prim) {
  return String(prim);
}

function fi(prim) {
  return prim;
}

function iof(prim) {
  return prim | 0;
}

function px(m) {
  return String(m) + "px";
}

function scale(n, max, range) {
  return n / max * range | 0;
}

function render(width, height, canvas) {
  var ctx = canvas.getContext("2d");
  for(var x = 0; x <= width; ++x){
    for(var y = 0; y <= height; ++y){
      var color = Presenter.hsl(scale(x, width, 360), scale(y, height, 100), 50);
      ctx.fillStyle = color;
      ctx.fillRect(x, y, 1.0, 1.0);
    }
  }
  return /* () */0;
}

var component = ReasonReact.reducerComponent("ColorSlider");

function isPressed(evt) {
  return +(evt.buttons === 1);
}

function getValue(evt) {
  return Caml_format.caml_int_of_string(evt.target.value);
}

function elementPos(element) {
  var box = element.getBoundingClientRect();
  var top = box.top;
  var left = box.left;
  return /* tuple */[
          top,
          left
        ];
}

function toValue(width, height, evt, canvas) {
  evt.preventDefault();
  var match = elementPos(canvas);
  var x = evt.clientX - match[1] | 0;
  var y = evt.clientY - match[0] | 0;
  return /* tuple */[
          scale(x, width, 360),
          scale(y, height, 100)
        ];
}

function $great$great$eq(a, b) {
  if (a) {
    return /* Some */[Curry._1(b, a[0])];
  } else {
    return /* None */0;
  }
}

function setCanvasRef(r, param) {
  param[/* state */2][/* canvas */0][0] = (r == null) ? /* None */0 : [r];
  return /* () */0;
}

function make(width, height, value, onChange, _) {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function (param) {
      var match = param[/* state */2][/* canvas */0][0];
      if (match) {
        render(width, height, match[0]);
      }
      return /* NoUpdate */0;
    });
  newrecord[/* render */9] = (function (self) {
      var state = self[/* state */2];
      var tmp;
      if (value) {
        var match = value[0];
        var saturation = match[1];
        var hue = match[0];
        var m = scale(hue, 360, width);
        var m$1 = scale(saturation, 100, height);
        var style = {
          backgroundColor: Presenter.hsl(hue, saturation, 50),
          border: "2px solid black",
          height: "10px",
          left: String(m) + "px",
          marginTop: "-5px",
          marginLeft: "-5px",
          position: "absolute",
          top: String(m$1) + "px",
          width: "10px",
          borderRadius: "5px"
        };
        var style$1 = ReactDOMRe.Style[/* unsafeAddProp */1](style, "pointerEvents", "none");
        tmp = React.createElement("div", {
              style: style$1
            });
      } else {
        tmp = null;
      }
      return React.createElement("div", {
                  style: {
                    position: "relative"
                  }
                }, React.createElement("canvas", {
                      ref: Curry._1(self[/* handle */0], setCanvasRef),
                      height: String(height),
                      width: String(width),
                      onMouseDown: (function (evt) {
                          $great$great$eq($great$great$eq(state[/* canvas */0][0], (function (param) {
                                      return toValue(width, height, evt, param);
                                    })), onChange);
                          return /* () */0;
                        }),
                      onMouseMove: (function (evt) {
                          var match = +(evt.buttons === 1);
                          if (match !== 0) {
                            $great$great$eq($great$great$eq(state[/* canvas */0][0], (function (param) {
                                        return toValue(width, height, evt, param);
                                      })), onChange);
                            return /* () */0;
                          } else {
                            return /* () */0;
                          }
                        })
                    }), tmp);
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[/* canvas */[/* None */0]];
    });
  newrecord[/* reducer */12] = (function (_, _$1) {
      return /* NoUpdate */0;
    });
  return newrecord;
}

exports.refToContext = refToContext;
exports.si = si;
exports.fi = fi;
exports.iof = iof;
exports.px = px;
exports.scale = scale;
exports.render = render;
exports.component = component;
exports.isPressed = isPressed;
exports.getValue = getValue;
exports.elementPos = elementPos;
exports.toValue = toValue;
exports.$great$great$eq = $great$great$eq;
exports.setCanvasRef = setCanvasRef;
exports.make = make;
/* component Not a pure module */
