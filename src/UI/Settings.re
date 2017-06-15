
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
  }
};

let initial = T.{
  board: Types.Board.Hexagon,
  algorithm: Types.Alg.Random,
  fill: HueSat (0, 90),
  size_hint: 10,
  batch_size: 1,
  canvas_size: 1000,
  wall: Some (5, 30),
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

        (se "Canvas Size: ") (se (si state.size_hint))
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
      </div>
    },
  };
};
