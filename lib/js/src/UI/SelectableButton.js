'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Aphrodite = require("../FFI/Aphrodite.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

function se(prim) {
  return prim;
}

function si(prim) {
  return String(prim);
}

var component = ReasonReact.statelessComponent("SelectableButton");

var styles = Aphrodite.create({
      button: {
        "background-color": "white",
        border: "none",
        padding: "5px 20px",
        cursor: "pointer",
        outline: "none",
        ":hover": {
          "background-color": "#eee"
        }
      },
      selected: {
        "background-color": "#aaa"
      }
    });

function className(is_current) {
  return Aphrodite.csss(styles, /* array */[
              "button",
              is_current !== 0 ? "selected" : "nonselected"
            ]);
}

function make(title, selected, onClick, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("button", {
                  className: className(selected),
                  onClick: (function () {
                      return Curry._1(onClick, /* () */0);
                    })
                }, title);
    });
  return newrecord;
}

exports.se = se;
exports.si = si;
exports.component = component;
exports.styles = styles;
exports.className = className;
exports.make = make;
/* component Not a pure module */
