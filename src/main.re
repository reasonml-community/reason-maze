
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

let module Gen = Random2;
let module Board = HexBox;
let module Man = Manager.F Board Gen;
let module Presenter = Presenter.F Board Gen;

/* have this take some config */
let show ctx (width, height) state => {
  Canvas.Ctx.setStrokeWidth ctx 1.0;
  Canvas.Ctx.setLineCap ctx "round";
  Canvas.Ctx.clearRect ctx 0.0 0.0 width height;
  /* TODO might be nice to do something sophisticated with corners... */

  let (w, h) = state.Manager.State.outsize;
  let xm = (width -. w) /. 2.0;
  let ym = (height -. h) /. 2.0;
  /*let (xm, ym) = (0.0, 0.0);*/

  Array.iter (Presenter.draw_shape ctx (xm, ym) (Man.max_age state)) (Man.all_shapes state);
  /*List.iter (Presenter.draw_edge ctx (xm, ym)) (Man.all_edges state);*/
  List.iter (Presenter.draw_wall ctx (xm, ym)) (Man.all_walls state);
};

let rec batch state n => if (n === 0) { state } else { batch (Man.step state) (n - 1) };

let animate ctx batch_size canvas_size state => {
  let rec inner state => {
    let state = batch state batch_size;
    show ctx canvas_size state;
    Man.finished state
      ? (Js.log "done")
      : Window.setTimeout (fun () => inner state) 40 |> ignore
  };
  inner state;
};

let main () => {
  Random.self_init();

  let canvas_size = (1000.0, 1000.0);
  let (width, height) = canvas_size;
  let min_margin = 50.0;

  let canvas = Canvas.createOnBody (iof width) (iof height);
  let ctx = Canvas.getContext canvas;

  let with_margins = (width -. min_margin, height -. min_margin);
  let state = Man.init with_margins 40;  

  if (false) {
    show ctx canvas_size state;
  } else if (false) {
    show ctx canvas_size (Man.loop_to_end state);
  } else {
    animate ctx 20 canvas_size state;
  }
};

main ();
