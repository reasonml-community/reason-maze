
include SimpleBoard.FromTile (Tile.FromSimple SquareTile);

type shape = (int, int);

let coordinates ((w, h): shape): list Coord.t => {
  let v = ref [];
  for x in 0 to (w - 1) {
    for y in 0 to (h - 1) {
      v := [(x, y), ...!v];
    }
  };
  !v;
};

let fi = float_of_int;
let iof = int_of_float;

let auto_size (cwidth, cheight) hint_num => {
  let dim = min cwidth cheight;
  let size = dim /. (fi hint_num);
  let width = iof (cwidth /. size);
  let height = iof (cheight /. size);
  ((width, height), size, ((fi width) *. size, (fi height) *. size))
};