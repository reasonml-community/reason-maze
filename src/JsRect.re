
type b;
type t = (int, int, b);
module Direction = {
  type t =
    | Up
    | Down
    | Left
    | Right;
};

let board: int => int => b = [%bs.raw {|
  function (w, h) {
    var b = {v: [], h: []}
    for (var x=0; x<w-1; x++) {
      var r = []
      b.v.push(r)
      for (var y=0;y<h;y++) {
        r.push(0)
      }
    }
    for (var x=0; x<w; x++) {
      var r = []
      b.h.push(r)
      for (var y=0;y<h-1;y++) {
        r.push(0)
      }
    }
    return b
  }
|}];

let create w h => (w, h, board w h);
let adjacent (w, h, _) (x, y) => {
  List.map (fun (d, _) => d)
  (List.filter (fun (_, b) => b)
  Direction.[
    (Left, x > 0),
    (Right, x < w - 1),
    (Up, y > 0),
    (Down, y < h - 1)
  ])
};

let _is_open: b => int => int => int => bool = [%bs.raw {|
  function (board, x, y, dir) {
    switch (dir) {
      case 0:
        if (x <= 0) return false
        return board.h[x-1][y]
      case 1:
        if (x > board.h.length - 1) return false
        return board.h[x][y]
      case 2:
        if (y <= 0) return false
        return board.v[x][y-1]
      case 3:
        if (y > board.v[0].length - 1) return false
        return board.v[x][y]
    }
  }
|}];

let dir_to_int direction => Direction.(switch direction {
  | Left => 0
  | Right => 1
  | Up => 2
  | Down => 3
});

let _add_wall: b => int => int => int => unit = [%bs.raw {|
  function (board, x, y, dir) {
    switch (dir) {
      case 0: // Left
        if (x <= 0 || x > board.v.length) return
        if (y < 0 || y > board.v[0].length - 1) return
        board.v[x-1][y] = true
        break
      case 1: // Right
        if (x < 0 || x > board.v.length - 1) return
        if (y < 0 || y > board.v[0].length - 1) return
        board.v[x][y] = true
        break
      case 2: // Up
        if (y <= 0 || y > board.h[0].length) return
        if (x < 0 || x > board.h.length - 1) return
        board.h[x][y-1] = true
        break
      case 3: // Down
        if (y < 0 || y >= board.h[0].length) return
        if (x < 0 || x > board.h.length - 1) return
        board.h[x][y] = true
        break
    }
  }
|}];

let is_open (_, _, board) (x, y) direction => {
  _is_open board x y (dir_to_int direction)
};

let add_wall (_, _, board) (x, y) direction => {
  _add_wall board x y (dir_to_int direction)
};

let open_adjacent t pos => {
  List.filter (is_open t pos) (adjacent t pos)
};

let _drawable_walls: b => float => float =>
  array ((float, float), (float, float)) =
[%bs.raw {|
  function (board, wsize, hsize) {
    var res = []
    var w = board.h.length
    var h = board.h[0].length + 1
    var vs = wsize / w
    var hs = hsize / h
    for (var x=0; x < w-1; x++) {
      for (var y=0; y < h; y++) {
        if (board.v[x][y]) {
          res.push([
            [hs + x * hs, y * vs],
            [hs + x * hs, (y + 1) * vs],
          ])
        }
      }
    }

    for (var x=0; x < w; x++) {
      for (var y=0; y < h-1; y++) {
        if (board.h[x][y]) {
          res.push([
            [x * hs, vs + y * vs],
            [(x + 1) * hs, vs + y * vs],
          ])
        }
      }
    }

    return res
  }
|}];

let drawable_walls (_, _, board) (w, h) => {
  List.map
  (fun (p1, p2) => Shared.Line (p1, p2))
  (Array.to_list (_drawable_walls board w h))
};

