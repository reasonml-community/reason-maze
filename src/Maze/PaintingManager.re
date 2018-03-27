open Belt;

module State = {
  type t('shape, 'coord, 'map) = {
    shape: 'shape,
    scale: float,
    outsize: (float, float),
    coords: array('coord),
    enabled: 'map,
  };
};

module F = (Board: SimpleBoard.T, Gen: Generator.T) => {
  include Manager.F(Board, Gen);

  /*  module BoardCoordComparator2 = (
          val Id.comparable(~cmp=Board.Coord.compare)
        );
      */ module BoardCoordComparator2 =
           Id.MakeComparable({
             type t = Board.Coord.t;

             let cmp = Board.Coord.compare;
           });

  let boardCoord2 = Map.make(~id=(module BoardCoordComparator2));

  let create_enabled_map = coords =>
    Array.reduce(coords, boardCoord2, (map, c) => Map.set(map, c, false));

  let paint_init = ((width, height), hint_size) => {
    let (shape, scale, outsize) =
      Board.auto_size((width, height), hint_size);
    let coords = Board.coordinates(shape) |> List.toArray;
    let enabled = create_enabled_map(coords);
    State.{shape, scale, outsize, coords, enabled};
  };

  let toggle_all = (state, coord) => {
    open State;
    let enabled =
      Board.adjacents(state.shape, coord)
      |> List.map(_, Board.adjacent_coord(state.shape, coord))
      |> List.reduce(_, state.State.enabled, (enabled, coord) =>
           Map.has(enabled, coord) ? Map.set(enabled, coord, true) : enabled
         );
    {...state, State.enabled};
  };

  let toggle_point = (state, (x, y)) => {
    open State;
    let {shape, scale, enabled} = state;
    let coord = Board.from_point(shape, scale, (x, y));
    if (Map.has(enabled, coord)) {
      let state = toggle_all(state, coord);
      let enabled = Map.set(state.enabled, coord, true);
      {...state, State.enabled};
    } else {
      state;
    };
  };

  let realize_state = ({State.shape, scale, outsize, coords, enabled}) => {
    let coords = Array.keep(coords, coord => Map.getExn(enabled, coord));
    switch (coords) {
    | [||] => None
    | coords =>
      let coord_map = create_index_map(coords);
      let count = Array.length(coords);
      let gen_state = Gen.init(count);
      let get_adjacent = get_adjacent(shape, coords, coord_map);
      Some(
        Manager.State.{
          count,
          shape,
          scale,
          outsize,
          gen_state,
          get_adjacent,
          coords,
          coord_map,
        },
      );
    };
  };

  let paint_walls = state =>
    switch (realize_state(state)) {
    | None => []
    | Some(mstate) => all_walls(mstate)
    };

  let paint_shapes = ({State.coords, scale, shape, enabled}) =>
    /*all_shapes (realize_state state)*/
    /*List.map*/
    Array.keep(coords, coord => Map.getExn(enabled, coord))
    |> Array.map(
         _,
         coord => {
           let offset = Board.offset(shape, scale, coord);
           let shape = Board.tile_at_coord(shape, coord);
           /*let visited = Array.get (Gen.visited gen_state) i;*/
           (
             Shape.transform(offset, scale, shape),
             Map.getExn(enabled, coord) ? 8 : 2,
           );
         },
       );
};
