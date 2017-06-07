
let seed = [%bs.raw "parseInt(Math.random() * Number.MAX_SAFE_INTEGER)"];
/*let seed = [%bs.raw "6572995174978857"];*/
let seed = [%bs.raw "5246800480144799"];
Random.init seed;
Js.log ("Seed", seed);

let module Gen = NewDepth.F (NewDepth.RandomConfig ());
let module Board = HexBox;

let module Paint' = Paint.F Board Gen;
let module Show' = Show.F Board Gen;

let options = Show'.{
  canvas_size: (1000.0, 1000.0),
  min_margin: 50.0,
  size_hint: 1 + Random.int 3,
};
let (canvas, ctx, state) = Show'.init options;

Show'.loop_debug options ctx state;
