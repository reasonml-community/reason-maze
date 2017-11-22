let si = string_of_int;

let se = ReasonReact.stringToElement;

module Title = {
  let component = ReasonReact.statelessComponent("Title");
  let make = (children) => {
    ...component,
    render: (_) =>
      <div
        style=(
          ReactDOMRe.Style.make(
            ~fontWeight="bold",
            ~alignSelf="flex-start",
            ~padding="15px 0px 5px",
            ()
          )
        )>
        (ReasonReact.arrayToElement(children))
      </div>
  };
};

let component = ReasonReact.statelessComponent("Settings");

open Settings.T;

open Types;

let compose = (fn1, fn2, arg) => fn1(fn2(arg));

let set_board = (settings, board) => {...settings, board};

let set_alg = (settings, algorithm) => {...settings, algorithm};

let set_size_hint = (settings, size_hint) => {...settings, size_hint};

let set_fill = (settings, fill) => {...settings, fill: HueSat(fill)};

let newSeed: unit => int = [%bs.raw
  {|
  function () {
    return Math.floor(Math.random() * (1 << 30))
  }
|}
];

let make = (~settings, ~update, _children) => {
  ...component,
  render: (_self) =>
    <div className="settings">
      <Title> (se("Animation Speed")) </Title>
      <Range
        width=150
        height=20
        vertical=false
        min=1
        max=20
        value=settings.batch_size
        step=1.0
        onChange=((batch_size) => update({...settings, batch_size}))
      />
      (se("Canvas Size: "))
      (se(si(settings.canvas_size)))
      <Range
        width=150
        height=20
        vertical=false
        min=300
        max=1000
        value=settings.canvas_size
        step=10.0
        onChange=((canvas_size) => update({...settings, canvas_size}))
      />
      (se("Size: "))
      (se(si(settings.size_hint)))
      <Range
        width=150
        height=20
        vertical=false
        min=3
        max=50
        value=settings.size_hint
        step=1.0
        onChange=(compose(update, set_size_hint(settings)))
      />
      <Title> (se("Seed")) </Title>
      <input value=(si(settings.seed)) />
      <button onClick=((_) => update({...settings, seed: newSeed()})) style=Styles.button>
        (se("New Seed"))
      </button>
      <Title> (se("Fill color")) </Title>
      <div style=(ReactDOMRe.Style.make(~flexDirection="row", ()))>
        <SelectableButton
          title="No fill"
          selected=(settings.fill === NoFill)
          onClick=((_) => update({...settings, fill: NoFill}))
        />
        <SelectableButton
          title="Rainbow"
          selected=(settings.fill === Rainbow)
          onClick=((_) => update({...settings, fill: Rainbow}))
        />
      </div>
      <ColorSlider
        width=150
        height=100
        value=(
          switch settings.fill {
          | HueSat(fill) => Some(fill)
          | _ => None
          }
        )
        onChange=(compose(update, set_fill(settings)))
      />
      <Title> (se("Wall")) </Title>
      <LineSetting value=settings.wall onChange=((wall) => update({...settings, wall})) />
      <Title> (se("Path")) </Title>
      <LineSetting value=settings.edge onChange=((edge) => update({...settings, edge})) />
      <Title> (se("Shape")) </Title>
      <Options
        get_title=Board.name
        options=Board.all
        current=settings.board
        on_change=(compose(update, set_board(settings)))
      />
      <Title> (se("Algorithm")) </Title>
      <Options
        get_title=Alg.name
        options=Alg.all
        current=settings.algorithm
        on_change=(compose(update, set_alg(settings)))
      />
    </div>
};
