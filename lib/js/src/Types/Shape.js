'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Utils = require("../Maze/Utils.js");

function transform(param, scale, shape) {
  var dy = param[1];
  var dx = param[0];
  switch (shape.tag | 0) {
    case 0 : 
        return /* Polyline */Block.__(0, [List.map((function (param) {
                          return /* tuple */[
                                  Utils.Float[/* + */0](Utils.Float[/* * */3](param[0], scale), dx),
                                  Utils.Float[/* + */0](Utils.Float[/* * */3](param[1], scale), dy)
                                ];
                        }), shape[0])]);
    case 1 : 
        var match = shape[0];
        return /* Rect */Block.__(1, [/* tuple */[
                    Utils.Float[/* + */0](Utils.Float[/* * */3](match[0], scale), dx),
                    Utils.Float[/* + */0](Utils.Float[/* * */3](match[1], scale), dy),
                    Utils.Float[/* * */3](match[2], scale),
                    Utils.Float[/* * */3](match[3], scale)
                  ]]);
    case 2 : 
        var match$1 = shape[0];
        var match$2 = match$1[0];
        return /* Arc */Block.__(2, [/* tuple */[
                    /* tuple */[
                      Utils.Float[/* + */0](Utils.Float[/* * */3](match$2[0], scale), dx),
                      Utils.Float[/* + */0](Utils.Float[/* * */3](match$2[1], scale), dy)
                    ],
                    Utils.Float[/* * */3](match$1[1], scale),
                    Utils.Float[/* * */3](match$1[2], scale),
                    match$1[3],
                    match$1[4]
                  ]]);
    case 3 : 
        var match$3 = shape[0];
        var match$4 = match$3[0];
        return /* Circle */Block.__(3, [/* tuple */[
                    /* tuple */[
                      Utils.Float[/* + */0](Utils.Float[/* * */3](match$4[0], scale), dx),
                      Utils.Float[/* + */0](Utils.Float[/* * */3](match$4[1], scale), dy)
                    ],
                    Utils.Float[/* * */3](match$3[1], scale)
                  ]]);
    
  }
}

exports.transform = transform;
/* No side effect */
