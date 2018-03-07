module Ctx = Canvas.Ctx;

let sf = string_of_float;

let si = string_of_int;

let hsla = (h, s, l, a) =>
  "hsla("
  ++ si(h)
  ++ ", "
  ++ si(s)
  ++ "%, "
  ++ si(l)
  ++ "%, "
  ++ sf(a)
  ++ ")";

let draw_point = (ctx, count, age, dot_color, size, (x, y)) => {
  Ctx.setFillStyle(ctx, dot_color(age, count));
  /*Ctx.fillRect ctx (x -. size /. 2.0) (y -. size /. 2.0) size size*/
  Ctx.beginPath(ctx);
  Ctx.circle(ctx, x, y, size);
  Ctx.fill(ctx);
};

module type Config = {
  let unvisitedFill: option(string);
  let showTrails: bool;
  let wallColor: string;
  let batch: int;
  let showEdge: bool;
  let showWalls: bool;
  let showAge: bool;
  let dotColor: (int, int) => string;
  let dotSize: float;
  let edgeDotSize: float;
};

module Default = {
  let unvisitedFill = None;
  let showTrails = true;
  let batch = 1;
  let wallColor = "rgb(100, 100, 100)";
  let showEdge = true;
  let showWalls = true;
  let showAge = false;
  let dotColor = (age, total_age) =>
    hsla(0, 100, 100 * (total_age - age) / total_age, 0.3);
  let dotSize = 15.0;
  let edgeDotSize = 5.0;
};

module Draw = (Board: Shared.Board, Config: Config) => {
  let draw_wall = (ctx, wall) =>
    switch (wall) {
    | Shared.Line((p1, p2)) => Ctx.line(ctx, p1, p2)
    };
  let draw_walls = (ctx, bsize, csize, walls) =>
    List.iter(
      wall =>
        Board.drawable_wall(wall, bsize, csize)
        |> Utils.maybe(draw_wall(ctx))
        |> ignore,
      walls,
    );
  let vertex_dots = (ctx, bsize, csize, vertices, size) =>
    List.iter(
      vertex => {
        let (x, y) = Board.vertex_pos(vertex, bsize, csize);
        Ctx.beginPath(ctx);
        Ctx.circle(ctx, x, y, size);
        Ctx.fill(ctx);
      },
      vertices,
    );
  let dots = (ctx, bsize, csize, traveled, total_age, dot_color, size) =>
    List.iter(
      ({Shared.Edge.dest, age}) =>
        Board.vertex_pos(dest, bsize, csize)
        |> draw_point(ctx, total_age, age, dot_color, size),
      traveled,
    );
  let paths = (ctx, bsize, csize, traveled) =>
    List.iter(
      ({Shared.Edge.dest, src}) => {
        let a = Board.vertex_pos(src, bsize, csize);
        let b = Board.vertex_pos(dest, bsize, csize);
        Canvas.Ctx.line(ctx, a, b);
      },
      traveled,
    );
  let connections = (ctx, bsize, csize, adjacent) =>
    List.iter(
      ((src, dest)) => {
        let a = Board.vertex_pos(src, bsize, csize);
        let b = Board.vertex_pos(dest, bsize, csize);
        Canvas.Ctx.line(ctx, a, b);
      },
      adjacent,
    );
  let draw = (ctx, bsize, csize, walls, traveled, current, next) => {
    let (wsize, hsize) = csize;
    Canvas.Ctx.clearRect(ctx, 0.0, 0.0, wsize, hsize);
    if (Config.showWalls) {
      Canvas.Ctx.setStrokeStyle(ctx, Config.wallColor);
      Canvas.Ctx.strokeRect(ctx, 0.0, 0.0, wsize, hsize);
      draw_walls(ctx, bsize, csize, walls);
      Board.border_walls(bsize, csize) |> List.iter(draw_wall(ctx));
    };
    if (Config.showTrails) {
      Canvas.Ctx.setStrokeStyle(ctx, "rgb(200, 200, 200)");
      paths(ctx, bsize, csize, traveled);
    };
    if (Config.showAge) {
      dots(
        ctx,
        bsize,
        csize,
        traveled,
        Board.Shape.vertex_count(bsize),
        Config.dotColor,
        Config.dotSize,
      );
    };
    if (Config.showEdge) {
      Canvas.Ctx.setFillStyle(ctx, "green");
      vertex_dots(ctx, bsize, csize, current, Config.edgeDotSize);
      Canvas.Ctx.setFillStyle(ctx, "blue");
      vertex_dots(ctx, bsize, csize, next, Config.edgeDotSize);
    };
  };
};
