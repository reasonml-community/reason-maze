
include SimpleBoard.FromTile (Tile.FromSimple HexTile);
type shape = int;

let coordinates shape => {
  let v = ref [];
  /*
  */
  for y in 0 to (shape - 1) {
    for x in 0 to (shape - y - 1) {
      v := [(x, y), ...!v]
    }
  };
  for y in 0 to (shape - 2) {
    for x in y to (shape - 2) {
      v := [(-x-1, y), ...!v]
    }
  };
  for y in 0 to (shape - 2) {
    for x in y to (shape - 2) {
      v := [(x+1, -y-1), ...!v]
    }
  };
  for y in 0 to (shape - 2) {
    for x in 0 to (shape - y - 2) {
      v := [(-x, -y-1), ...!v]
    }
  };
  for x in 0 to (shape - 2) {
    for y in x to (shape - 2) {
      v := [(-x-1, y+1), ...!v]
    }
  };
  for x in 0 to (shape - 2) {
    for y in x to (shape - 3) {
      v := [(x+1, -y-2), ...!v]
    }
  };
  /*
  */
  !v;
};

let fi = float_of_int;
let iof = int_of_float;

let auto_size (cwidth, cheight) hint_num => {
  open Utils.Float;
  if (cwidth < cheight / (sqrt 3.0) * 2.0) {
    let size = cwidth / (fi hint_num) / 2.0;
    let height = cwidth * (sqrt 3.0) / 2.0;
    (hint_num, size, (cwidth, height))
  } else {
    let width = cheight / (sqrt 3.0) * 2.0;
    let size = width / (fi hint_num) / 2.0;
    (hint_num, size, (width, cheight))
  }
};

let offset shape scale (x, y) => {
  let (fx, fy) = (fi (x), fi (y));
  let across = fi (shape * 2 + 1);
  open Utils.Float;
  let cx = scale * across / 2.0;
  let vsize = scale * 2.0 / (sqrt 3.0);
  let vertical = vsize * 0.75;
  let cy = vertical * across / 2.0;
  (
    fx * scale / 2.0
    - fy * scale / 2.0
    + cx,
    /*+ (fi shape) / 2.0 * scale,*/
    fx * vertical
    + fy * vertical
    + cy,
    
  )
};


/*
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
*/

