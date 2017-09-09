let si = string_of_int;

let se = ReasonReact.stringToElement;

type updater = {update: 'a .('a => Settings.T.t => Settings.T.t) => ReasonReact.Callback.t 'a};

module Title = {
  let component = ReasonReact.statelessComponent "Title";
  let make children => {
    ...component,
    render: fun _ =>
      <div
        style=(
          ReactDOMRe.Style.make
            fontWeight::"bold" alignSelf::"flex-start" padding::"15px 0px 5px" ()
        )>
        (ReasonReact.arrayToElement children)
      </div>
  };
};

let component = ReasonReact.statelessComponent "Settings";

open Settings.T;

open Types;

let set_board board state => {...state, board};

let set_alg algorithm state => {...state, algorithm};

let set_size_hint size_hint state => {...state, size_hint};

let set_fill fill state => {...state, fill: HueSat fill};

let newSeed: unit => int = [%bs.raw
  {|
  function () {
    return Math.floor(Math.random() * (1 << 30))
  }
|}
];

let make ::state ::updater _children => {
  ...component,
  render: fun _self =>
    <div className="settings">
      <Title> (se "Animation Speed") </Title>
      <Range
        width=150
        height=20
        vertical=false
        min=1
        max=20
        value=state.batch_size
        step=1.0
        onChange=(updater.update (fun batch_size state => {...state, batch_size}))
      />
      (se "Canvas Size: ")
      (se (si state.canvas_size))
      <Range
        width=150
        height=20
        vertical=false
        min=300
        max=1000
        value=state.canvas_size
        step=10.0
        onChange=(updater.update (fun canvas_size state => {...state, canvas_size}))
      />
      (se "Size: ")
      (se (si state.size_hint))
      <Range
        width=150
        height=20
        vertical=false
        min=3
        max=50
        value=state.size_hint
        step=1.0
        onChange=(updater.update set_size_hint)
      />
      <Title> (se "Seed") </Title>
      <input value=(si state.seed) />
      <button
        onClick=(updater.update (fun _ state => {...state, seed: newSeed ()})) style=Styles.button>
        (se "New Seed")
      </button>
      <Title> (se "Fill color") </Title>
      <div style=(ReactDOMRe.Style.make flexDirection::"row" ())>
        <SelectableButton
          title="No fill"
          selected=(state.fill === NoFill)
          onClick=(updater.update (fun _ state => {...state, fill: NoFill}))
        />
        <SelectableButton
          title="Rainbow"
          selected=(state.fill === Rainbow)
          onClick=(updater.update (fun _ state => {...state, fill: Rainbow}))
        />
      </div>
      <ColorSlider
        width=150
        height=100
        value=(
          switch state.fill {
          | HueSat fill => Some fill
          | _ => None
          }
        )
        onChange=(updater.update set_fill)
      />
      <Title> (se "Wall") </Title>
      <LineSetting
        value=state.wall
        onChange=(updater.update (fun wall state => {...state, wall}))
      />
      <Title> (se "Path") </Title>
      <LineSetting
        value=state.edge
        onChange=(updater.update (fun edge state => {...state, edge}))
      />
      <Title> (se "Shape") </Title>
      <Options
        get_title=Board.name
        options=Board.all
        current=state.board
        on_change=(updater.update set_board)
      />
      <Title> (se "Algorithm") </Title>
      <Options
        get_title=Alg.name
        options=Alg.all
        current=state.algorithm
        on_change=(updater.update set_alg)
      />
    </div>
};
