module Ctx = Canvas.Ctx;

let sf = string_of_float;
let si = string_of_int;
let hsl h s l => "hsla(" ^ (si h) ^ ", " ^ (si s) ^ "%, " ^ (si l) ^ "%, 0.3)";

let draw_point ctx count age dot_color size (x, y) => {
  Ctx.setFillStyle ctx (dot_color age count);
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
          |> Utils.maybe (draw_wall ctx) |> ignore)
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

  let dots ctx bsize csize traveled total_age dot_color size => {
    List.iter
      (fun {Shared.Edge.dest, src, age} => {
        Board.vertex_pos dest bsize csize
          |> draw_point ctx total_age age dot_color size;
        })
      traveled;
  };

  let paths ctx bsize csize traveled => {
    List.iter
      (fun {Shared.Edge.dest, src, age} => {
        let a =
          (Board.vertex_pos src bsize csize);
        let b =
          (Board.vertex_pos dest bsize csize);
        Canvas.Ctx.line ctx a b;
        })
      traveled;
  };

  let connections ctx bsize csize adjacent => {
    List.iter
      (fun (src, dest) => {
        let a =
          (Board.vertex_pos src bsize csize);
        let b =
          (Board.vertex_pos dest bsize csize);
        Canvas.Ctx.line ctx
          a b;
        })
      adjacent;
  };
};

