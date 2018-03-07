'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Range = require("./Range.js");
var Types = require("./Types.js");
var React = require("react");
var Styles = require("./Styles.js");
var Options = require("./Options.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ColorSlider = require("./ColorSlider.js");
var LineSetting = require("./LineSetting.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");
var SelectableButton = require("./SelectableButton.js");

function se(prim) {
  return prim;
}

var component = ReasonReact.statelessComponent("Title");

function make(children) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", {
                  style: {
                    fontWeight: "bold",
                    padding: "15px 0px 5px",
                    alignSelf: "flex-start"
                  }
                }, children);
    });
  return newrecord;
}

var Title = /* module */[
  /* component */component,
  /* make */make
];

var component$1 = ReasonReact.statelessComponent("Settings");

function compose(fn1, fn2, arg) {
  return Curry._1(fn1, Curry._1(fn2, arg));
}

function set_board(settings, board) {
  var newrecord = settings.slice();
  newrecord[/* board */0] = board;
  return newrecord;
}

function set_alg(settings, algorithm) {
  var newrecord = settings.slice();
  newrecord[/* algorithm */1] = algorithm;
  return newrecord;
}

function set_size_hint(settings, size_hint) {
  var newrecord = settings.slice();
  newrecord[/* size_hint */6] = size_hint;
  return newrecord;
}

function set_fill(settings, fill) {
  var newrecord = settings.slice();
  newrecord[/* fill */2] = /* HueSat */[fill];
  return newrecord;
}

var newSeed = (
  function () {
    return Math.floor(Math.random() * (1 << 30))
  }
);

function make$1(settings, update, _) {
  var newrecord = component$1.slice();
  newrecord[/* render */9] = (function () {
      var match = settings[/* fill */2];
      return React.createElement("div", {
                  className: "settings"
                }, ReasonReact.element(/* None */0, /* None */0, make(/* array */["Animation Speed"])), ReasonReact.element(/* None */0, /* None */0, Range.make(1, 20, settings[/* batch_size */5], 1.0, 150, 20, /* false */0, (function (batch_size) {
                            var newrecord = settings.slice();
                            return Curry._1(update, (newrecord[/* batch_size */5] = batch_size, newrecord));
                          }), /* array */[])), "Canvas Size: ", Pervasives.string_of_int(settings[/* canvas_size */7]), ReasonReact.element(/* None */0, /* None */0, Range.make(300, 1000, settings[/* canvas_size */7], 10.0, 150, 20, /* false */0, (function (canvas_size) {
                            var newrecord = settings.slice();
                            return Curry._1(update, (newrecord[/* canvas_size */7] = canvas_size, newrecord));
                          }), /* array */[])), "Size: ", Pervasives.string_of_int(settings[/* size_hint */6]), ReasonReact.element(/* None */0, /* None */0, Range.make(3, 50, settings[/* size_hint */6], 1.0, 150, 20, /* false */0, (function (param) {
                            return Curry._1(update, set_size_hint(settings, param));
                          }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, make(/* array */["Seed"])), React.createElement("input", {
                      value: Pervasives.string_of_int(settings[/* seed */8])
                    }), React.createElement("button", {
                      style: Styles.button,
                      onClick: (function () {
                          var newrecord = settings.slice();
                          return Curry._1(update, (newrecord[/* seed */8] = Curry._1(newSeed, /* () */0), newrecord));
                        })
                    }, "New Seed"), ReasonReact.element(/* None */0, /* None */0, make(/* array */["Fill color"])), React.createElement("div", {
                      style: {
                        flexDirection: "row"
                      }
                    }, ReasonReact.element(/* None */0, /* None */0, SelectableButton.make("No fill", +(settings[/* fill */2] === /* NoFill */0), (function () {
                                var newrecord = settings.slice();
                                return Curry._1(update, (newrecord[/* fill */2] = /* NoFill */0, newrecord));
                              }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, SelectableButton.make("Rainbow", +(settings[/* fill */2] === /* Rainbow */1), (function () {
                                var newrecord = settings.slice();
                                return Curry._1(update, (newrecord[/* fill */2] = /* Rainbow */1, newrecord));
                              }), /* array */[]))), ReasonReact.element(/* None */0, /* None */0, ColorSlider.make(150, 100, typeof match === "number" ? /* None */0 : /* Some */[match[0]], (function (param) {
                            return Curry._1(update, set_fill(settings, param));
                          }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, make(/* array */["Wall"])), ReasonReact.element(/* None */0, /* None */0, LineSetting.make(settings[/* wall */3], (function (wall) {
                            var newrecord = settings.slice();
                            return Curry._1(update, (newrecord[/* wall */3] = wall, newrecord));
                          }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, make(/* array */["Path"])), ReasonReact.element(/* None */0, /* None */0, LineSetting.make(settings[/* edge */4], (function (edge) {
                            var newrecord = settings.slice();
                            return Curry._1(update, (newrecord[/* edge */4] = edge, newrecord));
                          }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, make(/* array */["Shape"])), ReasonReact.element(/* None */0, /* None */0, Options.make(Types.Board[/* all */0], Types.Board[/* name */2], settings[/* board */0], (function (param) {
                            return Curry._1(update, set_board(settings, param));
                          }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, make(/* array */["Algorithm"])), ReasonReact.element(/* None */0, /* None */0, Options.make(Types.Alg[/* all */0], Types.Alg[/* name */2], settings[/* algorithm */1], (function (param) {
                            return Curry._1(update, set_alg(settings, param));
                          }), /* array */[])));
    });
  return newrecord;
}

var si = Pervasives.string_of_int;

exports.si = si;
exports.se = se;
exports.Title = Title;
exports.component = component$1;
exports.compose = compose;
exports.set_board = set_board;
exports.set_alg = set_alg;
exports.set_size_hint = set_size_hint;
exports.set_fill = set_fill;
exports.newSeed = newSeed;
exports.make = make$1;
/* component Not a pure module */
