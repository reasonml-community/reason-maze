
module Draw (Board: Shared.Board) (Generator: Shared.Generator) => {
  let draw ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    let traveled = Generator.spanning_tree
      (Board.vertex_count bsize) full;
    let walls = Shared.walls_remaining full traveled;
    List.iter
      (fun wall =>
        Board.drawable_wall wall bsize csize
          |> DrawShared.draw_wall ctx)
      walls;
    Js.log "hi";
    List.iter
      (fun {Shared.Edge.dest, age} =>
       Board.vertex_pos dest bsize csize
        |> DrawShared.draw_point ctx age)
      traveled;
  };
}


