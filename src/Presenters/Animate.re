module type Config = {let batch: int;};

module Default: Config = {
  let batch = 10;
};

module Draw =
       (
         Config: Config,
         Board: Shared.Board,
         Generator: Shared.Generator,
         DrawConfig: DrawShared.Config,
       ) => {
  module Draw = DrawShared.Draw(Board, DrawConfig);
  let draw = (ctx, bsize, csize) => {
    let adjacency = Board.adjacency_list(bsize);
    let state = Generator.init(Board.Shape.vertex_count(bsize), adjacency);
    let rec loop = state => {
      let walls =
        Walls.walls_remaining(adjacency, Generator.State.traveled(state));
      Draw.draw(
        ctx,
        bsize,
        csize,
        walls,
        Generator.State.traveled(state),
        Generator.State.current(state),
        Generator.State.next(state),
      );
      if (Generator.State.finished(state)) {
        ();
      } else {
        let tmp = ref(state);
        for (_ in 0 to Config.batch - 1) {
          tmp := Generator.step(tmp^);
        };
        Window.setTimeout(() => loop(tmp^), 100) |> ignore;
      };
    };
    loop(state);
  };
};
