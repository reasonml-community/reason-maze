
type shape =  (int, int);

let from_vertex (w, _) v => (v mod w, v / w);
let vertex_count (w, h) => w * h;

module Tile = Squares;

let in_bounds (w, h) (x, y) => x < w && y < h && x >= 0 && y >= 0;

let to_vertex (w, h) (x, y) => if (in_bounds (w, h) (x, y)) {
  Some (x + y * w);
} else {
  None
};

let all_coordinates (w, h) => {
  let rec inner x y => {
    if (x >= w) {
      inner 0 (y + 1)
    } else if (y >= h) {
      []
    } else {
      [(x, y), ...inner  (x + 1) y]
    }
  };
  /* TODO maybe make this tail call recursive? or switch to using an array? */
  inner 0 0;
};

let fi = float_of_int;

let coord_to_board (w, h) (x, y) (wsize, hsize) => {
  open Utils.Float;
  let dx = wsize / (fi w);
  let dy = hsize / (fi h);
  (((fi x) + 0.5) * dx, ((fi y) + 0.5) * dy);
};

/* TODO I should just give a square size? */
let scale (w, h) (wsize, hsize) => {
  wsize /. (fi w)
};

let border_walls shape size => {
  []
};
