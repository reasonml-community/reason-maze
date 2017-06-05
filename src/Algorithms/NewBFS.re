type state = {
  visited: array int,
  edges: Generator.PairSet.t,
  frontier: list int,
  next: list int,
  step: int,
};

let init size => {
  visited: Array.make size 0,
  edges: Generator.PairSet.empty,
  frontier: [Random.int size],
  next: [],
  step: 0,
};

let edges state => state.edges;
let visited state => state.visited;

let sortpair a b => a > b ? (b, a) : (a, b);

let add_edges adjacents state src => {
  List.fold_left
  (fun (next, edges, step) dest => {
    if (Array.get state.visited dest > 0) {
      (next, edges, step)
    } else {
      Array.set state.visited dest (step + 1);
      ([dest, ...next], Generator.PairSet.add (sortpair src dest) edges, step + 1)
    }
  })
  (state.next, state.edges, state.step)
  adjacents
};

let step get_adjacent state => {
  switch (state.frontier) {
  | [] => state
  | [src] => {
    let (frontier, edges, step) = add_edges (get_adjacent src) state src;
    /* TODO add option to shuffle or not */
    {...state, frontier: Utils.shuffle frontier, next: [], edges, step}
  }
  | [src, ...rest] => {
    let (next, edges, step) = add_edges (get_adjacent src) state src;
    {...state, frontier: rest, next, edges, step}
  }
  }
};

let finished state => state.frontier === [];

/* hmm these can be shared */
let rec loop_to_end get_adjacent state => {
  if (not (finished state)) {
    loop_to_end get_adjacent (step get_adjacent state)
  } else {
    state
  }
};
let run size get_adjacent => loop_to_end get_adjacent (init size)