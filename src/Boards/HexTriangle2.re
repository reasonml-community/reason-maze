
type shape = int;
module Tile = Hex;

/*
let run_loop a0 b0 aMax getBMax fn => {
  let rec inner a b i bMax => {
    fn a b i;
    if (b >= bMax) {
      inner (a + 1) 0 (i + 1) (getBMax (a + 1))
    } else if (a < aMax) {
      inner a (b + 1) (i + 1) bMax
    } else {
      ()
    }
  };
  inner a0 b0 0 (getBMax a0);
};

let reduce_loop a0 b0 aMax getBMax fn init => {
  let rec inner coll a b i bMax => {
    let coll = fn coll a b i;
    if (b >= bMax) {
      inner coll (a + 1) 0 (i + 1) (getBMax (a + 1))
    } else if (a < aMax) {
      inner coll a (b + 1) (i + 1) bMax
    } else {
      coll
    }
  };
  inner init a0 b0 0 (getBMax a0);
};

let double_loop a0 b0 aMax getBMax fn => {
  let rec inner a b i bMax => {
    switch (fn a b i) {
      | Some x => Some x
      | None => {
        if (b >= bMax) {
          inner (a + 1) 0 (i + 1) (getBMax (a + 1))
        } else if (a < aMax) {
          inner a (b + 1) (i + 1) bMax
        } else {
          None
        }
      }
    }
  };
  inner a0 b0 0 (getBMax a0);
};

let iter_vertices size fn => {
  double_loop 0 0 (size - 1) (fun y => size - y - 1) fn
};

let optor orr opt => switch opt { |None => orr |Some x => x};

let raw_to_vertex x y size => {
  iter_vertices size (fun a b v => {
    if (a == x && b === y) {
      Some v
    } else {
      None
    }
  })
};

let from_vertex size vertex => {
  iter_vertices size (fun a b v => {
    if (v === vertex) {
      Some (a, b)
    } else {
      None
    }
  }) |> optor (0, 0)
};
*/

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

let find arr x => {
  let rec inner i => {
    if (Array.get arr i == x) {
      Some i
    } else if (i > Array.length arr) {
      None
    } else {
      inner (i + 1)
    }
  };
  inner 0;
};

/*
let to_vertex size coords (x, y) => {
  find coords (x, y);
};
*/

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
  let res = Array.make (vertex_count size) (0, 0);
  let i = ref 0;
  for y in 0 to (size - 1) {
    for x in 0 to (size - y - 1) {
      Array.set res !i (x, y);
      i := !i + 1;
    }
  };
  res;
};

let fi = float_of_int;

let coord_to_board size (w, h) (x, y) => {
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

