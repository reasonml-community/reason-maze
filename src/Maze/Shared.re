open Belt;

module Edge = {
  type edge = {
    src: int,
    dest: int,
    age: int,
  };
};

type adjacency_list = array(list(int));

let optmap = (fn, lst) =>
  List.reduce(lst, [], (res, v) =>
    switch (fn(v)) {
    | None => res
    | Some(x) => [x, ...res]
    }
  );

module type Generator = {
  module State: {
    type t;
    let finished: t => bool;
    let traveled: t => list(Edge.edge);
    let current: t => list(int);
    let next: t => list(int);
    let age: t => int;
  };
  let init: (int, adjacency_list) => State.t;
  let loop: State.t => list(Edge.edge);
  let step: State.t => State.t;
  let spanning_tree: (int, adjacency_list) => list(Edge.edge);
};

type canvas_size = (float, float);

type drawable_wall =
  | Line(((float, float), (float, float)));

let transform_wall = (wall, scale, (dx, dy)) =>
  Utils.Float.(
    switch (wall) {
    | Line(((x, y), (a, b))) =>
      Line((
        (x * scale + dx, y * scale + dy),
        (a * scale + dx, b * scale + dy),
      ))
    }
  );

module type Tile = {
  type direction;
  let to_direction: ((int, int)) => option(direction);
  /*let from_direction: direction => (int, int);*/
  let wall_in_direction: direction => drawable_wall;
  let adjacent: ((int, int)) => list((int, int));
};

module type Draw = {let draw: (Canvas.ctx, 'a, (float, float)) => unit;};

module type BoardShape = {
  type shape;
  module Tile: Tile;
  let to_vertex: (shape, (int, int)) => option(int);
  let from_vertex: (shape, int) => (int, int);
  let vertex_count: shape => int;
  let all_coordinates: shape => array((int, int));
  let coord_to_board: (shape, canvas_size, (int, int)) => (float, float);
  let scale: (shape, canvas_size) => float;
  let border_walls: shape => list(((int, int), Tile.direction));
};

module type Board = {
  module Shape: BoardShape;
  let adjacency_list: Shape.shape => adjacency_list;
  let vertex_pos: (int, Shape.shape, canvas_size) => (float, float);
  let drawable_wall:
    ((int, int), Shape.shape, canvas_size) => option(drawable_wall);
  let border_walls: (Shape.shape, canvas_size) => list(drawable_wall);
};

module Board = (Shape: BoardShape) => {
  module Shape = Shape;

  let border_walls = (shape, size) =>
    List.map(
      Shape.border_walls(shape),
      (((x, y), direction)) => {
        let wall = Shape.Tile.wall_in_direction(direction);
        let scale = Shape.scale(shape, size);
        let offset = Shape.coord_to_board(shape, size, (x, y));
        transform_wall(wall, scale, offset);
      },
    );

  let adjacency_list = shape => {
    let res = Array.make(Shape.vertex_count(shape), []);
    Shape.all_coordinates(shape)
    |> Array.forEachWithIndex(_, (i, (x, y)) =>
         ignore(
           res[i] =
             Shape.Tile.adjacent((x, y))
             |> optmap(((a, b)) => Shape.to_vertex(shape, (x + a, y + b))),
         )
       );
    res;
  };

  let (|?<) = (a, b) =>
    switch (b) {
    | Some(x) => Some(a(x))
    | None => None
    };

  let vertex_pos = (v, shape, size) =>
    Shape.coord_to_board(shape, size, Shape.from_vertex(shape, v));

  let drawable_wall = ((src, dest), shape, size) => {
    let (x, y) = Shape.from_vertex(shape, src);
    let (a, b) = Shape.from_vertex(shape, dest);
    switch (Shape.Tile.to_direction((a - x, b - y))) {
    | None =>
      /*Js.log ("Bad direction", a-x, b-y, x, y, a, b);*/
      None
    | Some(direction) =>
      let wall = Shape.Tile.wall_in_direction(direction);
      let scale = Shape.scale(shape, size);
      let offset = Shape.coord_to_board(shape, size, (x, y));
      Some(transform_wall(wall, scale, offset));
    };
  };
};
/*
 module type Board = {
   type shape;
   let vertex_count: shape => int;
   let adjacency_list: shape => adjacency_list;
   let vertex_pos: int => shape => canvas_size => (float, float);
   let drawable_wall: (int, int) => shape => canvas_size => drawable_wall;
   let border_walls: shape => canvas_size => list drawable_wall;
 };
 */
