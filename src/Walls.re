open Belt;

let get_walls = (full, clear) => {
  let (_, res) =
    Array.reduce(full, (0, []), ((src, res), ends) =>
      (
        src + 1,
        List.reduce(ends, [], (walls, vend) =>
          vend < src ?
            walls :
            Set.has(clear, (src, vend)) ? walls : [(src, vend), ...walls]
        )
        @ res,
      )
    );
  res;
};

let wall_set = traveled =>
  List.toArray(traveled)
  |> Array.map(_, ({Shared.Edge.src, dest}) =>
       src > dest ? (dest, src) : (src, dest)
     )
  |> Set.fromArray(~id=(module Utils.IntPairComparator));

let walls_remaining = (full, traveled) => {
  let clear = wall_set(traveled);
  get_walls(full, clear);
};
