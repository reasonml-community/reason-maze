module Ctx = Canvas.Ctx;

module type Board = Shared.Board;

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

let fill board => {
  for x in 0 to 9 {
    for y in 0 to 9 {
      JsRect.add_wall board (x, y) JsRect.Direction.Up;
      JsRect.add_wall board (x, y) JsRect.Direction.Right;
    }
  };
  ()
};

let init () => {
  open JsRect;
  let board = create 10 10;
  add_wall board (1, 1) JsRect.Direction.Up;
  add_wall board (1, 1) JsRect.Direction.Left;
  Js.log board;
  add_wall board (4, 4) JsRect.Direction.Down;
  add_wall board (4, 4) JsRect.Direction.Right;
  fill board;
  board;
};

let main () => {
  let canvas = Canvas.createOnBody 500 500;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 2.0;

  let board = init ();
  draw ctx (JsRect.drawable_walls board (500.0, 500.0));
  Ctx.strokeRect ctx 1.0 1.0 498.0 498.0;

  /*
  let ctx = Dom.createCtx Dom.document;
  let state = ref (Hunting.initial ctx);
  Animate.loop (fun () => state := Hunting.draw !state)
  */
  print_endline "hello folks2";
};

main ();
