
module F (Board: SimpleBoard.T) (Generator: Generator.T) => {
  module CoordMap = Map.Make Board.Coord;
  let create_index_map coords => {
    Array.fold_left
      (fun (i, map) c => (i + 1, CoordMap.add c i map))
      (0, CoordMap.empty)
      coords |> snd
  };

  let get_adjacent shape clist cmap i => {
    let coord = Array.get clist i;
    Board.adjacents shape coord
    |> List.map (Board.adjacent_coord shape coord)
    |> List.map (fun x => CoordMap.find x cmap)
  };

  let setup (width, height) hint_size ctx => {
    let (shape, scale, outsize) = Board.auto_size (width, height) hint_size;
    let coords = Board.coordinates shape |> Array.of_list;
    let coord_map = create_index_map coords;
    let count = Array.length coords;
    let state = Generator.init count;
    let get_adjacent = get_adjacent shape coords coord_map;
  };

  module State = {
    type t = {
      count: int,
      shape: Board.shape,
      scale: float,
      outsize: (float, float),
      gen_state: Generator.state,
      get_adjacent: int => list int,
    };
  };

  let init (width, height) hint_size ctx => {
    let (shape, scale, outsize) = Board.auto_size (width, height) hint_size;
    let coords = Board.coordinates shape |> Array.of_list;
    let coord_map = create_index_map coords;
    let count = Array.length coords;
    let gen_state = Generator.init count;
    let get_adjacent = get_adjacent shape coords coord_map;

    State.{count, shape, scale, outsize, gen_state, get_adjacent};
  };

  let step state => State.{
    ...state,
    gen_state: Generator.step state.get_adjacent state.gen_state
  };

  let loop state => State.(Generator.loop state.get_adjacent state.gen_state);
  let finished {State.gen_state} => Generator.finished gen_state;
  let edges {State.gen_state} => Generator.edges gen_state;
};
