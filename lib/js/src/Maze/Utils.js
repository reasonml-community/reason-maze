'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Random = require("bs-platform/lib/js/random.js");
var Belt_Id = require("bs-platform/lib/js/belt_Id.js");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
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

function cmp(param, param$1) {
  var v = Caml_obj.caml_compare(param[0], param$1[0]);
  if (v !== 0) {
    return v;
  } else {
    return Caml_obj.caml_compare(param[1], param$1[1]);
  }
}

var IntPairComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp]);

var intPairSet = Belt_Set.make(IntPairComparator);

exports.maybe = maybe;
exports.shuffle = shuffle;
exports.Float = Float;
exports.IntPairComparator = IntPairComparator;
exports.intPairSet = intPairSet;
/* IntPairComparator Not a pure module */
