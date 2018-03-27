module Draw =
       (
         Board: Shared.Board,
         Generator: Shared.Generator,
         DrawConfig: DrawShared.Config,
       ) => {
  module Draw = DrawShared.Draw(Board, DrawConfig);

  let draw = (ctx, bsize, csize) => {
    let full = Board.adjacency_list(bsize);
    let traveled =
      Generator.spanning_tree(Board.Shape.vertex_count(bsize), full);
    let walls = Walls.walls_remaining(full, traveled);
    Draw.draw(ctx, bsize, csize, walls, traveled, [], []);
  };
};
