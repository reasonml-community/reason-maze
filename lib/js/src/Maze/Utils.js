'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Random = require("bs-platform/lib/js/random.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");

function maybe(f, n) {
  if (n) {
    return /* Some */[Curry._1(f, n[0])];
  } else {
    return /* None */0;
  }
}

function shuffle(d) {
  var nd = Belt_List.map(d, (function (c) {
          return /* tuple */[
                  Random.bits(/* () */0),
                  c
                ];
        }));
  var sond = List.sort(Caml_obj.caml_compare, nd);
  return Belt_List.map(sond, (function (prim) {
                return prim[1];
              }));
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
