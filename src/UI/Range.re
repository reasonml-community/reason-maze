
let si = string_of_int;

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
