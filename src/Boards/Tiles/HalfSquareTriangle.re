module Coord = Coord2d;

type direction =
  | Up
  | Down
  | Left
  | Right
  | TopHalf
  | BottomHalf;

let topleft = ((-0.5), (-0.5));

let topright = (0.5, (-0.5));

let bottomleft = ((-0.5), 0.5);

let bottomright = (0.5, 0.5);

let shape = Shape.Polyline([topleft, topright, bottomleft]);

let flipped_shape = Shape.Polyline([topright, bottomright, bottomleft]);

let adjacents_simple = is_flipped =>
  is_flipped ? [Right, Down, TopHalf] : [Up, Left, BottomHalf];

let adjacent_coord_simple = direction =>
  switch (direction) {
  | Up => (1, (-1))
  | Down => ((-1), 1)
  | Left => ((-1), 0)
  | Right => (1, 0)
  | TopHalf => ((-1), 0)
  | BottomHalf => (1, 0)
  };

let direction_to_border = (_, direction) =>
  switch (direction) {
  | Up => Border.Line((topleft, topright))
  | Down => Border.Line((bottomleft, bottomright))
  | Left => Border.Line((topleft, bottomleft))
  | Right => Border.Line((topright, bottomright))
  | BottomHalf
  | TopHalf => Border.Line((topright, bottomleft))
  };

let to_shape_simple = is_flipped => is_flipped ? flipped_shape : shape;

let is_flipped = ((x, _)) => x mod 2 !== 0;

let adjacents = pos => adjacents_simple(is_flipped(pos));

let adjacent_coord = ((x, y), direction) => {
  let (dx, dy) = adjacent_coord_simple(direction);
  (x + dx, y + dy);
};

let to_shape = pos => to_shape_simple(is_flipped(pos));
