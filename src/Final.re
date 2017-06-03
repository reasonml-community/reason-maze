
module Draw (Board: Shared.Board) (Generator: Shared.Generator) => {
  module Draw = DrawShared.Draw(Board);

  let draw ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    let traveled = Generator.spanning_tree
      (Board.Shape.vertex_count bsize) full;
    let walls = Walls.walls_remaining full traveled;

    Draw.dots ctx bsize csize traveled (Board.Shape.vertex_count bsize) 15.0;
    Draw.walls ctx bsize csize walls;
    Draw.paths ctx bsize csize traveled;
  };
}


