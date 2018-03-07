'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Aphrodite = require("../FFI/Aphrodite.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");
var SelectableButton = require("./SelectableButton.js");

function se(prim) {
  return prim;
}

var component = ReasonReact.statelessComponent("Buttons");

var styles = Aphrodite.create({
      container: {
        display: "flex",
        "align-items": "stretch",
        border: "1px solid #aaa",
        margin: 5,
        "align-self": "stretch"
      }
    });

function className(is_current) {
  return Aphrodite.csss(styles, /* array */[
              "button",
              is_current !== 0 ? "selected" : "nonselected"
            ]);
}

function make(options, get_title, current, on_change, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", {
                  className: Aphrodite.css(styles, "container")
                }, Belt_Array.map(options, (function (option) {
                        return ReasonReact.element(/* Some */[Curry._1(get_title, option)], /* None */0, SelectableButton.make(Curry._1(get_title, option), +(current === option), (function () {
                                          return Curry._1(on_change, option);
                                        }), /* array */[]));
                      })));
    });
  return newrecord;
}

var si = Pervasives.string_of_int;

exports.se = se;
exports.si = si;
exports.component = component;
exports.styles = styles;
exports.className = className;
exports.make = make;
/* component Not a pure module */
