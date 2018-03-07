'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Types = require("./Types.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Js_null = require("bs-platform/lib/js/js_null.js");
var Presenter = require("../Maze/Presenter.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");

function fill_json(fill) {
  if (typeof fill === "number") {
    if (fill !== 0) {
      return "rainbow";
    } else {
      return "none";
    }
  } else {
    var match = fill[0];
    return /* float array */[
            match[0],
            match[1]
          ];
  }
}

function parse_fill(fill) {
  var match = Js_json.classify(fill);
  if (typeof match === "number") {
    return /* None */0;
  } else {
    switch (match.tag | 0) {
      case 0 : 
          switch (match[0]) {
            case "none" : 
                return /* Some */[/* NoFill */0];
            case "rainbow" : 
                return /* Some */[/* Rainbow */1];
            default:
              return /* None */0;
          }
      case 3 : 
          var match$1 = match[0];
          if (match$1.length !== 2) {
            return /* None */0;
          } else {
            var hue = match$1[0];
            var sat = match$1[1];
            var match$2 = Js_json.classify(hue);
            var match$3 = Js_json.classify(sat);
            if (typeof match$2 === "number" || !(match$2.tag === 1 && !(typeof match$3 === "number" || match$3.tag !== 1))) {
              return /* None */0;
            } else {
              return /* Some */[/* HueSat */[/* tuple */[
                          match$2[0] | 0,
                          match$3[0] | 0
                        ]]];
            }
          }
      default:
        return /* None */0;
    }
  }
}

var T = /* module */[
  /* fill_json */fill_json,
  /* parse_fill */parse_fill
];

function to_jsonable(t) {
  return /* tuple */[
          Types.Board[/* name */2](t[/* board */0]),
          Types.Alg[/* name */2](t[/* algorithm */1]),
          fill_json(t[/* fill */2]),
          Js_null.fromOption(t[/* wall */3]),
          Js_null.fromOption(t[/* edge */4]),
          t[/* batch_size */5],
          t[/* size_hint */6],
          t[/* canvas_size */7],
          t[/* seed */8]
        ];
}

function to_json(t) {
  return Js_primitive.undefined_to_opt(JSON.stringify(to_jsonable(t)));
}

function $great$great$eq$eq(a, b) {
  if (a) {
    return Curry._1(b, a[0]);
  } else {
    return /* None */0;
  }
}

function $great$great$eq(a, b) {
  if (a) {
    return /* Some */[Curry._1(b, a[0])];
  } else {
    return /* None */0;
  }
}

function $great$unknown(a, b) {
  if (a) {
    return a[0];
  } else {
    return b;
  }
}

function parse_line(value) {
  var match = Js_json.classify(value);
  if (typeof match === "number" || match.tag !== 3) {
    return /* None */0;
  } else {
    var match$1 = match[0];
    if (match$1.length !== 2) {
      return /* None */0;
    } else {
      var width = match$1[0];
      var light = match$1[1];
      var match$2 = Js_json.classify(width);
      var match$3 = Js_json.classify(light);
      if (typeof match$2 === "number" || !(match$2.tag === 1 && !(typeof match$3 === "number" || match$3.tag !== 1))) {
        return /* None */0;
      } else {
        return /* Some */[/* tuple */[
                  match$2[0] | 0,
                  match$3[0] | 0
                ]];
      }
    }
  }
}

