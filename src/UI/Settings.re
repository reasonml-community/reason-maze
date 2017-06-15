
let se = ReasonReact.stringToElement;
let si = string_of_int;

module Range = {
  let component = ReasonReact.statelessComponent "Range";
  let styles = Aphrodite.create{
    "container": {
    }
  };

  let px m => (si m) ^ "px";
  let mkstyle width height vertical => {
    let style = ReactDOMRe.Style.make width::(px width) height::(px height);
    vertical
      ? style
        transformOrigin::((px (width / 2)) ^ " " ^ (px (width / 2)))
        transform::"rotate(-90deg)" ()
      : style ();
  };

  let getValue evt => (int_of_string (ReactDOMRe.domElementToObj(ReactEventRe.Form.target evt))##value);

  let make ::min ::max ::value ::step ::width ::height ::vertical ::onChange _ => {
    ...component,
    render: fun () _ => {
      <input
        _type="range"
        style=(mkstyle width height vertical)
        min=min
        max=(si max)
        value=(si value)
        step=step
        onChange=(fun evt => onChange (getValue evt))
      />
    }
  }
};

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
    batch_size: int,
    size_hint: int,
  }
};

let initial = T.{
  board: Types.Board.Hexagon,
  algorithm: Types.Alg.Random,
  fill: Some (0, 90),
  size_hint: 10,
  batch_size: 1,
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
  update: 'a .('a => T.t => T.t) => bool => ReasonReact.Callback.t 'a
};

module LineSetting = {
  let component = ReasonReact.statelessComponent "LineSetting";
  let make ::value ::onChange _ => {
    ...component,
    render: fun _ _ => {
      let (width, color) = switch value {
        | Some x => x
        | None => (0, 20)
      };

      <div>
          (se "Width: ") (se (si width))
          <Range
            width=150
            height=20
            vertical=false
            min=0
            max=30
            value=(width)
            step=1.0
            onChange=(fun x => onChange (x === 0 ? None : Some (x, color)))
          />
          (se "Brightness: ") (se (si color))
          <Range
            width=150
            height=20
            vertical=false
            min=0
            max=100
            value=(color)
            step=1.0
            onChange=(fun x => onChange (Some (width, x)))
          />
      </div>
    }
  }
};

module Settings = {
  let component = ReasonReact.statelessComponent "Settings";

  open T;
  open Types;
  let set_board board state => {...state, board};
  let set_alg algorithm state => {...state, algorithm};
  let set_size_hint size_hint state => {...state, size_hint};
  let set_fill fill state => {...state, fill: Some fill};

  let make ::state ::updater _children => {
    ...component,
    render: fun () _ => {
      <div className="settings">
        (se "Shape")
        <Buttons
          get_title=(Board.name)
          options=(Board.all)
          current=(state.board)
          on_change=(updater.update set_board false)
        />

        (se "Algorithm")
        <Buttons
          get_title=(Alg.name)
          options=(Alg.all)
          current=(state.algorithm)
          on_change=(updater.update set_alg false)
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

        (se "Fill color: ")
        <ColorSlider
          width=150
          height=100
          value=state.fill
          onChange=(updater.update set_fill true)
        />
        (se "Wall")
        <LineSetting
          value=(state.wall)
          onChange=(updater.update (fun wall state => {...state, wall}) true)
        />
        (se "Path")
        <LineSetting
          value=(state.edge)
          onChange=(updater.update (fun edge state => {...state, edge}) true)
        />
        (se "Animation Speed")
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
      </div>
    },
  };
};
