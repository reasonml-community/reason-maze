
include SimpleBoard.FromTile TriangleTile;

type shape = int;
/*module Coord = Coord2d;*/


let coordinates (size: shape) => {
  let v = ref [(0, 0)];
  /*
  for x in 0 to (w - 1) {
    for y in 0 to (h - 1) {
      v := [(x, y), ...!v];
    }
  };
  */
  !v;
};

/* TODO make it do things other than squares */
let auto_size (cwidth, cheight) hint_num => {
  let size = cwidth /. (float_of_int hint_num);
  (hint_num, size, (cwidth, cwidth *. (sqrt 3.0) /. 2.0))
};