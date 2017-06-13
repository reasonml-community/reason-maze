
module Coord = Coord2d;
type shape = int;
type direction =
  | Left
  | Right
  | Down
  | Up
  | UpLeft
  | UpRight;

let pi: float = [%bs.raw "Math.PI"];
let tau = pi *. 2.0;

let fi = float_of_int;

let rec ring_counts n => {
  if (n === 1) {
    [2]
  } else if (n === 2) {
    [4, 2]
  } else {
    switch (ring_counts (n - 1)) {
    | [x, ...rest] => {
      if ((fi n) *. tau /. (fi x) > 2.0 ) {
        [x * 2, x, ...rest]
      } else {
        [x, x, ...rest]
      }
    }
    | _ => []
    }
  }
};

let counts = Array.of_list (List.rev (ring_counts 1000));

let adjacents size (x, y) => {
  if (y == 0) {
    [Down, UpLeft, UpRight];
  } else {
    let this = Array.get counts y;
    let next = Array.get counts (y + 1);
    if (next > this) {
      [UpLeft, UpRight, Left, Right, Down]
    } else {
      [Up, Left, Right, Down]
    }
  }
};

let adjacent_coord size (x, y) direction => switch direction {
| Left => x > 0 ? (x - 1, y) : ((Array.get counts y) - 1, y)
| Right => (x + 1 < Array.get counts y ? x + 1 : 0, y)
| Down => {
  y === 0 ? ((x + 1) mod 2, y) :
  (
  Array.get counts y === Array.get counts (y - 1)
  ? (x, y - 1)
  : (x / 2, y -1)
  )
}
| Up => (x, y + 1)
| UpLeft => (x * 2, y + 1)
| UpRight => (x * 2 + 1, y + 1)
};

let polar x y count => {
  let theta = (fi x) /. (fi count) *. tau;
  (
    (fi y) *. (cos theta),
    (fi y) *. (sin theta)
  );
};

let direction_to_border size (x, y) direction => switch direction {
| Left => {
  let count = Array.get counts y;
  Border.Line (polar x y count, polar x (y + 1) count)
}
| Right => {
  let count = Array.get counts y;
  Border.Line (polar (x + 1) y count, polar (x + 1) (y + 1) count)
}
| Down => {
  if (y === 0) {
    Border.Line (
      (polar 0 1 2),
      (polar 1 1 2),
    )
  } else {
  let count = Array.get counts y |> fi;
  Border.Arc (
    0.0,
    0.0,
    (fi y),
    (fi x) /. count *. tau,
    (fi (x + 1)) /. count *. tau
  )
  }
}
| Up => {
  let count = Array.get counts y |> fi;
  Border.Arc (
    0.0,
    0.0,
    (fi (y + 1)),
    (fi x) /. count *. tau,
    (fi (x + 1)) /. count *. tau
  )
}
| UpLeft => {
  let count = Array.get counts y |> fi;
  Border.Arc (
    0.0,
    0.0,
    (fi (y + 1)),
    (fi x) /. count *. tau,
    (0.5 +. fi x) /. count *. tau,
  )
}
| UpRight => {
  let count = Array.get counts y |> fi;
  Border.Arc (
    0.0,
    0.0,
    (fi (y + 1)),
    (0.5 +. fi x) /. count *. tau,
    (fi (x + 1)) /. count *. tau,
  )
}
};

let str_pos (a, b) => "(" ^ (string_of_int a) ^ ", " ^ (string_of_int b) ^ ")";

let coordinates size => {
  let v = ref [];
  for y in 0 to (size - 1) {
    let count = Array.get counts y;
    for x in 0 to (count - 1) {
      v := [(x, y), ...!v];
    }
  };
  !v;
}
[@@test [
  (1, [(1, 0), (0, 0)]),
  (1, [(3, 1), (2, 1), (1, 1), (0, 1), (1, 0), (0, 0)])
]]
[@@test.show fun arr => String.concat "," (List.map str_pos arr)];

let auto_size (width, height) size => {
  let dim = min width height;
  let rad = size / 2;
  let rad = rad < 1 ? 1 : rad;
  let scale = dim /. (fi (rad * 2));
  (rad, scale, (dim, dim))
};

let offset size scale (x, y) => {
  let (ax, ay) = polar (x + 0) y (Array.get counts y);
  let dim = (fi (size * 2)) *. scale;
  let rad = dim /. 2.0;
  (ax +. rad, ay +. rad)
  /*(ax *. scale +. rad, ay *. scale +. rad)*/
}
[@@test [
  ((2, 1.0, (0, 0)), (0.0, 0.0))
]]
;

let tile_at_coord size (x, y) => {
  let count = Array.get counts y |> fi;
  Shape.Arc ((0.0, 0.0), (fi y), (fi (y + 1)), tau *. (fi x) /. count, tau *. (fi (x + 1)) /. count)
};

let from_point _ _ _ => (0, 0);