module Ctx = Canvas.Ctx;

module type Board = Shared.Board;
module WallSet = Shared.WallSet;

Random.self_init();

module Draw = Final.Draw JsRect BreadthFirstSearch;

let main () => {
  let canvas = Canvas.createOnBody 500 500;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 2.0;

  let size = (50, 50);
  let csize = (500.0, 500.0);

  Draw.draw ctx size csize;
  Js.log "aaaimm";

  Ctx.strokeRect ctx 0.0 0.0 500.0 500.0;
};

main ();
