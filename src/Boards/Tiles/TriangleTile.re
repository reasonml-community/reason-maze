
module Coord = Coord2d;
type direction =
  | Up
  | Down
  | Left
  | Right;

let sq3 = sqrt 3.0;
let qsq3 = sq3 /. 4.0;

let adjacents_simple is_flipped => is_flipped
  ? [Left, Right, Up]
  : [Left, Right, Down];

let adjacent_coord_simple direction => switch direction {
| Up => (- 1, - 1)
| Down => (+ 1, + 1)
| Left => (- 1, 0)
| Right => (+ 1, 0)
};

let topleft = (-0.5, -.qsq3);
let topright = (0.5, -.qsq3);
let topcenter = (0.0, -.qsq3);
let bottomleft = (-0.5, qsq3);
let bottomright = (0.5, qsq3);
let bottomcenter = (0.0, qsq3);

let direction_to_border_simple is_flipped direction => switch direction {
| Up => Border.Line (topleft, topright)
| Down => Border.Line (bottomleft, bottomright)
| Left => is_flipped
  ? Border.Line (bottomcenter, topleft)
  : Border.Line (topcenter, bottomleft)
| Right => is_flipped
  ? Border.Line (bottomcenter, topright)
  : Border.Line (topcenter, bottomright)
};

let is_flipped (x, _) => x mod 2 !== 0;

let adjacents pos => adjacents_simple (is_flipped pos);
let adjacent_coord _ => adjacent_coord_simple;
let direction_to_border pos => direction_to_border_simple (is_flipped pos);
