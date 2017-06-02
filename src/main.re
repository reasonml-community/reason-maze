module Ctx = Canvas.Ctx;

module type Board = Shared.Board;

Random.self_init();

module Draw = Animate.Draw JsRect BreadthFirstSearch;

let main () => {
  let canvas = Canvas.createOnBody 500 500;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 5.0;

  let size = (20, 20);
  let csize = (500.0, 500.0);

  Draw.draw ctx size csize;
  Js.log "iiaaai0000bmm";

  Ctx.strokeRect ctx 0.0 0.0 500.0 500.0;
};

main ();
