open Belt;

module State = {
  type t('shape, 'gen_state, 'coord, 'direction, 'map) = {
    count: int,
    shape: 'shape,
    scale: float,
    outsize: (float, float),
    gen_state: 'gen_state,
    get_adjacent: int => list(int),
    coords: array('coord),
    coord_map: 'map,
  };
};

module F = (Board: SimpleBoard.T, Gen: Generator.T) => {
  module BoardCoordComparator =
    Id.MakeComparable({
      type t = Board.Coord.t;

      let cmp = Board.Coord.compare;
    });

  let boardCoord = Map.make(~id=(module BoardCoordComparator));

  let create_index_map = coords =>
    Array.reduce(coords, (0, boardCoord), ((i, map), c) =>
      (i + 1, Map.set(map, c, i))
    )
    |> snd;

  let get_adjacent = (shape, clist, cmap, i) => {
    let coord = Array.getExn(clist, i);
    Board.adjacents(shape, coord)
    |> List.map(_, Board.adjacent_coord(shape, coord))
    |> List.reduce(_, [], (adjacents, coord) =>
         Map.has(cmap, coord) ?
           [Map.getExn(cmap, coord), ...adjacents] : adjacents
       );
  };

  let init = ((width, height), hint_size) => {
    let (shape, scale, outsize) =
      Board.auto_size((width, height), hint_size);
    let coords = Board.coordinates(shape) |> List.toArray;
    let coord_map = create_index_map(coords);
    let count = Array.length(coords);
    let gen_state = Gen.init(count);
    let get_adjacent = get_adjacent(shape, coords, coord_map);
    State.{
      count,
      shape,
      scale,
      outsize,
      gen_state,
      get_adjacent,
      coords,
      coord_map,
    };
  };

  let step = state =>
    State.{
      ...state,
      gen_state: Gen.step(state.get_adjacent, state.gen_state),
    };

  let loop_to_end = state =>
    State.{
      ...state,
      gen_state: Gen.loop_to_end(state.get_adjacent, state.gen_state),
    };

  let finished = ({State.gen_state}) => Gen.finished(gen_state);

  let edges = ({State.gen_state}) => Gen.edges(gen_state);

  let max_age = ({State.count}) => count;

  let current_age = ({State.gen_state}) => Gen.max_age(gen_state);

  let all_edges = ({State.shape, scale, coords, gen_state}) => {
    let to_points = ((a, b)) => (
      Board.tile_center(shape, scale, Array.getExn(coords, a)),
      Board.tile_center(shape, scale, Array.getExn(coords, b)),
    );
    Set.reduce(Gen.edges(gen_state), [], (coll, pair) =>
      [to_points(pair), ...coll]
    );
  };

  let all_shapes = ({State.coords, shape, scale, gen_state}) =>
    Array.mapWithIndex(
      coords,
      (i, coord) => {
        let offset = Board.offset(shape, scale, coord);
        let shape = Board.tile_at_coord(shape, coord);
        let visited = Array.getExn(Gen.visited(gen_state), i);
        (Shape.transform(offset, scale, shape), visited);
      },
    );

  let all_walls = ({State.shape, scale, coords, coord_map, gen_state}) => {
    let edges = Gen.edges(gen_state);
    Array.reduce(
      coords,
      (0, []),
      ((i, walls), _coord) => {
        let coord = Array.getExn(coords, i);
        /*let make_border = Board.direction_to_border shape coord;*/
        let borders =
          List.keep(
            Board.adjacents(shape, coord),
            d => {
              let next = Board.adjacent_coord(shape, coord, d);
              /* borders */
              if (! Map.has(coord_map, next)) {
                true;
              } else {
                let nexti = Map.getExn(coord_map, next);
                /* dedup shared walls */
                if (nexti < i) {
                  false;
                } else {
                  ! Set.has(edges, (i, nexti));
                };
              };
            },
          )
          |> List.map(_, direction =>
               Border.transform(
                 scale,
                 Board.offset(shape, scale, coord),
                 Board.direction_to_border(shape, coord, direction),
               )
             );
        (i + 1, borders @ walls);
      },
    )
    |> snd;
  };
};
