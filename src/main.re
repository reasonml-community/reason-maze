
/*module M: SimpleBoard.T = TriangleBoard;*/
/*module R: SimpleBoard.T = NewRect;*/

let iof = int_of_float;

/*
module DrawConfig = {
  include DrawShared.Default;
  let showTrails = false;
  let showAge = true;
  let showEdge = false;
  let dotSize = 13.0;
  let showWalls = false;
  let dotColor age total_age => (DrawShared.hsla 0 100 (100 * (total_age - age) / total_age) 0.7)
};
module Board = (Shared.Board Rect);
module Algo = DepthFirst.F { let maxHits = 5; let joinOnHit = 0.5; };
module ADraw = Animate.Draw {
  include Animate.Default;
  let batch = 1;
};
module Draw = Final.Draw Board Algo DrawConfig ;

let main () => {
  Random.self_init();
  let csize = (1000.0, 1000.0);
  let (width, height) = csize;
  let canvas = Canvas.createOnBody (iof width) (iof height);
  let ctx = Canvas.getContext canvas;

  Canvas.Ctx.setStrokeWidth ctx 1.0;
  let size = 500;
  let size = (100, 100);
  Draw.draw ctx size csize;
};
*/

let main () => {
  Random.self_init();

  let module Manager = Manager.F NewRect NewBFS;
  let module Presenter = Presenter.F NewRect NewBFS;
  let canvas_size = (500.0, 500.0);
  let (width, height) = canvas_size;
  let state = Manager.init canvas_size 10;  
  let state = Manager.loop_to_end state;
  let walls = Manager.all_walls state;

  let canvas = Canvas.createOnBody (iof width) (iof height);
  let ctx = Canvas.getContext canvas;

  Js.log state;
  Js.log walls;

  Generator.PairSet.iter
  (fun (a, b) => {
    Canvas.Ctx.line ctx
    (NewRect.offset state.shape state.scale (Array.get state.coords a))
    (NewRect.offset state.shape state.scale (Array.get state.coords b));
  })
  (NewBFS.edges state.gen_state);

  Canvas.Ctx.setStrokeWidth ctx 0.5;

  Presenter.draw_walls ctx canvas_size walls;
};

main ();
