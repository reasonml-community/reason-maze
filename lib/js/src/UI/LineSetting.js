'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Range = require("./Range.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

function se(prim) {
  return prim;
}

var component = ReasonReact.statelessComponent("LineSetting");

function make(value, onChange, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      var match = value ? value[0] : /* tuple */[
          0,
          20
        ];
      var color = match[1];
      var width = match[0];
      return React.createElement("div", undefined, "Width: ", Pervasives.string_of_int(width), ReasonReact.element(/* None */0, /* None */0, Range.make(0, 30, width, 1.0, 150, 20, /* false */0, (function (x) {
                            var match = +(x === 0);
                            return Curry._1(onChange, match !== 0 ? /* None */0 : /* Some */[/* tuple */[
                                            x,
                                            color
                                          ]]);
                          }), /* array */[])), "Lightness: ", Pervasives.string_of_int(color), ReasonReact.element(/* None */0, /* None */0, Range.make(0, 100, color, 1.0, 150, 20, /* false */0, (function (x) {
                            return Curry._1(onChange, /* Some */[/* tuple */[
                                          width,
                                          x
                                        ]]);
                          }), /* array */[])));
    });
  return newrecord;
}

var si = Pervasives.string_of_int;

exports.se = se;
exports.si = si;
exports.component = component;
exports.make = make;
/* component Not a pure module */
