include SimpleBoard.FromTile EquilateralTriangle;

type shape = int;

let coordinates (size: shape) => {
  let v = ref [];
  for y in 0 to (size - 1) {
    for x in 0 to (y * 2) {
      v := [(x, y), ...!v]
    }
  };
  !v
};

let auto_size (cwidth, cheight) hint_num => {
  let size = cwidth /. float_of_int hint_num;
  (hint_num, size, (cwidth, cwidth *. sqrt 3.0 /. 2.0))
};

let hsq3 = sqrt 3.0 /. 2.0;

let fi = float_of_int;

let offset shape scale (x, y) => {
  open Utils.Float;
  let (fx, fy) = (fi x, fi y);
  ((fx - fy + fi shape) / 2.0 * scale, (fy + 0.5) * hsq3 * scale)
};

let offcenter = 0.5 -. 0.5 /. sqrt 3.0;

let tile_center shape scale (x, y) => {
  let (ax, ay) = offset shape scale (x, y);
  let dy =
    if (EquilateralTriangle.is_flipped (x, y)) {
      -. scale
      *. offcenter
      /. 1.5
      /*-.scale *. hsq3 /. 4.0*/
    } else {
      scale
      *. offcenter
      /. 1.5
      /*scale *. hsq3 /. 4.0*/
    };
  (ax, ay +. dy)
};

let from_point shape scale (x, y) => {
  /*x = (fx - fy) / 2.0 * scale + ((fi shape) / 2.0) * scale,
    x = ((fx - fy) + shape) / 2.0 * scale;
    x * 2.0 / scale = fx - fy + shape;
    x * 2.0 / scale - shape + fy = fx
    fx = x * 2.0 / scale - shape + fy
    y = (fy + 0.5) * hsq3 * scale
    fy = y / hsq3 / scale - 0.5;*/
  let fshape = fi shape;
  open Utils.Float;
  let fy = y / hsq3 / scale - 0.5;
  let fx = x * 2.0 / scale - fshape + fy;
  (int_of_float fx, int_of_float fy)
};
