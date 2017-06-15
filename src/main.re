
let free_hand () => {
  /*Random.init seed;*/

  let options = Show.Options.{
    canvas_size: (1000.0, 1000.0),
    min_margin: 50.0,
    size_hint: 40,
    draw_edges: None,
    draw_shapes: Some (fun current _ => Presenter.hslf 0.0 100.0 (current *. 100.0)),
    draw_walls: Some (1.0, "#ccc"),
  };

  let module Board = HexBox;
  let module Gen = Random2;

  let module Paint' = Paint.F Board Gen;
  let module Show' = Show.F Board Gen;

  Paint'.paint options;
};

let generate_random () => {
  let canvas = Canvas.createOnBody 1000 1000;
  let ctx = Canvas.getContext canvas;

  RandomMaze.run ctx (1000.0, 1000.0);
};

/*free_hand();*/
/*generate_random();*/
Builder.run();