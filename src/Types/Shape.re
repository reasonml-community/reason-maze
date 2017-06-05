
type t =
  | Polyline (list (float, float))
  | Rect (float, float, float, float)
  | Circle ((float, float), float);

let transform (dx, dy) scale shape => Utils.Float.(switch shape {
| Rect (x, y, w, h) => Rect (x * scale + dx, y * scale + dy, w * scale, h * scale)
| Circle ((x, y), r) => Circle ((x * scale + dx, y * scale + dy), r * scale)
| Polyline pts => Polyline (List.map (fun (x, y) => (x * scale + dx, y * scale + dy)) pts)
});