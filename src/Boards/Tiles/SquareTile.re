
module Coord = Coord2d;

type direction =
  | Up
  | Down
  | Left
  | Right;

let adjacents = [
  Up,
  Down,
  Left,
  Right,
];

let adjacent_coord direction => switch direction {
| Up => (0, - 1)
| Down => (0, + 1)
| Left => (- 1, 0)
| Right => (+ 1, 0)
};

let direction_to_border direction => switch direction {
| Up => Border.Line ((-0.5, -0.5), (0.5, -0.5))
| Down => Border.Line ((-0.5, 0.5), (0.5, 0.5))
| Left => Border.Line ((-0.5, -0.5), (-0.5, 0.5))
| Right => Border.Line ((0.5, -0.5), (0.5, 0.5))
};