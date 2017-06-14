
let iof = int_of_float;

let module Options = {
  type t = {
    canvas_size: (float, float),
    min_margin: float,
    size_hint: int,
    /*line_width: float,*/
    draw_edges: option (float, string),
    draw_walls: option (float, string),
    draw_shapes: option (int => string),
  };
};
open Options;

let module F (Board: SimpleBoard.T) (Gen: Generator.T) => {
  let module Man = Manager.F Board Gen;
  let module Presenter = Presenter.F Board Gen;

  /* have this take some config */
  let show ctx options state => {
    let (width, height) = options.canvas_size;
    /*Js.log state;*/
    /*Canvas.Ctx.setStrokeWidth ctx options.line_width;*/
    Canvas.Ctx.setLineCap ctx "round";
    Canvas.Ctx.setFillStyle ctx "white";
    Canvas.Ctx.fillRect ctx 0.0 0.0 width height;
    /* TODO might be nice to do something sophisticated with corners... */

    let (w, h) = state.Manager.State.outsize;
    let xm = (width -. w) /. 2.0;
    let ym = (height -. h) /. 2.0;
    /*Js.log (w, h, width, height, xm, ym);*/
    /*let (xm, ym) = (0.0, 0.0);*/

    switch (options.draw_shapes) {
      | Some get_color => {
        /*Canvas.Ctx.setFillStyle ctx color;*/
        Array.iter (Presenter.draw_shape ctx (xm, ym) get_color (Man.max_age state)) (Man.all_shapes state);
      }
      | None => ()
    };
    switch (options.draw_edges) {
      | Some (width, color) => {
        Canvas.Ctx.setLineWidth ctx width;
        Canvas.Ctx.setStrokeStyle ctx color;
        let edges = (Man.all_edges state);
        List.iter (Presenter.draw_edge ctx (xm, ym)) edges;
      }
      | None => ()
    };
    switch (options.draw_walls) {
      | Some (width, color) => {
        Canvas.Ctx.setLineWidth ctx width;
        Canvas.Ctx.setStrokeStyle ctx color;
        let walls = (Man.all_walls state);
        List.iter (Presenter.draw_wall ctx (xm, ym)) walls;
      }
      | None => ()
    };
  };

  /* have this take some config */
  let show_debug ctx options state => {
    let (width, height) = options.canvas_size;
    Js.log state;
    /*Canvas.Ctx.setStrokeWidth ctx 1.0;*/
    Canvas.Ctx.setLineCap ctx "round";
    /*Canvas.Ctx.setFillStyle ctx "white";*/
    Canvas.Ctx.clearRect ctx 0.0 0.0 width height;
    /* TODO might be nice to do something sophisticated with corners... */

    let (w, h) = state.Manager.State.outsize;
    let xm = (width -. w) /. 2.0;
    let ym = (height -. h) /. 2.0;
    Js.log (w, h, width, height, xm, ym);
    /*let (xm, ym) = (0.0, 0.0);*/

    let edges = Man.edges state;
    Generator.PairSet.iter
    (fun (a, b) => Js.log(a, b))
    edges;

    let walls = (Man.all_walls state);
    Js.log ("walls", Array.of_list walls);
    switch (options.draw_shapes) {
      | Some get_color => {
        /*Canvas.Ctx.setFillStyle ctx color;*/
        /*Array.iter (Presenter.draw_shape ctx (xm, ym) get_color (Man.max_age state)) (Man.all_shapes state);*/
        Array.iteri (Presenter.draw_shapei ctx (xm, ym) get_color (Man.max_age state)) (Man.all_shapes state);
      }
      | None => ()
    };
    switch (options.draw_edges) {
      | Some (width, color) => {
        Canvas.Ctx.setLineWidth ctx width;
        Canvas.Ctx.setStrokeStyle ctx color;
        List.iter (Presenter.draw_edge ctx (xm, ym)) (Man.all_edges state);
        /*List.iteri (Presenter.draw_edgei ctx (xm, ym)) (Man.all_edges state);*/
      }
      | None => ()
    };
    switch (options.draw_walls) {
      | Some (width, color) => {
        Canvas.Ctx.setLineWidth ctx width;
        Canvas.Ctx.setStrokeStyle ctx color;
        let walls = (Man.all_walls state);
        Js.log walls;
        Js.log "hi";
        /*List.iter (Presenter.draw_wall ctx (xm, ym)) walls;*/
        List.iteri (Presenter.draw_walli ctx (xm, ym)) walls;
      }
      | None => ()
    };
  };

  let rec batch state n => if (n === 0) { state } else { batch (Man.step state) (n - 1) };

  let animate ctx batch_size options state => {
    Js.log "animate";
    let rec inner state => {
      let state = batch state batch_size;
      show ctx options state;
      Man.finished state
        ? (Js.log "done")
        : Window.setTimeout (fun () => inner state) 40 |> ignore
    };
    inner state;
  };

  let init_state {canvas_size, min_margin, size_hint} => {
    let (width, height) = canvas_size;
    let with_margins = (width -. (min_margin *. 2.0), height -. (min_margin *. 2.0));
    Man.init with_margins size_hint;
  };

  let init options => {
    let (width, height) = options.canvas_size;
    let canvas = Canvas.createOnBody (iof width) (iof height);
    let ctx = Canvas.getContext canvas;
    (canvas, ctx, init_state options)
  };

  let loop options ctx state => {
    show ctx options (Man.loop_to_end state);
  };

  let loop_debug options ctx state => {
    show_debug ctx options (Man.loop_to_end state);
  };

  /*let main {canvas_size, min_margin, size_hint} => {

    if (false) {
      show ctx canvas_size state;
    } else if (false) {
      show ctx canvas_size (Man.loop_to_end state);
    } else {
      animate ctx 20 canvas_size state;
    }
  };*/

};