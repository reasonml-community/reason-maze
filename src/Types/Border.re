
/* TODO maybe support 3d or something */
type t =
  | Arc (float, float, float, float, float)
  | Line ((float, float), (float, float));
  /* TODO arc */

let transform scale (dx, dy) t => {
  open Utils.Float;
  switch t {
  | Line ((x, y), (a, b)) => Line (
      (x * scale + dx, y * scale + dy),
      (a * scale + dx, b * scale + dy)
    )
  | Arc (x, y, r, t1, t2) => Arc (x * scale + dx, y * scale + dy, r * scale, t1, t2)
  }
};