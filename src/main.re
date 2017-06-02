module Ctx = Canvas.Ctx;

module type Board = Shared.Board;

Random.self_init();

module Draw = Animate.Draw JsRect RandomSearch;

let main () => {
  let canvas = Canvas.createOnBody 1000 1000;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 5.0;

  let size = 20;
  let size = (20, 20);
  let csize = (500.0, 500.0);

  Draw.draw ctx size csize;
  /*
  Draw.dots ctx size csize;
  Draw.walls ctx size csize;
  Draw.connections ctx size csize;
  */
  Js.log "iiaaai0000bmm";

  /*
  let s = 4;
  let v = ref 0;
  for y in 0 to (s - 1) {
    for x in 0 to (s - y - 1) {
      Js.log (!v, x, y, HexTriangle.from_vertex !v s);
      v := !v + 1;
    }
  };
  */
};

main ();
