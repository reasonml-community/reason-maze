'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Aphrodite = require("aphrodite");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

var get = (
  function (styles, name) {
    return styles[name]
  }
);

function css(styles, name) {
  return Aphrodite.css(Curry._2(get, styles, name));
}

function csss(styles, names) {
  return Aphrodite.css(Belt_Array.map(names, Curry._1(get, styles)));
}

function create(v) {
  return Aphrodite.StyleSheet.create(v);
}

exports.get = get;
exports.css = css;
exports.csss = csss;
exports.create = create;
/* get Not a pure module */
