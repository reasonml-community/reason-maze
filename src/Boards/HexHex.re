
include SimpleBoard.FromTile (Tile.FromSimple HexTile);
type shape = int;

let coordinates shape => {
  let v = ref [];
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
  !v;
};

let fi = float_of_int;
let iof = int_of_float;

let width_to_height_ratio = 1.0 /. 2.0  *. (sqrt 3.0);

let auto_size (cwidth, cheight) hint_num => {
  let hint_num = hint_num / 2;
  let across = fi (hint_num * 2 - 1);
  open Utils.Float;
  if (cwidth * width_to_height_ratio < cheight ) {
    let size = cwidth / across;
    let height = cwidth * width_to_height_ratio;
    (hint_num, size, (cwidth, height))
  } else {
    let width = cheight / width_to_height_ratio;
    let size = width / across;
    (hint_num, size, (width, cheight))
  }
};

let offset shape scale (x, y) => {
  let (fx, fy) = (fi (x), fi (y));
  let across = fi (shape * 2 - 1);
  open Utils.Float;
  let cx = scale * across / 2.0;
  let vsize = scale * 2.0 / (sqrt 3.0);
  let vertical = vsize * 0.75;
  let cy = vertical * across / 2.0;
  (
    fx * scale / 2.0
    - fy * scale / 2.0
    + cx,
    fx * vertical
    + fy * vertical
    + cy,
  )
};
let tile_center = offset;

let from_point _ _ _ => (0, 0);