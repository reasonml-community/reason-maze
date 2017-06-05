type state = {
  visited: array int,
  edges: Generator.PairSet.t,
  frontier: list (int, int),
  next: list (int, int),
  step: int,
};

let init size => {
  let start = Random.int size;
  /*let start = 0;*/
  {
    visited: Array.make size 0,
    edges: Generator.PairSet.empty,
    frontier: [(start, start)],
    next: [],
    step: 0,
  };
};

let edges state => state.edges;
let visited state => state.visited;
let max_age state => state.step;

let sortpair a b => a > b ? (b, a) : (a, b);

let add_edges adjacents state (pre, src) => {
  Array.set state.visited src (state.step + 1);
  let next = List.fold_left
  (fun next dest => {
    if (Array.get state.visited dest > 0) {
      next
    } else {
      Array.set state.visited dest (state.step + 1);
      [(src, dest), ...next]
    }
  })
  state.next
  adjacents;
  (next, Generator.PairSet.add (sortpair pre src) state.edges, state.step + 1)
};

let step get_adjacent state => {
  switch (state.frontier) {
  | [] => state
  | [(pre, src)] => {
    let (frontier, edges, step) = add_edges (get_adjacent src) state (pre, src);
    /* TODO add option to shuffle or not */
    {...state, frontier: Utils.shuffle frontier, next: [], edges, step}
  }
  | [(pre, src), ...rest] => {
    let (next, edges, step) = add_edges (get_adjacent src) state (pre, src);
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
