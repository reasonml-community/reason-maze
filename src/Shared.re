
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

module StepResponse = {
  type edge = (int, int);
  type step_response =
    | Epoch (list int, list edge)
    | Step (list int, list int, list edge)
    | Done (list edge)
};

module type Board = {
  type t;
  type size;
  let vertex_count: size => int;
  let adjacency_list: size => array (list int);
  let drawable_walls: (int, int) => size => (float, float) => drawable_wall;
};

let wall_set tree => WallSet.of_list (
  List.map (fun (a, b) => a > b ? (b, a) : (a, b)) tree
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
  let clear = Shared.wall_set tree;
  get_walls full clear;
}

