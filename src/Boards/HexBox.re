
include SimpleBoard.FromTile (Tile.FromSimple HexTile);
type shape = int;

let coordinates shape => {
  let v = ref [];
  for x in 0 to (shape - 1) {
    for y in (-x) to (min (shape - x - 1) x) {
      v := [(x, y), ...!v];
    }
  };
  for x in shape to (shape * 2) {
    for y in (x - shape * 2 + 2) to (shape - x - 1) {
      v := [(x, y), ...!v];
    }
  };
  !v;
};

let fi = float_of_int;
let iof = int_of_float;

let width_to_height_ratio = 1.0 /. 2.0  *. (sqrt 3.0);

let auto_size (cwidth, cheight) hint_num => {
  let double = hint_num;
  let across = fi (double);
  open Utils.Float;
  if (cwidth * width_to_height_ratio < cheight ) {
    let size = cwidth / across;
    let height = size * width_to_height_ratio * (across + 0.25);
    Js.log (cwidth, height);
    (double, size, (cwidth, height))
  } else {
    let width = cheight / width_to_height_ratio;
    let size = width / (across + 0.25);
    (double, size, (width, cheight))
  }
};

let offset shape scale (x, y) => {
  let (fx, fy) = (fi (x), fi (y));
  let across = fi (shape * 2);
  open Utils.Float;
  let vsize = scale * 2.0 / (sqrt 3.0);
  let vertical = vsize * 0.75;
  (
    fx * scale / 2.0
    - fy * scale / 2.0
    + scale * width_to_height_ratio / 2.0
    /*- scale / 2.0*/
    ,
    /*+ 20.0,*/
    /*+ cx,*/
    fx * vertical
    + fy * vertical
    + vsize / 2.0
    /*+ cy,*/
    ,
  )
};

let from_point shape scale (x, y) => {
  open Utils.Float;
  let vsize = scale * 2.0 / (sqrt 3.0);
  let vertical = vsize * 0.75;

  let x' = x * 2.0 / scale - width_to_height_ratio;
  let y' = (y - vsize / 2.0) / vertical;

  let fy = (y' - x') / 2.0;
  let fx = x' + fy;

/*x' = fx - fy
y' = fx + fy
x' + fy = fx
y' = x' + fy + fy
y' = x' + 2fy
y' - x' = 2fy
fy = (y' - x') / 2.0
fx = x' + fy*/

  (int_of_float fx, int_of_float fy)
};

/*x' = x * 2.0 / scale - width_to_height_ratio = fx - fy
y' = (y - vsize / 2.0) / vertical = fx + fy

x' = fx - fy
y' = fx + fy
x' + fy = fx
y' = x' + fy + fy
y' = x' + 2fy
y' - x' = 2fy
fx = x' + fy*/

