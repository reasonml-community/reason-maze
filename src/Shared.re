
type pos = (int, int);
type drawable_wall =
  | Line ((float, float), (float, float));
type size = (float, float);

module type Board = {
  type t;
  type size;
  let num_vertices: size => int;
  let adjacency_list: size => list (int, int);
  let drawable_walls: list (int, int) => size => (float, float) => list drawable_wall;
};

module type Old_Board = {
  type t;
  module Direction: {
    type t;
  };
  let create: int => int => t;
  let adjacent: t => pos => list Direction.t;
  let open_adjacent: t => pos => list Direction.t;
  let is_open: t => pos => Direction.t => bool;
  let add_wall: t => pos => Direction.t => unit;
  let drawable_walls: t => size => list drawable_wall;
};

