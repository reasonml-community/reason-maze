
let seed = [%bs.raw "parseInt(Math.random() * Number.MAX_SAFE_INTEGER)"];
/*let seed = [%bs.raw "6572995174978857"];*/
/*let seed = [%bs.raw "5246800480144799"];*/
Random.init seed;
Js.log ("Seed", seed);

let random_line () => (
  1.0 +. (float_of_int (Random.int 10)),
  Presenter.hsl 0 0 (Random.int 80)
);

let options = Show.Options.{
  canvas_size: (1000.0, 1000.0),
  min_margin: 50.0,
  size_hint: 3 + Random.int 15,
  /*line_width: 1.0 +. (float_of_int (Random.int 10)),*/
  draw_edges: Random.bool () ? Some (random_line ()) : None,
  draw_shapes: Random.bool () ? Some {
    let hue = (Random.int 360);
    let saturation = (70 + Random.int 30);
    Presenter.hsl hue saturation
  } : None,
  draw_walls: Random.bool () ? Some (random_line ()) : None,
};
let options = (options.draw_edges == None && options.draw_shapes == None && options.draw_walls == None)
  ? {...options, draw_walls: Some (random_line ())}
  : options;

let choose arr => {
  Array.get arr (Random.int (Array.length arr))
};

let random_board () => choose [|
  (module HexBox: SimpleBoard.T),
  (module HexHex),
  (module NewHexTriangle),
  (module NewRect),
  /* TODO circle */
|];

let module Board = (val random_board());

let module Gen = NewDepth.F (NewDepth.RandomConfig ());
/*let module Board = HexBox;*/

let module Paint' = Paint.F Board Gen;
let module Show' = Show.F Board Gen;

let (canvas, ctx, state) = Show'.init options;

Show'.loop options ctx state;
