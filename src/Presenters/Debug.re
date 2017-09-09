let all_walls full =>
  Array.fold_left
    (fun (i, res) item => (i + 1, List.map (fun d => (i, d)) item @ res)) (0, []) full
  |> snd;

let range i n => {
  let rec aux n acc =>
    if (n < i) {
      acc
    } else {
      aux (n - 1) [n, ...acc]
    };
  aux (n - 1) []
};

module Draw (Board: Shared.Board) (Generator: Shared.Generator) (DrawConfig: DrawShared.Config) => {
  module Draw = DrawShared.Draw Board DrawConfig;
  let walls ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    Draw.draw_walls ctx bsize csize (all_walls full)
  };
  let dots ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    let vertices = Board.Shape.vertex_count bsize;
    Draw.vertex_dots ctx bsize csize (range 0 vertices) 10.0
  };
  let paths ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    let traveled = Generator.spanning_tree (Board.Shape.vertex_count bsize) full;
    Canvas.Ctx.setStrokeStyle ctx "rgba(100, 100, 100, 0.1)";
    Draw.paths ctx bsize csize traveled
  };
  let connections ctx bsize csize => {
    let full = Board.adjacency_list bsize;
    Js.log (Array.map Array.of_list full);
    Canvas.Ctx.setStrokeStyle ctx "rgba(100, 100, 100, 0.1)";
    Draw.connections ctx bsize csize (all_walls full)
  };
};
