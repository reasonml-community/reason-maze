open Belt;

let iof = int_of_float;

module F = (Board: SimpleBoard.T, Gen: Generator.T) => {
  module Man = PaintingManager.F(Board, Gen);
  module Pres = Presenter.F(Board, Gen);
  module Show' = Show.F(Board, Gen);
  let show_paint = (ctx, (width, height), state) => {
    Canvas.Ctx.setStrokeWidth(ctx, 1.0);
    Canvas.Ctx.setLineCap(ctx, "round");
    Canvas.Ctx.clearRect(ctx, 0.0, 0.0, width, height);
    /* TODO might be nice to do something sophisticated with corners... */
    let (w, h) = state.PaintingManager.State.outsize;
    let xm = (width -. w) /. 2.0;
    let ym = (height -. h) /. 2.0;
    /*let (xm, ym) = (0.0, 0.0);*/
    /*Array.iter (Pres.draw_shape ctx (xm, ym) (Presenter.hsl 0 100) 10) (Man.paint_shapes state);*/
    Canvas.Ctx.setStrokeStyle(ctx, "#aaa");
    List.forEach(Man.paint_walls(state), Pres.draw_wall(ctx, (xm, ym)));
  };
  let listen_to_canvas:
    (Canvas.canvasElement, ((float, float)) => unit) => unit = [%bs.raw
    {|function(canvas, fn) {
    canvas.addEventListener('mousemove', evt => {
      if (evt.button === 0 && evt.buttons === 1) {
        fn([evt.clientX, evt.clientY])
      }
    })
  }|}
  ];
  let make_button: (string, unit => unit) => unit = [%bs.raw
    {|function(text, fn) {
    var button = document.createElement('button')
    button.textContent = text;
    document.body.appendChild(button)
    button.addEventListener('click', fn)
  }|}
  ];
  let paint = options => {
    open Show.Options;
    Random.self_init();
    let (width, height) = options.canvas_size;
    let min_margin = options.min_margin;
    let canvas = Canvas.createOnBody(iof(width), iof(height));
    let ctx = Canvas.getContext(canvas);
    let with_margins = (width -. min_margin, height -. min_margin);
    let paint_state = Man.paint_init(with_margins, options.size_hint);
    show_paint(ctx, options.canvas_size, paint_state);
    let (w, h) = paint_state.PaintingManager.State.outsize;
    let xm = (width -. w) /. 2.0;
    let ym = (height -. h) /. 2.0;
    let pstate = ref(paint_state);
    listen_to_canvas(
      canvas,
      ((x, y)) => {
        pstate := Man.toggle_point(pstate^, (x -. xm, y -. ym));
        show_paint(ctx, options.canvas_size, pstate^);
      },
    );
    make_button("Go", () =>
      switch (Man.realize_state(pstate^)) {
      | Some(state) => Show'.animate(ctx, 5, 40, options, state) |> ignore
      | None => ()
      /* TODO need to make it work with unconnected sections */
      }
    );
  };
};
