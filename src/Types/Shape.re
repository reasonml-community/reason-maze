open Belt;

type t =
  | Polyline(list((float, float)))
  | Rect((float, float, float, float))
  | Arc(((float, float), float, float, float, float))
  | Circle(((float, float), float));

let transform = ((dx, dy), scale, shape) =>
  Utils.Float.(
    switch (shape) {
    | Rect((x, y, w, h)) =>
      Rect((x * scale + dx, y * scale + dy, w * scale, h * scale))
    | Circle(((x, y), r)) =>
      Circle(((x * scale + dx, y * scale + dy), r * scale))
    | Polyline(pts) =>
      Polyline(List.map(pts, ((x, y)) => (x * scale + dx, y * scale + dy)))
    | Arc(((cx, cy), y1, y2, t1, t2)) =>
      Arc((
        (cx * scale + dx, cy * scale + dy),
        y1 * scale,
        y2 * scale,
        t1,
        t2,
      ))
    }
  );
