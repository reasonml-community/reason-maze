
module T = {
  type fill =
    | NoFill
    | Rainbow
    | HueSat (int, int);
  type t = {
    board: Types.Board.t,
    algorithm: Types.Alg.t,
    fill: fill,
    wall: option (int, int),
    edge: option (int, int),
    batch_size: int,
    size_hint: int,
    canvas_size: int,
    seed: int,
  };

  let fill_json fill => switch fill {
  | NoFill => Js.Json.string "none"
  | Rainbow => Js.Json.string "rainbow"
  | HueSat (hue, sat) => Js.Json.numberArray [|float_of_int hue, float_of_int sat|]
  };
  let parse_fill fill => Js.Json.(switch (classify fill) {
  | JSONString "none" => Some NoFill
  | JSONString "rainbow" => Some Rainbow
  | JSONArray [|hue, sat|] => switch (classify hue, classify sat) {
    | (JSONNumber hue, JSONNumber sat) => Some (HueSat (int_of_float hue, int_of_float sat))
    | _ => None
  }
  | _ => None
  })
};

let to_jsonable t => {
  T.(
  Types.Board.name t.board,
  Types.Alg.name t.algorithm,
  T.fill_json t.fill,
  Js.Null.from_opt t.wall,
  Js.Null.from_opt t.edge,
  t.batch_size,
  t.size_hint,
  t.canvas_size,
  t.seed
  )
};

let to_json t => Js.Json.stringifyAny (to_jsonable t);

let (>>==) a b => switch a { |Some a => (b a) | None => None};
let (>>=) a b => switch a { |Some a => Some (b a) | None => None};
let (>?) a b => switch a { |Some a => a | None => b};

let parse_line value => Js.Json.(switch (classify value) {
| JSONArray [|width, light|] => switch (classify width, classify light) {
  | (JSONNumber width, JSONNumber light) => Some (int_of_float width, int_of_float light)
  | _ => None
  }
| _ => None
});

let maybe_get ar count n => n < count ? Some (Array.get ar n) : None;

let initial = T.{
  board: Types.Board.Hexagon,
  algorithm: Types.Alg.DFS,
  fill: HueSat (30, 90),
  size_hint: 10,
  batch_size: 1,
  canvas_size: 1000,
  wall: Some (1, 20),
  edge: None,
  seed: 0,
};

let from_json str => {
  open Js.Json;
  let parsed = try (Some (parseExn str)) {
  | _ => None
  };

  switch parsed {
  | Some arr => {
    switch (decodeArray arr) {
    | Some items => {
      let count = Array.length items;
      let item = maybe_get items count;
      let board = item 0 >>== decodeString >>== Types.Board.by_name >? initial.board;
      let algorithm = item 1 >>== decodeString >>== Types.Alg.by_name >? initial.algorithm;
      let fill = item 2 >>== T.parse_fill >? initial.fill;
      let wall = item 3 >>== parse_line;
      let edge = item 4 >>== parse_line;
      let batch_size = item 5 >>== decodeNumber >>= int_of_float >? initial.batch_size;
      let size_hint = item 6 >>== decodeNumber >>= int_of_float >? initial.size_hint;
      let canvas_size = item 7 >>== decodeNumber >>= int_of_float >? initial.canvas_size;
      let seed = item 8 >>== decodeNumber >>= int_of_float >? initial.seed;

      Some T.{
        board,
        algorithm,
        fill,
        wall,
        edge,
        batch_size,
        size_hint,
        canvas_size,
        seed,
      }
    }

    /*
    | Some [|
      board,
      alg,
      fill,
      wall,
      edge,
      batch_size,
      size_hint,
      canvas_size
    |] => {
        Some T.{
          board,
          algorithm,
          fill: 
          wall: parse_line wall,
          edge: parse_line edge,
          batch_size: 
          size_hint: 
          canvas_size: 
        }
      }
      */
    | _ => None
    }
  };
  | None => None
  };
};

let to_options (settings: T.t) => {
  Show.Options.{
    canvas_size: (float_of_int settings.canvas_size, float_of_int settings.canvas_size),
    min_margin: 10.0,
    size_hint: settings.size_hint,
    draw_edges: switch (settings.edge) {
    | Some (width, lightness) => Some (float_of_int width, Presenter.hsl 0 0 lightness)
    | None => None
    },
    draw_shapes: switch (settings.fill) {
    | HueSat (hue, saturation) => Some (fun current max => Presenter.hslf (float_of_int hue) (float_of_int saturation) (100.0 -. current *. 50.0))
    | Rainbow => Some (fun current max => Presenter.hslf (max *. 360.0) 70.0 50.0)
    | NoFill => None
    },
    draw_walls: switch (settings.wall) {
    | Some (width, lightness) => Some (float_of_int width, Presenter.hsl 0 0 lightness)
    | None => None
    },
  };
};
