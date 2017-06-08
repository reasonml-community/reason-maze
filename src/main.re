
let main () => {
  /*Random.init seed;*/

  let options = Show.Options.{
    canvas_size: (1000.0, 1000.0),
    min_margin: 50.0,
    size_hint: 20,
    draw_edges: None,
    /*draw_edges: Some (1.0, "#aaa"),*/
    /*draw_walls: None,*/
    draw_shapes: None,
    /*draw_shapes: Some (Presenter.hsl 0 100),*/
    draw_walls: Some (1.0, "#ccc"),
  };

  let module Board = Circle;
  let module Gen = Random2;

  let module Paint' = Paint.F Board Gen;
  let module Show' = Show.F Board Gen;

  let (canvas, ctx, state) = Show'.init options;

  Show'.loop options ctx state;
};

/*main();*/
RandomMaze.run();