function from_json(str) {
  var parsed;
  try {
    parsed = /* Some */[JSON.parse(str)];
  }
  catch (exn){
    parsed = /* None */0;
  }
  if (parsed) {
    var match = Js_json.decodeArray(parsed[0]);
    if (match) {
      var items = match[0];
      var board = $great$unknown($great$great$eq$eq($great$great$eq$eq(Belt_Array.get(items, 0), Js_json.decodeString), Types.Board[/* by_name */3]), /* Hexagon */2);
      var algorithm = $great$unknown($great$great$eq$eq($great$great$eq$eq(Belt_Array.get(items, 1), Js_json.decodeString), Types.Alg[/* by_name */3]), /* DFS */0);
      var fill = $great$unknown($great$great$eq$eq(Belt_Array.get(items, 2), parse_fill), /* HueSat */[/* tuple */[
              30,
              90
            ]]);
      var wall = $great$great$eq$eq(Belt_Array.get(items, 3), parse_line);
      var edge = $great$great$eq$eq(Belt_Array.get(items, 4), parse_line);
      var batch_size = $great$unknown($great$great$eq($great$great$eq$eq(Belt_Array.get(items, 5), Js_json.decodeNumber), (function (prim) {
                  return prim | 0;
                })), 1);
      var size_hint = $great$unknown($great$great$eq($great$great$eq$eq(Belt_Array.get(items, 6), Js_json.decodeNumber), (function (prim) {
                  return prim | 0;
                })), 10);
      var canvas_size = $great$unknown($great$great$eq($great$great$eq$eq(Belt_Array.get(items, 7), Js_json.decodeNumber), (function (prim) {
                  return prim | 0;
                })), 1000);
      var seed = $great$unknown($great$great$eq($great$great$eq$eq(Belt_Array.get(items, 8), Js_json.decodeNumber), (function (prim) {
                  return prim | 0;
                })), 0);
      return /* Some */[/* record */[
                /* board */board,
                /* algorithm */algorithm,
                /* fill */fill,
                /* wall */wall,
                /* edge */edge,
                /* batch_size */batch_size,
                /* size_hint */size_hint,
                /* canvas_size */canvas_size,
                /* seed */seed
              ]];
    } else {
      return /* None */0;
    }
  } else {
    return /* None */0;
  }
}

function to_options(settings) {
  var match = settings[/* edge */4];
  var tmp;
  if (match) {
    var match$1 = match[0];
    tmp = /* Some */[/* tuple */[
        match$1[0],
        Presenter.hsl(0, 0, match$1[1])
      ]];
  } else {
    tmp = /* None */0;
  }
  var match$2 = settings[/* wall */3];
  var tmp$1;
  if (match$2) {
    var match$3 = match$2[0];
    tmp$1 = /* Some */[/* tuple */[
        match$3[0],
        Presenter.hsl(0, 0, match$3[1])
      ]];
  } else {
    tmp$1 = /* None */0;
  }
  var match$4 = settings[/* fill */2];
  var tmp$2;
  if (typeof match$4 === "number") {
    tmp$2 = match$4 !== 0 ? /* Some */[(function (_, max) {
            return Presenter.hslf(max * 360.0, 70.0, 50.0);
          })] : /* None */0;
  } else {
    var match$5 = match$4[0];
    var saturation = match$5[1];
    var hue = match$5[0];
    tmp$2 = /* Some */[(function (current, _) {
          return Presenter.hslf(hue, saturation, 100.0 - current * 50.0);
        })];
  }
  return /* record */[
          /* canvas_size : tuple */[
            settings[/* canvas_size */7],
            settings[/* canvas_size */7]
          ],
          /* min_margin */10.0,
          /* size_hint */settings[/* size_hint */6],
          /* draw_edges */tmp,
          /* draw_walls */tmp$1,
          /* draw_shapes */tmp$2
        ];
}

var initial = /* record */[
  /* board : Hexagon */2,
  /* algorithm : DFS */0,
  /* fill : HueSat */[/* tuple */[
      30,
      90
    ]],
  /* wall : Some */[/* tuple */[
      1,
      20
    ]],
  /* edge : None */0,
  /* batch_size */1,
  /* size_hint */10,
  /* canvas_size */1000,
  /* seed */0
];

exports.T = T;
exports.to_jsonable = to_jsonable;
exports.to_json = to_json;
exports.$great$great$eq$eq = $great$great$eq$eq;
exports.$great$great$eq = $great$great$eq;
exports.$great$unknown = $great$unknown;
exports.parse_line = parse_line;
exports.initial = initial;
exports.from_json = from_json;
exports.to_options = to_options;
/* Types Not a pure module */
