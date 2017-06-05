type canvasRenderingContext2D;

type ctx = canvasRenderingContext2D;

type canvasElement;

let getById: string => canvasElement = [%bs.raw {|function(arg) {
  return document.getElementById(arg)
 }|}];

let createOnBody: int => int => canvasElement = [%bs.raw {|function(width, height) {
  var node = document.createElement('canvas')
  node.width = width
  node.height = height
  document.body.appendChild(node)
  return node
}|}];

external getContext : canvasElement => _ [@bs.as "2d"] => canvasRenderingContext2D =
  "getContext" [@@bs.send];

/* canvas api methods */
module Ctx = {
  external setFillStyle : ctx => string => unit = "fillStyle" [@@bs.set];
  external setStrokeStyle : ctx => string => unit = "strokeStyle" [@@bs.set];
  external setStrokeWidth : ctx => float => unit = "lineWidth" [@@bs.set];
  external setLineCap : ctx => string => unit = "lineCap" [@@bs.set];
  external fillRect : ctx => float => float => float => float => unit = "" [@@bs.send];
  external strokeRect : ctx => float => float => float => float => unit = "" [@@bs.send];
  external clearRect : ctx => float => float => float => float => unit = "" [@@bs.send];
  external ellipse : ctx => float => float => float => float => float => float => float => unit =
    "" [@@bs.send];
  let circle ctx x y r => ellipse ctx x y r r 0.0 0.0 (2.0 *. [%bs.raw "Math.PI"]);
  external moveTo : ctx => float => float => unit = "" [@@bs.send];
  let moveToPos ctx (x, y) => moveTo ctx x y;
  external lineTo : ctx => float => float => unit = "" [@@bs.send];
  let lineToPos ctx (x, y) => lineTo ctx x y;
  external fill : ctx => unit = "" [@@bs.send];
  external beginPath : ctx => unit = "" [@@bs.send];
  external stroke : ctx => unit = "" [@@bs.send];
  let line ctx (x, y) (a, b) => {
    beginPath ctx;
    moveTo ctx x y;
    lineTo ctx a b;
    stroke ctx;
  };
};

/*
let createCanvas doc (width: int) (height: int) => {
  let elem = createCanvasElement doc;
  let jscanv = canvasElementToJsObj elem;
  jscanv##width#=width;
  jscanv##height#=height;
  elem
};

let createCtx (doc: document) => {
  let canv = createCanvas doc 1000 500;
  addCanvasToBody doc canv;
  getContext canv
};
*/
