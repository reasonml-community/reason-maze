
include SimpleBoard.FromTile TriangleTile;

type shape = int;

let coordinates (size: shape) => {
  let v = ref [];
  for y in 0 to (size - 1) {
    for x in 0 to (y * 2 ) {
      v := [(x, y), ...!v];
    }
  };
  !v;
};

let auto_size (cwidth, cheight) hint_num => {
  let size = cwidth /. (float_of_int hint_num);
  (hint_num, size, (cwidth, cwidth *. (sqrt 3.0) /. 2.0))
};

let hsq3 = (sqrt 3.0) /. 2.0;

let fi = float_of_int;
let offset shape scale (x, y) => {
  open Utils.Float;
  let (fx, fy) = ((fi x), (fi y));
  (
    (fx - fy) / 2.0 * scale + ((fi shape) / 2.0) * scale,
    (fy + 0.5) * hsq3 * scale,
  )
  /*(
    (-. fx / 2.0 + fy / 2.0) * scale + scale * ((fi shape) / 2.0),
    (fy * hsq3 + fx * hsq3) * scale + scale / 2.0 * hsq3,
  )*/
};