module Ctx = Canvas.Ctx;

module type Board = Shared.Board;

module Rect: Board = JsRect;

let draw ctx walls => {
  List.iter
  (fun wall => {
    switch (wall)  {
      | Shared.Line ((x, y), (a, b)) => {
        Ctx.beginPath ctx;
        Ctx.moveTo ctx x y;
        Ctx.lineTo ctx a b;
        Ctx.stroke ctx;
      }
    }
  })
  walls
};

let init () => {
  open JsRect;
  let board = create 10 10;
  add_wall board (2, 2) JsRect.Direction.Up;
  add_wall board (2, 2) JsRect.Direction.Left;
  add_wall board (4, 4) JsRect.Direction.Down;
  add_wall board (4, 4) JsRect.Direction.Right;
  board;
};

let main () => {
  let canvas = Canvas.createOnBody ();
  let ctx = Canvas.getContext canvas;
  Ctx.fillRect ctx 100.0 100.0 100.0 100.0;

  let board = init ();
  draw ctx (JsRect.drawable_walls board (100.0, 100.0));

  /*
  let ctx = Dom.createCtx Dom.document;
  let state = ref (Hunting.initial ctx);
  Animate.loop (fun () => state := Hunting.draw !state)
  */
  print_endline "hello folks2";
};

main ();
