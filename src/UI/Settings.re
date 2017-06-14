
let se = ReasonReact.stringToElement;

module Buttons = {
  let component = ReasonReact.statelessComponent "Buttons";

  let styles = Aphrodite.create {
    "container": {
      "display": "flex",
      "align-items": "stretch",
      "border": "1px solid #aaa",
      "margin": 5,
      "align-self": "stretch",
    },
    "button": {
      "background-color": "white",
      "border": "none",
      "padding": "10px 20px",
      "flex": 1,
      "cursor": "pointer",
      "outline": "none",
      ":hover": {
        "background-color": "#eee"
      }
    },
    "selected": {
      "background-color": "#aaa"
    },
  };

  let className is_current => Aphrodite.(csss styles [|
    "button",
    is_current ? "selected" : "nonselected"
  |]);

  let make ::options ::get_title ::current ::on_change _children => {
    {
      ...component,
      render: fun () _self =>
        <div className=Aphrodite.(css styles "container")>
          (ReasonReact.arrayToElement (Array.map
            (fun option => <button
              key=(get_title option)
              onClick=(fun _ => on_change option)
              className=(className (current === option))
            >
              (se (get_title option))
            </button>)
            options
          ))
        </div>
    }
  };
};

module T = {
  type t = {
    board: Types.Board.t,
    algorithm: Types.Alg.t,
    fill: option (int, int),
    wall: option (int, int),
    edge: option (int, int),
    size_hint: int,
  }
};

let initial = T.{
  board: Types.Board.Hexagon,
  algorithm: Types.Alg.Random,
  fill: Some (0, 90),
  size_hint: 10,
  wall: Some (5, 30),
  edge: None,
};

let to_options canvas_size (settings: T.t) => {
  Show.Options.{
    canvas_size,
    min_margin: 50.0,
    size_hint: settings.size_hint,
    draw_edges: switch (settings.edge) {
    | Some (width, lightness) => Some (float_of_int width, Presenter.hsl 0 0 lightness)
    | None => None
    },
    draw_shapes: switch (settings.fill) {
    | Some (hue, saturation) => Some (Presenter.hsl hue saturation)
    | None => None
    },
    draw_walls: switch (settings.wall) {
    | Some (width, lightness) => Some (float_of_int width, Presenter.hsl 0 0 lightness)
    | None => None
    },
  };
};


type updater = {
  update: 'a .('a => T.t => T.t) => ReasonReact.Callback.t 'a
};

module Settings = {
  let component = ReasonReact.statelessComponent "Settings";

  open T;
  open Types;
  let set_board board state => {...state, board};
  let set_alg algorithm state => {...state, algorithm};

  let make ::state ::updater _children => {
    ...component,
    render: fun () _ => {
      <div className="settings">
        <Buttons
          get_title=(Board.name)
          options=(Board.all)
          current=(state.board)
          on_change=(updater.update set_board)
        />

        <Buttons
          get_title=(Alg.name)
          options=(Alg.all)
          current=(state.algorithm)
          on_change=(updater.update set_alg)
        />
      </div>
    },
  };
};
