
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

let module Manager = Manager.F NewRect NewBFS;
let module Presenter = Presenter.F NewRect NewBFS;

/* have this take some config */
let show ctx (width, height) state => {
  Canvas.Ctx.setStrokeWidth ctx 1.0;
  Canvas.Ctx.setLineCap ctx "round";
  Canvas.Ctx.clearRect ctx 0.0 0.0 width height;
  /* TODO might be nice to do something sophisticated with corners... */

  /*List.iter (Presenter.draw_edge ctx) (Manager.all_edges state);*/
  List.iter (Presenter.draw_wall ctx) (Manager.all_walls state);
};

let rec batch state n => if (n === 0) { state } else { batch (Manager.step state) (n - 1) };

let animate ctx canvas_size state => {
  let rec inner state => {
    let state = batch state 1;
    show ctx canvas_size state;
    Manager.finished state
      ? (Js.log "done")
      : Window.setTimeout (fun () => inner state) 40 |> ignore
  };
  inner state;
};

let main () => {
  Random.self_init();

  let canvas_size = (500.0, 500.0);
  let (width, height) = canvas_size;

  let canvas = Canvas.createOnBody (iof width) (iof height);
  let ctx = Canvas.getContext canvas;

  let state = Manager.init canvas_size 10;  

  if (false) {
    show ctx canvas_size (Manager.loop_to_end state);
  } else {
    animate ctx canvas_size state;
  }
};

main ();
