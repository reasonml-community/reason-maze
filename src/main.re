module Ctx = Canvas.Ctx;

module type Board = Shared.Board;

Random.self_init();

module Config = {
  include Animate.Default;
  let showTrails = false;
};

module Draw = Animate.Draw HexTriangle RandomSearch Config;

let main () => {
  let canvas = Canvas.createOnBody 1000 1000;
  let ctx = Canvas.getContext canvas;

  Ctx.setStrokeWidth ctx 5.0;

  let size = (20, 20);
  let size = 20;
  let csize = (500.0, 500.0);

  Draw.draw ctx size csize;
};

main ();
