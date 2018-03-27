let se = ReasonReact.stringToElement;

let si = string_of_int;

let component = ReasonReact.statelessComponent("LineSetting");

let make = (~value, ~onChange, _) => {
  ...component,
  render: _ => {
    let (width, color) =
      switch (value) {
      | Some(x) => x
      | None => (0, 20)
      };
    <div>
      (se("Width: "))
      (se(si(width)))
      <Range
        width=150
        height=20
        vertical=false
        min=0
        max=30
        value=width
        step=1.0
        onChange=(x => onChange(x === 0 ? None : Some((x, color))))
      />
      (se("Lightness: "))
      (se(si(color)))
      <Range
        width=150
        height=20
        vertical=false
        min=0
        max=100
        value=color
        step=1.0
        onChange=(x => onChange(Some((width, x))))
      />
    </div>;
  },
};
