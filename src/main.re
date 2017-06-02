module Ctx = Canvas.Ctx;

module type Board = Shared.Board;

let draw_wall ctx wall => {
  switch (wall)  {
    | Shared.Line ((x, y), (a, b)) => {
      Ctx.beginPath ctx;
      Ctx.moveTo ctx x y;
      Ctx.lineTo ctx a b;
      Ctx.stroke ctx;
    }
  }
};

module Wall = {
  type t = (int, int);
  let compare (x, y) (a, b) => {
    switch (compare x a) {
      | 0 => compare y b
      | v => v
    }
  };
};

module WallSet = Set.Make(Wall);

let get_walls walls clear => {
  let (i, res) = Array.fold_left
  (fun (i, res) ends => {
    (
      i + 1,
      (List.fold_left
      (fun res vend => {
        vend < i
          ? res
          : (WallSet.mem (i, vend) clear
            ? res
            : [(i, vend), ...res])
      })
      []
      ends) @ res
    )
  })
  (0, [])
  walls;
  res
};

let main () => {
  let canvas = Canvas.createOnBody 500 500;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 2.0;

  let size = (10, 10);
  let walls = JsRect.adjacency_list size;
  let tree = BreadthFirstSearch.spanning_tree (JsRect.vertex_count size) walls;
  let clear = WallSet.of_list (List.map (fun (a, b) => a > b ? (b, a) : (a,
                                                                         b)) tree);
  let to_draw = get_walls walls clear;
  Js.log (walls, Array.of_list tree, WallSet.elements clear |> Array.of_list, to_draw);
  List.iter
  (fun wall => JsRect.drawable_wall wall size (500.0, 500.0) |> draw_wall ctx)
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
