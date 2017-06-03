module Ctx = Canvas.Ctx;

let sf = string_of_float;
let si = string_of_int;
let hsl h s l => "hsla(" ^ (si h) ^ ", " ^ (si s) ^ "%, " ^ (si l) ^ "%, 0.3)";

let draw_point ctx count age size (x, y) => {
  Ctx.setFillStyle ctx (hsl 0 100 (100 * (count - age) / count));
  Ctx.beginPath ctx;
  Ctx.circle ctx x y size;
  Ctx.fill ctx;
};

module Draw (Board: Shared.Board) => {

  let draw_wall ctx wall => {
    switch (wall)  {
      | Shared.Line (p1, p2) => {
        Ctx.line ctx p1 p2
      }
    }
  };
  let walls ctx bsize csize walls => {
    List.iter
      (fun wall =>
        Board.drawable_wall wall bsize csize
          |> draw_wall ctx)
      walls;
  };


  let vertex_dots ctx bsize csize vertices size => {
    List.iter
      (fun vertex => {
        let (x, y) = Board.vertex_pos vertex bsize csize;
        Ctx.beginPath ctx;
        Ctx.circle ctx x y size;
        Ctx.fill ctx;
      })
      vertices;
  };

  let dots ctx bsize csize traveled total_age size => {
    List.iter
      (fun {Shared.Edge.dest, src, age} => {
        Board.vertex_pos dest bsize csize
          |> draw_point ctx total_age age size;
        })
      traveled;
  };
  let paths ctx bsize csize traveled => {
    List.iter
      (fun {Shared.Edge.dest, src, age} => {
        Canvas.Ctx.line ctx
          (Board.vertex_pos src bsize csize)
          (Board.vertex_pos dest bsize csize)
        })
      traveled;
  };

  let connections ctx bsize csize traveled => {
    List.iter
      (fun (src, dest) => {
        Canvas.Ctx.line ctx
          (Board.vertex_pos src bsize csize)
          (Board.vertex_pos dest bsize csize)
        })
      traveled;
  };
};

