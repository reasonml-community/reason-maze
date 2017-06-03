
module type Config = {
  let unvisitedFill: option string;
  let showTrails: bool;
  let wallColor: string;
  let batch: int;
  let showEdge: bool;
  let showWalls: bool;
};

module Default: Config = {
  let unvisitedFill = None;
  let showTrails = true;
  let batch = 1;
  let wallColor = "rgb(100, 100, 100)";
  let showEdge = true;
  let showWalls = true;
};

module Draw (Board: Shared.Board) (Generator: Shared.Generator) (Config: Config) => {
  module Draw = DrawShared.Draw(Board);

  let draw ctx bsize csize => {
    let adjacency = Board.adjacency_list bsize;
    let state = Generator.init (Board.Shape.vertex_count bsize) adjacency;
    Canvas.Ctx.setLineCap ctx "round";
    let batch_size = Config.batch;
    let rec loop state => {
      let (wsize, hsize) = csize;
      Canvas.Ctx.clearRect ctx 0.0 0.0 wsize hsize;

      let walls = Walls.walls_remaining adjacency (Generator.State.traveled state);

      if (Config.showWalls) {
        Canvas.Ctx.setStrokeStyle ctx Config.wallColor;
        Canvas.Ctx.strokeRect ctx 0.0 0.0 wsize hsize;
        Draw.walls ctx bsize csize walls;
        Board.Shape.border_walls bsize csize |> List.iter (Draw.draw_wall ctx);
      };

      if (Config.showTrails) {
        Canvas.Ctx.setStrokeStyle ctx "rgb(200, 200, 200)";
        Draw.paths ctx bsize csize (Generator.State.traveled state);
      };

      Draw.dots ctx bsize csize (Generator.State.traveled state) (Board.Shape.vertex_count bsize) 15.0;

      if (Config.showEdge) {
        Canvas.Ctx.setFillStyle ctx "green";
        Draw.vertex_dots ctx bsize csize (Generator.State.current state) 5.0;

        Canvas.Ctx.setFillStyle ctx "blue";
        Draw.vertex_dots ctx bsize csize (Generator.State.next state) 5.0;
      };

      switch (Generator.State.current state) {
        | [] => ()
        | _ => {
          let tmp = ref state;
          for _ in 0 to (Config.batch - 1) {
            tmp := (Generator.step !tmp);
          };
          Window.setTimeout (fun () => loop !tmp) 100; ()
        }
      }
    };
    loop state
  };
};

