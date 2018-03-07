'use strict';

var $$Set = require("bs-platform/lib/js/set.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");

var compare = Caml_obj.caml_compare;

var PairSet = $$Set.Make(/* module */[/* compare */compare]);

exports.PairSet = PairSet;
/* PairSet Not a pure module */
