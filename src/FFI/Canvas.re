type canvasRenderingContext2D;

type ctx = canvasRenderingContext2D;

type canvasElement;

let getById: string => canvasElement = [%bs.raw
  {|function(arg) {
  return document.getElementById(arg)
 }|}
];

let createOnBody: (int, int) => canvasElement = [%bs.raw
  {|function(width, height) {
  var node = document.createElement('canvas')
  node.width = width
  node.height = height
  document.body.appendChild(node)
  return node
}|}
];

[@bs.send]
external getContext : (canvasElement, [@bs.as "2d"] _) => canvasRenderingContext2D = "getContext";

/* canvas api methods */
module Ctx = {
  [@bs.get] external canvas : ctx => canvasElement = "";
  [@bs.set] external setFillStyle : (ctx, string) => unit = "fillStyle";
  [@bs.set] external setStrokeStyle : (ctx, string) => unit = "strokeStyle";
  [@bs.set] external setStrokeWidth : (ctx, float) => unit = "lineWidth";
  [@bs.set] external setLineWidth : (ctx, float) => unit = "lineWidth";
  [@bs.set] external setLineCap : (ctx, string) => unit = "lineCap";
  [@bs.set] external setFont : (ctx, string) => unit = "font";
  [@bs.send] external fillRect : (ctx, float, float, float, float) => unit = "";
  [@bs.send] external fillText : (ctx, string, float, float) => unit = "";
  [@bs.send] external strokeRect : (ctx, float, float, float, float) => unit = "";
  [@bs.send] external clearRect : (ctx, float, float, float, float) => unit = "";
  [@bs.send]
  external ellipse : (ctx, float, float, float, float, float, float, float) => unit = "";
  let circle = (ctx, x, y, r) => ellipse(ctx, x, y, r, r, 0.0, 0.0, 2.0 *. [%bs.raw "Math.PI"]);
  [@bs.send] external moveTo : (ctx, float, float) => unit = "";
  [@bs.send] external arc : (ctx, float, float, float, float, float) => unit = "";
  [@bs.send]
  external arc_rev : (ctx, float, float, float, float, float, [@bs.as {json|true|json}] _) => unit =
    "arc";
  let moveToPos = (ctx, (x, y)) => moveTo(ctx, x, y);
  [@bs.send] external lineTo : (ctx, float, float) => unit = "";
  let lineToPos = (ctx, (x, y)) => lineTo(ctx, x, y);
  [@bs.send] external fill : ctx => unit = "";
  [@bs.send] external beginPath : ctx => unit = "";
  [@bs.send] external stroke : ctx => unit = "";
  let line = (ctx, (x, y), (a, b)) => {
    beginPath(ctx);
    moveTo(ctx, x, y);
    lineTo(ctx, a, b);
    stroke(ctx)
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
