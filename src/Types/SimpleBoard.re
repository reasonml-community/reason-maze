
module type T = {
  type shape;
  module Coord: Coord.T;
  let coordinates: shape => list Coord.t;
  let auto_size: (float, float) => int => (shape, float, (float, float));

  /* Stuff that can be used from a simple tile definition */
  type direction;
  let adjacents: shape => Coord.t => list direction;
  let adjacent_coord: shape => Coord.t => direction => Coord.t;
  let direction_to_border: shape => Coord.t => direction => Border.t;
};

module FromTile (Tile: Tile.T)/*: (T with module Coord := Tile.Coord)*/ => {
  type direction = Tile.direction;
  module Coord = Tile.Coord;
  let adjacents _ => Tile.adjacents;
  let adjacent_coord _ => Tile.adjacent_coord;
  let direction_to_border _ => Tile.direction_to_border;
};
