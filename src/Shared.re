
type drawable_wall =
  | Line ((float, float), (float, float));

module Edge = {
  type edge = {src: int, dest: int, age: int};
};

module State = {
  type state = {
    adjacency_list: array (list int),
    visited: array bool,
    current: list int,
    next: list int,
    age: int,
    traveled: list Edge.edge,
  };
  type t = state;
};

module type Board = {
  type t;
  type size;
  let vertex_count: size => int;
  let adjacency_list: size => array (list int);
  let vertex_pos: int => size => (float, float) => (float, float);
  let drawable_wall: (int, int) => size => (float, float) => drawable_wall;
};

module type Generator = {
  let spanning_tree: int => array (list int) => list Edge.edge;
};

