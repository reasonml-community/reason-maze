module Ctx = Canvas.Ctx;

module type Board = Shared.Board;
module WallSet = Shared.WallSet;

Random.self_init();

let main () => {
  let canvas = Canvas.createOnBody 500 500;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 2.0;

  let size = (10, 10);
  let walls = JsRect.adjacency_list size;
  let tree = BreadthFirstSearch.spanning_tree (JsRect.vertex_count size) walls;
  let to_draw = Shared.walls_remaining walls tree;
  List.iter
  (fun wall => JsRect.drawable_wall wall size (500.0, 500.0) |> DrawShared.draw_wall ctx)
  to_draw;


  /*
  draw ctx (JsRect.drawable_walls board (500.0, 500.0));
  Ctx.strokeRect ctx 1.0 1.0 498.0 498.0;

  let ctx = Dom.createCtx Dom.document;
  let state = ref (Hunting.initial ctx);
  Animate.loop (fun () => state := Hunting.draw !state)
  */
  print_endline "hello folks2";
};

main ();
