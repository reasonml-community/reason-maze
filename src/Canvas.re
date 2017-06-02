type canvasRenderingContext2D;

type ctx = canvasRenderingContext2D;

type canvasElement;

let getById: string => canvasElement = [%bs.raw {|function(arg) {
  return document.getElementById(arg)
 }|}];

let createOnBody: unit => canvasElement = [%bs.raw {|function() {
  var node = document.createElement('canvas')
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
  external fillRect : ctx => float => float => float => float => unit = "" [@@bs.send];
  external clearRect : ctx => float => float => float => float => unit = "" [@@bs.send];
  external ellipse : ctx => float => float => float => float => float => float => float => unit =
    "" [@@bs.send];
  external moveTo : ctx => float => float => unit = "" [@@bs.send];
  external lineTo : ctx => float => float => unit = "" [@@bs.send];
  external fill : ctx => unit = "" [@@bs.send];
  external beginPath : ctx => unit = "" [@@bs.send];
  external stroke : ctx => unit = "" [@@bs.send];
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
