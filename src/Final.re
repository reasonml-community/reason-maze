
module Draw (Board: Shared.Board) => {
  let draw ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    let tree = BreadthFirstSearch.spanning_tree
      (Board.vertex_count bsize) full;
    let clear = Shared.wall_set tree;
    let walls = get_walls full clear;
    List.iter
      (fun wall =>
        Board.drawable_wall wall bsize csize
          |> DrawShared.draw_wall ctx)
      walls;
  };
}

