
include SimpleBoard.FromTile (Tile.FromSimple SquareTile);
/*include SimpleBoard.FromTile TriangleTile;*/

type shape = (int, int);
/*module Coord = Coord2d;*/


let coordinates ((w, h): shape): list Coord.t => {
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
  ((hint_num, hint_num), size, (cwidth, cwidth))
};