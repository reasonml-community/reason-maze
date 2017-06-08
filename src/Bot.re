

/*
module Board = (Shared.Board Rect);

let choose l => l.(Random.int (Array.length l));

module type ConfigBase = {
  let showTrails: bool;
  let showAge: bool;
  let showWalls: bool;
};

let main () => {
  Random.self_init();
  let csize = (1000.0, 1000.0);
  let canvas = NodeCanvas.canvas 1000 1000;
  let ctx = NodeCanvas.getContext canvas "2d";
  Canvas.Ctx.setFillStyle ctx "white";
  Canvas.Ctx.fillRect ctx 0.0 0.0 1000.0 1000.0;

  let algorithms: array (module Shared.Generator) = [|
    (module DepthFirst.F {
      let maxHits = 1 + Random.int 9;
      let joinOnHit = Random.float 1.0;
    }),
    /*(module BreadthFirstSearch),*/
    (module RandomSearch),
    (module RandomSearch2)
  |];

  let configBases: array (module ConfigBase) = [|
    (module {
      let showTrails = false;
      let showAge = true;
      let showWalls = false;
    }),
    (module {
      let showTrails = Random.bool();
      let showAge = false;
      let showWalls = true;
    }),
  |];

  let module Algo = (val (choose algorithms));
  let module DrawConfig = {
    include DrawShared.Default;
    include (val (choose configBases));
    let showEdge = false;
    let dotSize = 10 + Random.int 30 |> float_of_int;
    let dotColor age total_age => (DrawShared.hsla (Random.int 360) 100 (100 * (total_age - age) / total_age) 0.6)
  };

  let module Draw = Final.Draw Board Algo DrawConfig;

  let sz = 30;
  let wall_ratio = (Random.float 0.4) +. 0.1;
  Canvas.Ctx.setStrokeWidth ctx (1000.0 /. (float_of_int sz) *. wall_ratio);
  let size = 20;
  let size = (30, 30);
  Draw.draw ctx size csize;

  NodeCanvas.saveAs "./out.png" (NodeCanvas.toBuffer canvas);
};

main();
*/

let main () => {
  let csize = (1000.0, 1000.0);
  let canvas = NodeCanvas.canvas 1000 1000;
  let ctx = NodeCanvas.getContext canvas "2d";

  /*main();*/
  RandomMaze.run ctx (1000.0, 1000.0);

  NodeCanvas.saveAs "./out.png" (NodeCanvas.toBuffer canvas);
};
main();
