
module Coord = Coord2d;

type direction =
  | UpRight
  | UpLeft
  | DownRight
  | DownLeft
  | Left
  | Right;

let adjacents = [
  UpRight,
  UpLeft,
  DownRight,
  DownLeft,
  Left,
  Right,
];

let adjacent_coord direction => switch direction {
| UpRight => (0, -1)
| UpLeft => (-1, 0)
| DownRight => (1, 0)
| DownLeft => (0, 1)
| Left => (-1, 1)
| Right => (1, -1)
};

let hsq3 = sqrt 3.0 /. 2.0;
let isq3 = 1.0 /. (sqrt 3.0);

let top = (0.0, -.isq3);
let bottom = (0.0, isq3);
let tl = (-0.5, -.hsq3 +. isq3);
let tr = (0.5, -.hsq3 +. isq3);
let bl = (-0.5, hsq3 -. isq3);
let br = (0.5, hsq3 -. isq3);

let direction_to_border direction => {
  open Utils.Float;
  Border.Line (switch direction {
| UpRight => (top, tr)
| UpLeft => (top, tl)
| DownRight => (bottom, br)
| DownLeft => (bottom, bl)
| Left => (tl, bl)
| Right => (tr, br)
});
};

let shape = Shape.Polyline [
  top,
  tr,
  br,
  bottom,
  bl,
  tl
];