module State = {
  type t 'shape 'gen_state 'coord 'direction 'map = {
    count: int,
    shape: 'shape,
    scale: float,
    outsize: (float, float),
    gen_state: 'gen_state,
    get_adjacent: int => list int,
    coords: array 'coord,
    coord_map: 'map
  };
};

module F (Board: SimpleBoard.T) (Gen: Generator.T) => {
  module CoordMap = Map.Make Board.Coord;
  let create_index_map coords =>
    Array.fold_left (fun (i, map) c => (i + 1, CoordMap.add c i map)) (0, CoordMap.empty) coords
    |> snd;
  let get_adjacent shape clist cmap i => {
    let coord = clist.(i);
    Board.adjacents shape coord
    |> List.map (Board.adjacent_coord shape coord)
    |> List.fold_left
         (
           fun adjacents coord =>
             CoordMap.mem coord cmap ? [CoordMap.find coord cmap, ...adjacents] : adjacents
         )
         []
  };
  let init (width, height) hint_size => {
    let (shape, scale, outsize) = Board.auto_size (width, height) hint_size;
    let coords = Board.coordinates shape |> Array.of_list;
    let coord_map = create_index_map coords;
    let count = Array.length coords;
    let gen_state = Gen.init count;
    let get_adjacent = get_adjacent shape coords coord_map;
    State.{count, shape, scale, outsize, gen_state, get_adjacent, coords, coord_map}
  };
  let step state => State.{...state, gen_state: Gen.step state.get_adjacent state.gen_state};
  let loop_to_end state =>
    State.{...state, gen_state: Gen.loop_to_end state.get_adjacent state.gen_state};
  let finished {State.gen_state: gen_state} => Gen.finished gen_state;
  let edges {State.gen_state: gen_state} => Gen.edges gen_state;
  let max_age {State.count: count} => count;
  let current_age {State.gen_state: gen_state} => Gen.max_age gen_state;
  let all_edges {State.shape: shape, scale, coords, gen_state} => {
    let to_points (a, b) => (
      Board.tile_center shape scale coords.(a),
      Board.tile_center shape scale coords.(b)
    );
    Generator.PairSet.fold (fun pair coll => [to_points pair, ...coll]) (Gen.edges gen_state) []
  };
  let all_shapes {State.coords: coords, shape, scale, gen_state} =>
    Array.mapi
      (
        fun i coord => {
          let offset = Board.offset shape scale coord;
          let shape = Board.tile_at_coord shape coord;
          let visited = (Gen.visited gen_state).(i);
          (Shape.transform offset scale shape, visited)
        }
      )
      coords;
  let all_walls {State.shape: shape, scale, coords, coord_map, gen_state, get_adjacent} => {
    let edges = Gen.edges gen_state;
    Array.fold_left
      (
        fun (i, walls) coord => {
          let coord = coords.(i);
          let make_border = Board.direction_to_border shape coord;
          let borders =
            List.filter
              (
                fun d => {
                  let next = Board.adjacent_coord shape coord d;
                  /* borders */
                  if (not (CoordMap.mem next coord_map)) {
                    true
                  } else {
                    let nexti = CoordMap.find next coord_map;
                    /* dedup shared walls */
                    if (nexti < i) {
                      false
                    } else {
                      not (Generator.PairSet.mem (i, nexti) edges)
                    }
                  }
                }
              )
              (Board.adjacents shape coord)
            |> List.map (
                 fun direction =>
                   Border.transform
                     scale
                     (Board.offset shape scale coord)
                     (Board.direction_to_border shape coord direction)
               );
          (i + 1, borders @ walls)
        }
      )
      (0, [])
      coords
    |> snd
  };
};
