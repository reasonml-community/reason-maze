module Ctx = Canvas.Ctx;

Random.self_init();

module DrawConfig = {
  include DrawShared.Default;
  let showTrails = true;
  let showAge = true;
  let showEdge = false;
  let dotSize = 35.0;
  let showWalls = true;
  let dotColor age total_age => (DrawShared.hsla 0 100 (100 * (total_age - age) / total_age) 0.1)
};
module Board = (Shared.Board Rect);
module Algo = DepthFirst.F { let maxHits = 1; let joinOnHit = 0.01; };
module ADraw = Animate.Draw Board Algo DrawConfig {
  include Animate.Default;
  let batch = 4;
};
module FDraw = Final.Draw Board Algo DrawConfig;

let iof = int_of_float;

let main () => {
  let csize = (1000.0, 1000.0);
  let (width, height) = csize;
  let canvas = Canvas.createOnBody (iof width) (iof height);
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 3.0;

  let size = 50;
  let size = (30, 30);
  FDraw.draw ctx size csize;
};

main ();
