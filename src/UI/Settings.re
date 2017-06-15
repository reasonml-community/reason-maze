
let se = ReasonReact.stringToElement;
let si = string_of_int;

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
  t.canvas_size
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

let from_json str => {
  open Js.Json;
  let parsed = try (Some (parseExn str)) {
  | _ => None
  };

  switch parsed {
  | Some arr => {
    switch (decodeArray arr) {
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
          board: decodeString board >>== Types.Board.by_name >? HexBox,
          algorithm: decodeString alg >>== Types.Alg.by_name >? Random,
          fill: T.parse_fill fill >? HueSat (0, 80),
          wall: parse_line wall,
          edge: parse_line edge,
          batch_size: decodeNumber batch_size >>= int_of_float >? 1,
          size_hint: decodeNumber size_hint >>= int_of_float >? 5,
          canvas_size: decodeNumber canvas_size >>= int_of_float >? 1000
        }
      }
    | _ => None
    }
  };
  | None => None
  };
};

let initial = T.{
  board: Types.Board.Hexagon,
  algorithm: Types.Alg.DFS,
  fill: HueSat (30, 90),
  size_hint: 10,
  batch_size: 1,
  canvas_size: 1000,
  wall: Some (1, 20),
  edge: None,
};

let to_options (settings: T.t) => {
  Show.Options.{
    canvas_size: (float_of_int settings.canvas_size, float_of_int settings.canvas_size),
    min_margin: 50.0,
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

type updater = {
  update: 'a .('a => T.t => T.t) => bool => ReasonReact.Callback.t 'a
};

module Title = {
  let component = ReasonReact.statelessComponent "Title";
  let make children => {
    ...component,
    render: fun () _ => <div style=(ReactDOMRe.Style.make
      fontWeight::"bold"
      alignSelf::"flex-start"
      padding::"15px 0px 5px"
      ()
    )>
      (ReasonReact.arrayToElement children)
    </div>
  }
};

module Settings = {
  let component = ReasonReact.statelessComponent "Settings";

  open T;
  open Types;
  let set_board board state => {...state, board};
  let set_alg algorithm state => {...state, algorithm};
  let set_size_hint size_hint state => {...state, size_hint};
  let set_fill fill state => {...state, fill: HueSat fill};

  let make ::state ::updater _children => {
    ...component,
    render: fun () _ => {
      <div className="settings">
        <Title>(se "Animation Speed")</Title>
        <Range
          width=150
          height=20
          vertical=false
          min=1
          max=20
          value=(state.batch_size)
          step=1.0
          onChange=(updater.update (fun batch_size state => {...state, batch_size}) true)
        />

        (se "Canvas Size: ") (se (si state.canvas_size))
        <Range
          width=150
          height=20
          vertical=false
          min=300
          max=1000
          value=(state.canvas_size)
          step=10.0
          onChange=(updater.update (fun canvas_size state => {...state, canvas_size}) true)
        />

        (se "Size: ") (se (si state.size_hint))
        <Range
          width=150
          height=20
          vertical=false
          min=3
          max=50
          value=(state.size_hint)
          step=1.0
          onChange=(updater.update set_size_hint true)
        />

        <Title>(se "Fill color")</Title>
        <div style=(ReactDOMRe.Style.make flexDirection::"row" ())>
          <SelectableButton
            title="No fill"
            selected=(state.fill === NoFill)
            onClick=(updater.update (fun _ state => {...state, fill: NoFill}) true)
          />
          <SelectableButton
            title="Rainbow"
            selected=(state.fill === Rainbow)
            onClick=(updater.update (fun _ state => {...state, fill: Rainbow}) true)
          />
        </div>
        <ColorSlider
          width=150
          height=100
          value=(switch (state.fill) { |HueSat fill => Some fill | _ => None})
          onChange=(updater.update set_fill true)
        />
        <Title>(se "Wall")</Title>
        <LineSetting
          value=(state.wall)
          onChange=(updater.update (fun wall state => {...state, wall}) true)
        />
        <Title>(se "Path")</Title>
        <LineSetting
          value=(state.edge)
          onChange=(updater.update (fun edge state => {...state, edge}) true)
        />

        <Title>(se "Shape")</Title>
        <Options
          get_title=(Board.name)
          options=(Board.all)
          current=(state.board)
          on_change=(updater.update set_board false)
        />

        <Title>(se "Algorithm")</Title>
        <Options
          get_title=(Alg.name)
          options=(Alg.all)
          current=(state.algorithm)
          on_change=(updater.update set_alg false)
        />
      </div>
    },
  };
};
