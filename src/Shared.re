
module Edge = {
  type edge = {src: int, dest: int, age: int};
};

type adjacency_list = array (list int);

module type Generator = {
  module State: {
    type t;
    let traveled: t => list Edge.edge;
    let current: t => list int;
    let next: t => list int;
    let age: t => int;
  };
  let init: int => adjacency_list => State.t;
  let loop: State.t => list Edge.edge;
  let step: State.t => State.t;
  let spanning_tree: int => adjacency_list => list Edge.edge;
};

type canvas_size = (float, float);

type drawable_wall =
  | Line ((float, float), (float, float));

module type Board = {
  type size;
  let vertex_count: size => int;
  let adjacency_list: size => adjacency_list;
  let vertex_pos: int => size => canvas_size => (float, float);
  let drawable_wall: (int, int) => size => canvas_size => drawable_wall;
  let border_walls: size => canvas_size => list drawable_wall;
};

