
type shape = int;

let vertex_count size => {
  size * (size + 1) / 2
};

let from_vertex v s => {
  let res = ref (0, 0);
  let i = ref 0;
  for y in 0 to (s - 1) {
    for x in 0 to (s - y - 1) {
      if (v === !i) {res := (x, y)};
      i := !i + 1;
    }
  };
  !res;
};

let to_vertex a b s => {
  let res = ref 0;
  let v = ref 0;
  for y in 0 to (s - 1) {
    for x in 0 to (s - y - 1) {
      if (x == a && y == b) {res := !v};
      v := !v + 1;
    }
  };
  !res
};

let maybe_vertex size (x, y) => {
  x < 0 || y < 0 || x > size || y > size || x + y >= size
    ? None
    : Some (to_vertex x y size)
};

let optmap fn lst => List.fold_left
  (fun res v => switch (fn v) {
    | None => res
    | Some x => [x, ...res]
  }) [] lst;

let adjacency_list size => {
  let v = Array.make (vertex_count size) [];
  for x in 0 to (size - 1) {
    for y in 0 to (size - x - 1) {
      let neighbors = [
        (x - 1, y),
        (x + 1, y),
        (x, y - 1),
        (x, y + 1),
        (x - 1, y + 1),
        (x + 1, y - 1),
      ];
      let connections = (optmap (maybe_vertex size) neighbors);
      Array.set v (to_vertex x y size) connections;
    }
  };
  v
};

let fi = float_of_int;

let point_pos (x, y) size (w, h) => {
  open Utils.Float;
  let length = w;
  let height = length / 2.0 * (sqrt 3.0);

  let sx = length / fi size / 2.0;
  let sy = height / fi size;

  let (fx, fy) = (fi x, fi y);
  let dx = sx * fx - sx * fy;
  let dy = sy * fx + sy * fy;

  (dx + length / 2.0, dy + (h - height) / 2.0);
};

let vertex_pos v size (w, h) => {
  let (x, y) = from_vertex v size;
  point_pos (x, y) size (w, h)
};

type direction =
  | Xminus
  | Xplus
  | Yminus
  | Yplus
  | Zx
  | Zy;

let direction_of_points src dest (x, y) (a, b) => {
  switch true {
    | _ when (x + 1 === a && y - 1 === b) => Zx
    | _ when (x - 1 === a && y + 1 === b) => Zy
    | _ when (x + 1 === a && y === b) => Xplus
    | _ when (x - 1 === a && y === b) => Xminus
    | _ when (y + 1 === b && x === a) => Yplus
    | _ when (y - 1 === b && x === a) => Yminus
    | _ => {
      Js.log ("bad dir", x, y, a, b, src, dest);
      Zx
      }
  }
};

let sq3 = sqrt 3.0;

let wall_in_direction fx fy u direction => {
  open Utils.Float;
  switch direction {
    | Zx => {
        (
          (fx + u / 2.0, fy + u * sq3 / 2.0 - u / sq3),
          (fx + u / 2.0, fy - u * sq3 / 2.0 + u / sq3)
        )
      }
    | Zy => {
        (
          (fx - u / 2.0, fy + u * sq3 / 2.0 - u / sq3),
          (fx - u / 2.0, fy - u * sq3 / 2.0 + u / sq3)
        )
      }
    | Yminus => {
        (
          (fx, fy - u / sq3),
          (fx + u / 2.0, fy - u * sq3 / 2.0 + u / sq3)
        )
      }
    | Yplus => {
        (
          (fx, fy + u / sq3),
          (fx - u / 2.0, fy + u * sq3 / 2.0 - u / sq3)
        )
      }
    | Xminus => {
        (
          (fx, fy - u / sq3),
          (fx - u / 2.0, fy - u * sq3 / 2.0 + u / sq3)
        )
      }
    | Xplus => {
        (
          (fx, fy + u / sq3),
          (fx + u / 2.0, fy + u * sq3 / 2.0 - u / sq3)
        )
      }
  }
};

let border_walls size csize => {
  let res = ref [];
  let (w, _) = csize;
  let u = w /. (fi size);
  for x in 0 to (size - 1) {
    let (fx, fy) = point_pos (x, 0) size csize;
    res := [
      Shared.Line (wall_in_direction fx fy u Yminus),
      Shared.Line (wall_in_direction fx fy u Zx),
      ...!res
    ];
  };
  for y in 0 to (size - 1) {
    let (fx, fy) = point_pos (0, y) size csize;
    res := [
      Shared.Line (wall_in_direction fx fy u Xminus),
      Shared.Line (wall_in_direction fx fy u Zy),
      ...!res
    ];
  };
  for x in 0 to (size - 1) {
    let y = size - 1 - x;
    let (fx, fy) = point_pos (x, y) size csize;
    res := [
      Shared.Line (wall_in_direction fx fy u Yplus),
      Shared.Line (wall_in_direction fx fy u Xplus),
      ...!res
    ];
  };
  !res
};

let drawable_wall (src, dest) size csize => {
  let (x, y) = from_vertex src size;
  let (a, b) = from_vertex dest size;
  let (w, _) = csize;
  open Utils.Float;
  let u = w / (fi size);
  let direction = (direction_of_points src dest (x, y) (a, b));
  let (fx, fy) = point_pos (x, y) size csize;
  let pts = wall_in_direction fx fy u direction;
  Shared.Line pts;
};

