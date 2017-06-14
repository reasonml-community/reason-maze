
external refToCanvas: Dom.element => Canvas.canvasElement = "%identity";

let refToContext canv => {
  switch (Js.Null.to_opt canv) {
  | Some canv => Some (Canvas.getContext (refToCanvas canv))
  | None => None
  }
};

let si = string_of_int;
let fi = float_of_int;
let iof = int_of_float;
let px m => (si m) ^ "px";

let scale n max range => iof ((fi n) /. (fi max) *. (fi range));

let render width height ctx => {
  for x in 0 to width {
    for y in 0 to height {
      let color = Presenter.hsl (scale x width 360) (scale y height 100) 50;
      Canvas.Ctx.setFillStyle ctx color;
      Canvas.Ctx.fillRect ctx (fi x) (fi y) 1.0 1.0;
    }
  }
};

type state = {
  ctx: option Canvas.ctx,
};
let component = ReasonReact.statefulComponent "ColorSlider";

let isPressed _ => false;
let toValue _ => (50, 70);

let make ::width ::height ::value ::onChange _ => {
  ...component,
  initialState: fun () => {ctx: None},
  didMount: fun state _ => {
    switch (state.ctx) {
    | Some ctx => render width height ctx
    | None => ()
    };
    ReasonReact.NoUpdate
  },
  render: fun state self => {
    <div style=(ReactDOMRe.Style.make position::"relative" ())>
      <canvas
        width=(si width)
        height=(si height)
        onMouseDown=(fun evt => onChange (toValue evt))
        onMouseMove=(fun evt => isPressed evt ? onChange (toValue evt) : ())
        ref=(self.update (fun ref state _ => ReasonReact.SilentUpdate {
          ...state,
          ctx: refToContext ref,
        }))
      />
      (switch value {
      | None => ReasonReact.nullElement
      | Some (hue, saturation) => {
        <div
          pointerEvents="none"
          style=(ReactDOMRe.Style.make
          position::"absolute"
          width::"10px"
          height::"10px"
          border::"2px solid black"
          borderRadius::"5px"
          marginLeft::"-5px"
          marginTop::"-5px"
          top::(px (scale saturation 100 height))
          left::(px (scale hue 360 width))
          ())
        />
      }
      })
    </div>
  }
};

