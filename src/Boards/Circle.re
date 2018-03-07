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

let rec ring_counts = n =>
  if (n === 1) {
    [2];
  } else if (n === 2) {
    [4, 2];
  } else {
    switch (ring_counts(n - 1)) {
    | [x, ...rest] =>
      if (fi(n) *. tau /. fi(x) > 2.0) {
        [x * 2, x, ...rest];
      } else {
        [x, x, ...rest];
      }
    | _ => []
    };
  };

let counts = Array.of_list(List.rev(ring_counts(1000)));

let adjacents = (_size, (_x, y)) =>
  if (y == 0) {
    [Down, UpLeft, UpRight];
  } else {
    let this = counts[y];
    let next = counts[y + 1];
    if (next > this) {
      [UpLeft, UpRight, Left, Right, Down];
    } else {
      [Up, Left, Right, Down];
    };
  };

let adjacent_coord = (_size, (x, y), direction) =>
  switch (direction) {
  | Left => x > 0 ? (x - 1, y) : (counts[y] - 1, y)
  | Right => (x + 1 < counts[y] ? x + 1 : 0, y)
  | Down =>
    y === 0 ?
      ((x + 1) mod 2, y) :
      counts[y] === counts[y - 1] ? (x, y - 1) : (x / 2, y - 1)
  | Up => (x, y + 1)
  | UpLeft => (x * 2, y + 1)
  | UpRight => (x * 2 + 1, y + 1)
  };

let polar = (x, y, count) => {
  let theta = fi(x) /. fi(count) *. tau;
  (fi(y) *. cos(theta), fi(y) *. sin(theta));
};

let polarf = (x, y, count) => {
  let theta = x /. fi(count) *. tau;
  (y *. cos(theta), y *. sin(theta));
};

let direction_to_border = (_size, (x, y), direction) =>
  switch (direction) {
  | Left =>
    let count = counts[y];
    Border.Line((polar(x, y, count), polar(x, y + 1, count)));
  | Right =>
    let count = counts[y];
    Border.Line((polar(x + 1, y, count), polar(x + 1, y + 1, count)));
  | Down =>
    if (y === 0) {
      Border.Line((polar(0, 1, 2), polar(1, 1, 2)));
    } else {
      let count = counts[y] |> fi;
      Border.Arc((
        0.0,
        0.0,
        fi(y),
        fi(x) /. count *. tau,
        fi(x + 1) /. count *. tau,
      ));
    }
  | Up =>
    let count = counts[y] |> fi;
    Border.Arc((
      0.0,
      0.0,
      fi(y + 1),
      fi(x) /. count *. tau,
      fi(x + 1) /. count *. tau,
    ));
  | UpLeft =>
    let count = counts[y] |> fi;
    Border.Arc((
      0.0,
      0.0,
      fi(y + 1),
      fi(x) /. count *. tau,
      (0.5 +. fi(x)) /. count *. tau,
    ));
  | UpRight =>
    let count = counts[y] |> fi;
    Border.Arc((
      0.0,
      0.0,
      fi(y + 1),
      (0.5 +. fi(x)) /. count *. tau,
      fi(x + 1) /. count *. tau,
    ));
  };

let str_pos = ((a, b)) =>
  "(" ++ string_of_int(a) ++ ", " ++ string_of_int(b) ++ ")";

let coordinates = size => {
  let v = ref([]);
  for (y in 0 to size - 1) {
    let count = counts[y];
    for (x in 0 to count - 1) {
      v := [(x, y), ...v^];
    };
  };
  v^;
};

let auto_size = ((width, height), size) => {
  let dim = min(width, height);
  let rad = size / 2;
  let rad = rad < 1 ? 1 : rad;
  let scale = dim /. fi(rad * 2);
  (rad, scale, (dim, dim));
};

let offset = (size, scale, _) => {
  let dim = fi(size * 2) *. scale;
  let rad = dim /. 2.0;
  (rad, rad);
};

let tile_center = (size, scale, (x, y)) => {
  let (cx, cy) = offset(size, scale, ());
  let (ax, ay) =
    if (y === 0) {
      polarf(fi(x) +. 0.5, scale *. 0.5, 2);
    } else {
      polarf(fi(x) +. 0.5, scale *. (fi(y) +. 0.5), counts[y]);
    };
  (ax +. cx, ay +. cy);
};

/* TODO allow board to define a path edge, e.g. so I can have arc edges between nodes on the same level
   let path_edge size scale (a, b) (c, d) => {

   };
    */
let tile_at_coord = (_size, (x, y)) => {
  let count = counts[y] |> fi;
  Shape.Arc((
    (0.0, 0.0),
    fi(y),
    fi(y + 1),
    tau *. fi(x) /. count,
    tau *. fi(x + 1) /. count,
  ));
};

let from_point = (_, _, _) => (0, 0);
