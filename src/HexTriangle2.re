
type shape = int;
module Tile = Hex;

let raw_to_vertex a b s => {
  let res = ref 0;
  let v = ref 0;
  for y in 0 to (s - 1) {
    for x in 0 to (s - y - 1) {
      if (x == a && y == b) {res := !v};
      v := !v + 1;
    }
  };
  !res
};

let to_vertex size (x, y) => {
  x < 0 || y < 0 || x > size || y > size || x + y >= size
    ? None
    : Some (raw_to_vertex x y size)
};

let from_vertex size vertex => {
  let res = ref (0, 0);
  let i = ref 0;
  for y in 0 to (size - 1) {
    for x in 0 to (size - y - 1) {
      if (vertex === !i) {
        res := (x, y)
      };
      i := !i + 1;
    }
  };
  !res;
};

let vertex_count size => size * (size + 1) / 2;

let all_coordinates size => {
  let coords = ref [];
  for y in 0 to (size - 1) {
    for x in 0 to (size - y - 1) {
      coords := [(x, y), ...!coords];
    }
  };
  List.rev !coords;
};

let fi = float_of_int;

let coord_to_board size (x, y) (w, h) => {
  open Utils.Float;
  let length = w;
  let height = length / 2.0 * (sqrt 3.0);

  let sx = length / fi size / 2.0;
  let sy = height / fi size;

  let (fx, fy) = (fi x, fi y);
  let dx = sx * fx - sx * fy;
  let dy = sy * fx + sy * fy;

  (dx + length / 2.0, dy + (h - height) / 2.0);
};

let scale size (w, _) => {
   w /. (fi size)
};

let border_walls size => {
  let res = ref [];

  for x in 0 to (size - 1) {
    res := [
      ((x, 0), Hex.Yminus),
      ((x, 0), Hex.Zx),
      ...!res
    ];
  };

  for y in 0 to (size - 1) {
    res := [
      ((0, y), Hex.Xminus),
      ((0, y), Hex.Zy),
      ...!res
    ];
  };

  for x in 0 to (size - 1) {
    let y = size - 1 - x;
    res := [
      ((x, y), Hex.Yplus),
      ((x, y), Hex.Xplus),
      ...!res
    ];
  };

  !res
};

