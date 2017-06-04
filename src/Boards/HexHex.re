
type shape = int;
module Tile = Hex;

let triangle n => (n * (n + 1)) / 2;

let raw_to_vertex x y => {
  x === 0 ? 0
  : (triangle (x - 1)) * 6 + y
};

let to_vertex size (x, y) => {
  x >= size
    ? None
    : Some (raw_to_vertex x y)
};

let from_vertex size vertex => {
  let rec loop x i => {
    let n = x + (i * 6);
    if (n > vertex) {
      (i, vertex - x)
    } else {
      loop n (i + 1)
    }
  };
  loop 1 0
};

let vertex_count size => 1 + (triangle size) * 6;

let all_coordinates size => {
  let coords = ref [];
  for x in 0 to (size - 1) {
    for y in 0 to (x * 6) {
      coords := [(x, y), ...!coords];
    }
  };
  List.rev !coords;
};

let fi = float_of_int;

let coord_to_board size (w, h) (x, y) => {
  open Utils.Float;
  let length = w / 2.0;
  let height = length / 2.0 * (sqrt 3.0);

  let sx = length / fi size / 2.0;
  let sy = height / fi size;

  let (fx, fy) = (fi x, fi y);
  let dx = sx * fx - sx * fy;
  let dy = sy * fx + sy * fy;

  (dx + length, dy + (h - height * 2.0) / 2.0);
};

let scale size (w, _) => {
   w /. 2.0 /. (fi size)
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


