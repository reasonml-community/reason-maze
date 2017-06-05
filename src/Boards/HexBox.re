
include SimpleBoard.FromTile (Tile.FromSimple HexTile);
type shape = int;

let coordinates shape => {
  let v = ref [];
  for x in 0 to (shape - 1) {
    for y in (-x) to (min (shape - x) x) {
      v := [(x, y), ...!v];
    }
  };
  for x in shape to (shape * 2) {
    for y in (x - shape * 2 + 2) to (shape - x) {
      v := [(x, y), ...!v];
    }
  };
  !v;
};

let fi = float_of_int;
let iof = int_of_float;

let width_to_height_ratio = 1.0 /. 2.0  *. (sqrt 3.0);

let auto_size (cwidth, cheight) hint_num => {
  let across = fi (hint_num);
  open Utils.Float;
  if (cwidth * width_to_height_ratio < cheight ) {
    let size = cwidth / across;
    let height = cwidth * width_to_height_ratio;
    Js.log (cwidth, height);
    (hint_num, size, (cwidth, height))
  } else {
    let width = cheight / width_to_height_ratio;
    let size = width / across;
    (hint_num, size, (width, cheight))
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

