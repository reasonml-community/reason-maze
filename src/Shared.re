
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

let get_walls full clear => {
  let (_, res) = Array.fold_left
    (fun (i, res) ends => {
      let src = i;
      (
        i + 1,
        (List.fold_left
        (fun walls vend => {
          vend < src
            ? walls
            : (WallSet.mem (src, vend) clear
              ? walls
              : [(src, vend), ...walls])
        })
        []
        ends) @ res
      )
    }) (0, []) full;
  res
};

let wall_set traveled => WallSet.of_list (
  List.map (fun {Edge.src, dest} => src > dest ? (dest, src) : (src, dest))
  traveled
);

let walls_remaining full traveled => {
  let clear = wall_set traveled;
  get_walls full clear;
}

/*
let _walls: array (array int) => array Edge.edge => array (int, int) =
[%bs.raw {|
  function (full, traveled) {
    var seen = {}
    traveled.forEach(([src, dest]) => {
      seen[Math.min(src, dest) + ':' + Math.max(src,dest)] = true
    })
    var res = []
    full.forEach((dests, i) => {
      dests.forEach(d => {
        if (d < i) return
        if (!seen[i + ':' + d]) {
          res.push([i, d])
        }
      })
    })
    console.log(full, traveled, res)
    return res;
  }
|}];

let walls_remaining full traveled => {
  Array.to_list (_walls (Array.map Array.of_list full) (Array.of_list traveled))
}
*/

