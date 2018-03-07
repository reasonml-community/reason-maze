module type T = {
  type shape;
  /* Stuff that can be derived from a Tile.T definition */
  module Coord: Coord.T;
  type direction;
  let adjacents: (shape, Coord.t) => list(direction);
  let adjacent_coord: (shape, Coord.t, direction) => Coord.t;
  let direction_to_border: (shape, Coord.t, direction) => Border.t;
  let coordinates: shape => list(Coord.t);
  /* TODO need to make a "output coord" or something? */
  let auto_size:
    ((float, float), int) =>
    (shape, float /* unit size */, (float, float) /* full size */);
  let offset: (shape, float, Coord.t) => (float, float);
  let tile_center: (shape, float, Coord.t) => (float, float);
  let tile_at_coord: (shape, Coord.t) => Shape.t;
  let from_point: (shape, float, (float, float)) => Coord.t;
};

module FromTile = (Tile: Tile.T) => {
  type direction = Tile.direction;
  module Coord = Tile.Coord;
  let adjacents = (_) => Tile.adjacents;
  let adjacent_coord = (_) => Tile.adjacent_coord;
  let direction_to_border = (_) => Tile.direction_to_border;
  let tile_at_coord = (_) => Tile.to_shape;
};
