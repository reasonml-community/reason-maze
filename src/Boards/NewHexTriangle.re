include SimpleBoard.FromTile((Tile.FromSimple(HexTile)));

type shape = int;

let coordinates = shape => {
  let v = ref([]);
  for (y in 0 to shape - 1) {
    for (x in 0 to shape - y - 1) {
      v := [(x, y), ...v^];
    };
  };
  v^;
};

let fi = float_of_int;

let iof = int_of_float;

let auto_size = ((cwidth, cheight), hint_num) =>
  Utils.Float.(
    if (cwidth < cheight / sqrt(3.0) * 2.0) {
      let size = cwidth / fi(hint_num);
      let height = cwidth * sqrt(3.0) / 2.0;
      (hint_num, size, (cwidth, height));
    } else {
      let width = cheight / sqrt(3.0) * 2.0;
      let size = width / fi(hint_num);
      (hint_num, size, (width, cheight));
    }
  );

let offset = (shape, scale, (x, y)) => {
  open Utils.Float;
  let (fx, fy) = (fi(x), fi(y));
  let vsize = scale * 2.0 / sqrt(3.0);
  /*let vertical = scale / 2.0 + vsize / 2.0;*/
  let vertical = vsize * 0.75;
  (
    /*scale / 2.0,
      vsize / 2.0*/
    /*fx * scale,
      fy * vsize*/
    fx * scale / 2.0 - fy * scale / 2.0 + fi(shape) / 2.0 * scale,
    fx * vertical + fy * vertical + vsize / 2.0,
  );
};

let tile_center = offset;

let from_point = (_, _, _) => (0, 0);
