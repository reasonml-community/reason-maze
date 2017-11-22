external refToCanvas : Dom.element => Canvas.canvasElement = "%identity";

let refToContext = (canv) => Canvas.getContext(refToCanvas(canv));

let si = string_of_int;

let fi = float_of_int;

let iof = int_of_float;

let px = (m) => si(m) ++ "px";

let scale = (n, max, range) => iof(fi(n) /. fi(max) *. fi(range));

let render = (width, height, canvas) => {
  let ctx = refToContext(canvas);
  for (x in 0 to width) {
    for (y in 0 to height) {
      let color = Presenter.hsl(scale(x, width, 360), scale(y, height, 100), 50);
      Canvas.Ctx.setFillStyle(ctx, color);
      Canvas.Ctx.fillRect(ctx, fi(x), fi(y), 1.0, 1.0)
    }
  }
};

type state = {canvas: ref(option(Dom.element))};

let component = ReasonReact.reducerComponent("ColorSlider");

let isPressed = (evt) => ReactEventRe.Mouse.buttons(evt) == 1;

let getValue = (evt) =>
  int_of_string(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(evt))##value);

let elementPos = (element) => {
  let element = ReactDOMRe.domElementToObj(element);
  let box = element##getBoundingClientRect();
  let top: int = box##top;
  let left: int = box##left;
  (top, left)
};

let toValue = (width, height, evt, canvas) => {
  ReactEventRe.Mouse.preventDefault(evt);
  let (top, left) = elementPos(canvas);
  let x = ReactEventRe.Mouse.clientX(evt) - left;
  let y = ReactEventRe.Mouse.clientY(evt) - top;
  (scale(x, width, 360), scale(y, height, 100))
};

let (>>=) = (a, b) =>
  switch a {
  | Some(a) => Some(b(a))
  | None => None
  };

let setCanvasRef = (r, {ReasonReact.state}) => state.canvas := Js.Nullable.to_opt(r);

let make = (~width, ~height, ~value, ~onChange, _children) => {
  ...component,
  reducer: ((), _state) => ReasonReact.NoUpdate,
  initialState: () => {canvas: ref(None)},
  didMount: ({state}) => {
    switch state.canvas^ {
    | Some(canvas) => render(width, height, canvas)
    | None => ()
    };
    ReasonReact.NoUpdate
  },
  render: ({state} as self) =>
    <div style=(ReactDOMRe.Style.make(~position="relative", ()))>
      <canvas
        width=(si(width))
        height=(si(height))
        onMouseDown=((evt) => state.canvas^ >>= toValue(width, height, evt) >>= onChange |> ignore)
        onMouseMove=(
          (evt) =>
            isPressed(evt) ?
              state.canvas^ >>= toValue(width, height, evt) >>= onChange |> ignore : ()
        )
        ref=(self.handle(setCanvasRef))
      />
      (
        switch value {
        | None => ReasonReact.nullElement
        | Some((hue, saturation)) =>
          let style =
            ReactDOMRe.Style.make(
              ~position="absolute",
              ~width="10px",
              ~height="10px",
              ~border="2px solid black",
              ~borderRadius="5px",
              ~marginLeft="-5px",
              ~marginTop="-5px",
              ~top=px(scale(saturation, 100, height)),
              ~left=px(scale(hue, 360, width)),
              ~backgroundColor=Presenter.hsl(hue, saturation, 50),
              ()
            );
          let style = ReactDOMRe.Style.unsafeAddProp(style, "pointerEvents", "none");
          <div style />
        }
      )
    </div>
};
