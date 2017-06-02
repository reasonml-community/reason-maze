
module Wall = {
  type t = (int, int);
  let compare (x, y) (a, b) => {
    switch (compare x a) {
      | 0 => compare y b
      | v => v
    }
  };
};

module WallSet = Set.Make(Wall);

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

let wall_set tree => WallSet.of_list (
  List.map (fun {Edge.src, dest} => src > dest ? (dest, src) : (src, dest)) tree
);

let get_walls full clear => {
  let (i, res) = Array.fold_left
  (fun (i, res) ends => {
    (
      i + 1,
      (List.fold_left
      (fun res vend => {
        vend < i
          ? res
          : (WallSet.mem (i, vend) clear
            ? res
            : [(i, vend), ...res])
      })
      []
      ends) @ res
    )
  })
  (0, [])
  full;
  res
};

let walls_remaining full tree => {
  let clear = wall_set tree;
  get_walls full clear;
}

