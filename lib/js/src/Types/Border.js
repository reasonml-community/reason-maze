'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Utils = require("../Maze/Utils.js");

function transform(scale, param, t) {
  var dy = param[1];
  var dx = param[0];
  if (t.tag) {
    var match = t[0];
    var match$1 = match[1];
    var match$2 = match[0];
    return /* Line */Block.__(1, [/* tuple */[
                /* tuple */[
                  Utils.Float[/* + */0](Utils.Float[/* * */3](match$2[0], scale), dx),
                  Utils.Float[/* + */0](Utils.Float[/* * */3](match$2[1], scale), dy)
                ],
                /* tuple */[
                  Utils.Float[/* + */0](Utils.Float[/* * */3](match$1[0], scale), dx),
                  Utils.Float[/* + */0](Utils.Float[/* * */3](match$1[1], scale), dy)
                ]
              ]]);
  } else {
    var match$3 = t[0];
    return /* Arc */Block.__(0, [/* tuple */[
                Utils.Float[/* + */0](Utils.Float[/* * */3](match$3[0], scale), dx),
                Utils.Float[/* + */0](Utils.Float[/* * */3](match$3[1], scale), dy),
                Utils.Float[/* * */3](match$3[2], scale),
                match$3[3],
                match$3[4]
              ]]);
  }
}

exports.transform = transform;
/* No side effect */
