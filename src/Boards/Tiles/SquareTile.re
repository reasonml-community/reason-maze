module Coord = Coord2d;

type direction =
  | Up
  | Down
  | Left
  | Right;

let adjacents = [Up, Down, Left, Right];

let adjacent_coord = direction =>
  switch (direction) {
  | Up => (0, (-1))
  | Down => (0, 1)
  | Left => ((-1), 0)
  | Right => (1, 0)
  };

let topleft = ((-0.5), (-0.5));

let topright = (0.5, (-0.5));

let bottomleft = ((-0.5), 0.5);

let bottomright = (0.5, 0.5);

let direction_to_border = direction =>
  switch (direction) {
  | Up => Border.Line((topleft, topright))
  | Down => Border.Line((bottomleft, bottomright))
  | Left => Border.Line((topleft, bottomleft))
  | Right => Border.Line((topright, bottomright))
  };

/*let shape = Shape.Polyline [
    topleft,
    topright,
    bottomright,
    bottomleft,
    /*(bottomleft, topleft),*/
  ];
  */
let shape = Shape.Rect(((-0.5), (-0.5), 1.0, 1.0));
