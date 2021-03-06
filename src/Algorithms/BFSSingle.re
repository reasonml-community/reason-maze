open Belt;

type state = {
  visited: array(int),
  edges: Utils.intPairSet,
  frontier: list((int, int)),
  next: list((int, int)),
  step: int,
};

let init = size => {
  let start = Random.int(size);
  /*let start = 0;*/
  {
    visited: Array.make(size, 0),
    edges: Utils.intPairSet,
    frontier: [(start, start)],
    next: [],
    step: 0,
  };
};

let edges = state => state.edges;

let visited = state => state.visited;

let max_age = state => state.step;

let sortpair = (a, b) => a > b ? (b, a) : (a, b);

let add_edges = (adjacents, state, (pre, src)) => {
  ignore(state.visited[src] = state.step + 1);
  let next =
    List.reduce(adjacents, state.next, (next, dest) =>
      if (Array.getExn(state.visited, dest) > 0) {
        next;
      } else {
        ignore(state.visited[dest] = state.step + 1);
        [(src, dest), ...next];
      }
    );
  (next, Set.add(state.edges, sortpair(pre, src)), state.step + 1);
};

let step = (get_adjacent, state) =>
  switch (state.frontier) {
  | [] => state
  | [(pre, src)] =>
    let (frontier, edges, step) =
      add_edges(get_adjacent(src), state, (pre, src));
    /* TODO add option to shuffle or not */
    {...state, frontier: Utils.shuffle(frontier), next: [], edges, step};
  | [(pre, src), ...rest] =>
    let (next, edges, step) =
      add_edges(get_adjacent(src), state, (pre, src));
    {...state, frontier: rest, next, edges, step};
  };

let finished = state => state.frontier === [];

/* hmm these can be shared */
let rec loop_to_end = (get_adjacent, state) =>
  if (! finished(state)) {
    loop_to_end(get_adjacent, step(get_adjacent, state));
  } else {
    state;
  };

let run = (size, get_adjacent) => loop_to_end(get_adjacent, init(size));
