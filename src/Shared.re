
module Edge = {
  type edge = {src: int, dest: int, age: int};
};

module State = {
  type adjacency_list = array (list int);
  type state = {
    adjacency_list: adjacency_list,
    visited: array bool,
    current: list int,
    next: list int,
    age: int,
    traveled: list Edge.edge,
  };
  type t = state;
};

module type Generator = {
  let init: int => State.adjacency_list => State.t;
  let loop: State.t => list Edge.edge;
  let step: State.t => State.t;
  let spanning_tree: int => State.adjacency_list => list Edge.edge;
};

type canvas_size = (float, float);

type drawable_wall =
  | Line ((float, float), (float, float));

module type Board = {
  type size;
  let vertex_count: size => int;
  let adjacency_list: size => State.adjacency_list;
  let vertex_pos: int => size => canvas_size => (float, float);
  let drawable_wall: (int, int) => size => canvas_size => drawable_wall;
};

