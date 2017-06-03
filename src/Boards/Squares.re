
let adjacent _ => [
  (-1, 0),
  ( 1, 0),
  (0, -1),
  (0,  1)
];

type direction =
  | Up
  | Down
  | Left
  | Right;

let to_direction (dx, dy) => {
  switch (dx, dy) {
    | (-1, 0) => Some Left
    | ( 1, 0) => Some Right
    | (0, -1) => Some Up
    | (0,  1) => Some Down
    | _ => None
  }
};

let wall_in_direction direction => {
  let pts = switch direction {
    | Up => ((-0.5, -0.5), (0.5, -0.5))
    | Down => ((-0.5, 0.5), (0.5, 0.5))
    | Left => ((-0.5, -0.5), (-0.5, 0.5))
    | Right => ((0.5, -0.5), (0.5, 0.5))
  };
  Shared.Line pts;
};

