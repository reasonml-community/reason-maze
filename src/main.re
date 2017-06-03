module Ctx = Canvas.Ctx;

Random.self_init();

module Draw = Animate.Draw (Shared.Board Rect) RandomSearch {
  include Animate.Default;
  let showTrails = false;
};

let main () => {
  let canvas = Canvas.createOnBody 1000 1000;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 5.0;

  let size = 20;
  let size = (20, 20);
  let csize = (500.0, 500.0);

  Draw.draw ctx size csize;
};

main ();
