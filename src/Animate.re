
module Draw (Board: Shared.Board) (Generator: Shared.Generator) => {
  module Draw = DrawShared.Draw(Board);

  let draw ctx bsize csize => {
    let adjacency = Board.adjacency_list bsize;
    let state = Generator.init (Board.vertex_count bsize) adjacency;
    Canvas.Ctx.setLineCap ctx "round";
    let rec loop state => {
      Canvas.Ctx.clearRect ctx 0.0 0.0 500.0 500.0;
      Canvas.Ctx.setStrokeStyle ctx "rgb(100, 100, 100)";
      Canvas.Ctx.strokeRect ctx 0.0 0.0 500.0 500.0;

      let walls = Walls.walls_remaining adjacency (Generator.State.traveled state);
      Canvas.Ctx.setStrokeStyle ctx "rgb(100, 100, 100)";
      Draw.walls ctx bsize csize walls;
      Canvas.Ctx.setStrokeStyle ctx "rgb(200, 200, 200)";
      Draw.paths ctx bsize csize (Generator.State.traveled state);

      Canvas.Ctx.setFillStyle ctx "green";
      Draw.vertex_dots ctx bsize csize (Generator.State.current state) 5.0;

      Canvas.Ctx.setFillStyle ctx "blue";
      Draw.vertex_dots ctx bsize csize (Generator.State.next state) 5.0;

      switch (Generator.State.current state) {
        | [] => ()
        | _ => {Window.setTimeout
                (fun () => loop (Generator.step state)) 100; ()
        }
      }
    };
    loop state
  };
};

