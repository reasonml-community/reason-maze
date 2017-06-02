
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

let get_walls full clear => {
  let (_, res) = Array.fold_left
    (fun (src, res) ends => {
      (
        src + 1,
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
  List.map (fun {Shared.Edge.src, dest} => src > dest ? (dest, src) : (src, dest))
  traveled
);

let walls_remaining full traveled => {
  let clear = wall_set traveled;
  get_walls full clear;
}

