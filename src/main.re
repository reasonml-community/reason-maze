module Ctx = Canvas.Ctx;

Random.self_init();

module Board = (Shared.Board HexTriangle2);
module Draw = Animate.Draw Board RandomSearch {
  include Animate.Default;
  let showTrails = false;
  let showAge = true;
  let batch = 100;
  let showEdge = false;
  let showWalls = false;
  let dotColor age total_age => (DrawShared.hsl 80 100 (100 * (total_age - age) / total_age))
};

let iof = int_of_float;

let main () => {
  let csize = (1000.0, 1000.0);
  let (width, height) = csize;
  let canvas = Canvas.createOnBody (iof width) (iof height);
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 3.0;

  let size = (50, 50);
  let size = 100;

  Draw.draw ctx size csize;
  /*
  Draw.dots ctx size csize;
  Draw.connections ctx size csize;
  */

    /*
  Js.log (
    Rect.to_vertex (5, 5) (0, 0),
    Rect.to_vertex (5, 5) (1, 0),
    Rect.to_vertex (5, 5) (0, 1),
    Rect.to_vertex (5, 5) (4,4),
    Rect.from_vertex (5, 5) 0,
    Rect.from_vertex (5, 5) 1,
    Rect.from_vertex (5, 5) 2,
    Rect.from_vertex (5, 5) 5,
    Rect.from_vertex (5, 5) 24,
    Rect.coord_to_board (5, 5) (0, 0) (100.0, 100.0),
    Rect.coord_to_board (5, 5) (4, 4) (100.0, 100.0),
    Rect.coord_to_board (5, 5) (2, 0) (100.0, 100.0),
    Rect.coord_to_board (5, 5) (0, 2) (100.0, 100.0),
    Rect.coord_to_board (5, 5) (0, 0) (100.0, 100.0),
    Board.vertex_pos 0 (5, 5) (100.0, 100.0),
    Rect.coord_to_board (5, 5) (1, 0) (100.0, 100.0),
    Board.vertex_pos 1 (5, 5) (100.0, 100.0),
  );
    */
};

main ();
