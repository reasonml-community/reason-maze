module Coord = Coord2d;

type direction =
  | Up
  | Down
  | Left
  | Right
  | UpLeft
  | UpRight
  | DownLeft
  | DownRight;

let topleft = ((-0.5), (-0.5));

let topright = (0.5, (-0.5));

let bottomleft = ((-0.5), 0.5);

let bottomright = (0.5, 0.5);

type tile =
  | TL
  | TR
  | BL
  | BR;

let shape = tile =>
  switch (tile) {
  | TL => [topleft, topright, bottomleft]
  | TR => [topleft, topright, bottomright]
  | BL => [bottomleft, bottomright, topleft]
  | BR => [bottomleft, bottomright, topright]
  };

let adjacents = tile =>
  switch (tile) {
  | TL => [Up, Left, DownRight]
  | TR => [Up, Right, DownLeft]
  | BR => [Down, Right, UpLeft]
  | BL => [Down, Left, UpRight]
  };

let adjacent_coord = direction =>
  switch (direction) {
  | Left => ((-1), 0)
  | Right => (1, 0)
  | UpLeft => ((-1), 0)
  | UpRight => (1, 0)
  | DownLeft => ((-1), 0)
  | DownRight => (1, 0)
  | Up => (0, (-1))
  | Down => (0, 1)
  };

let direction_to_border = (_, direction) =>
  switch (direction) {
  | Up => Border.Line((topleft, topright))
  | Down => Border.Line((bottomleft, bottomright))
  | Left => Border.Line((topleft, bottomleft))
  | Right => Border.Line((topright, bottomright))
  | UpLeft
  | DownRight => Border.Line((topright, bottomleft))
  | DownLeft
  | UpRight => Border.Line((topleft, bottomright))
  };

exception Unreachable;

let tile = ((x, y)) =>
  switch (x mod 2, (y + x / 2) mod 2) {
  | (0, 0) => TL
  | (1, 0) => BR
  | (0, 1) => BL
  | (1, 1) => TR
  | _ => raise(Unreachable)
  };

let adjacents = pos => adjacents(tile(pos));

let adjacent_coord = ((x, y), direction) => {
  let (dx, dy) = adjacent_coord(direction);
  (x + dx, y + dy);
};

let to_shape = pos => Shape.Polyline(shape(tile(pos)));
