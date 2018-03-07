'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Aphrodite = require("aphrodite");

var get = (
  function (styles, name) {
    return styles[name]
  }
);

function css(styles, name) {
  return Aphrodite.css(Curry._2(get, styles, name));
}

function csss(styles, names) {
  return Aphrodite.css($$Array.map(Curry._1(get, styles), names));
}

function create(v) {
  return Aphrodite.StyleSheet.create(v);
}

exports.get = get;
exports.css = css;
exports.csss = csss;
exports.create = create;
/* get Not a pure module */
