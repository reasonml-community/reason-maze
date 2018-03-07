'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Random = require("bs-platform/lib/js/random.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");

function maybe(f, n) {
  if (n) {
    return /* Some */[Curry._1(f, n[0])];
  } else {
    return /* None */0;
  }
}

function shuffle(d) {
  var nd = List.map((function (c) {
          return /* tuple */[
                  Random.bits(/* () */0),
                  c
                ];
        }), d);
  var sond = List.sort(Caml_obj.caml_compare, nd);
  return List.map((function (prim) {
                return prim[1];
              }), sond);
}

function $plus(t, t$prime) {
  return t + t$prime;
}

function $neg(t, t$prime) {
  return t - t$prime;
}

function $slash(t, t$prime) {
  return t / t$prime;
}

function $star(t, t$prime) {
  return t * t$prime;
}

var Float = /* module */[
  /* + */$plus,
  /* - */$neg,
  /* / */$slash,
  /* * */$star
];

exports.maybe = maybe;
exports.shuffle = shuffle;
exports.Float = Float;
/* No side effect */
