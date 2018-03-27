open Belt;

module type Config = {let maxHits: int; let joinOnHit: float;};

module RandomConfig = (()) => {
  let maxHits = 1 + Random.int(20);

  let joinOnHit = Random.float(1.0);
};

module F = (Config: Config) => {
  type state = {
    visited: array(int),
    edges: Utils.intPairSet,
    frontier: array((int, int)),
    step: int,
    active: option(((int, int), int)),
  };

  let init = size => {
    let start = Random.int(size);
    {
      visited: Array.make(size, 0),
      edges: Utils.intPairSet,
      frontier: [||],
      step: 0,
      active: Some(((start, start), 0)),
    };
  };

  let edges = state => state.edges;

  let visited = state => state.visited;

  let max_age = state => state.step;

  let finished = state => state.active == None;

  let sortpair = (a, b) => a > b ? (b, a) : (a, b);

  let add_edge = (edges, src, dest) => Set.add(edges, sortpair(src, dest));

  let shouldHit = prob =>
    switch (prob) {
    | 0.0 => false
    | 1.0 => true
    | _ => Random.float(1.0) < prob
    };

  let get_new = state => {
    let frontier = state.frontier;
    if (Array.length(frontier) === 0) {
      {...state, active: None};
    } else {
      switch (
        Js.Array.spliceInPlace(
          ~pos=Random.int(Array.length(frontier)),
          ~remove=1,
          ~add=[||],
          frontier,
        )
      ) {
      | [|item|] => {...state, frontier, active: Some((item, 0))}
      | _ => {...state, frontier}
      };
    };
  };

  let rec step = (get_adjacent, state) => {
    let step_count = state.step;
    let {edges} = state;
    switch (state.active) {
    | None => state
    | Some(((src, dest), hits)) =>
      if (Array.getExn(state.visited, dest) > 0) {
        step(get_adjacent, get_new(state));
      } else {
        let others =
          get_adjacent(dest)
          |> Utils.shuffle
          |> List.keepMap(_, x =>
               if (x === src) {
                 None;
               } else {
                 Some((dest, x));
               }
             );
        let step_count = step_count + 1;
        ignore(state.visited[dest] = step_count);
        let edges = add_edge(edges, src, dest);
        let rec loop = (adjacents, hit) =>
          switch (adjacents) {
          | [(esrc, edest), ...rest] =>
            if (Array.getExn(state.visited, edest) > 0) {
              if (hits > Config.maxHits) {
                let edges =
                  shouldHit(Config.joinOnHit) ?
                    add_edge(edges, esrc, edest) : edges;
                get_new({...state, edges, step: step_count});
              } else {
                loop(rest, true);
              };
            } else {
              let frontier =
                Array.concat(List.toArray(rest), state.frontier);
              {
                ...state,
                frontier,
                edges,
                step: step_count,
                active: Some(((esrc, edest), hit ? hits + 1 : hits)),
              };
            }
          | _ => get_new({...state, edges, step: step_count})
          };
        loop(others, false);
      }
    };
  };

  let step__ = (get_adjacent, state) =>
    switch (state.frontier) {
    | [||] => state
    | nonEmptyArray =>
      switch (
        Js.Array.spliceInPlace(
          ~pos=Random.int(Array.length(nonEmptyArray)),
          ~remove=1,
          ~add=[||],
          nonEmptyArray,
        )
      ) {
      | [|(src, dest)|] =>
        if (Array.getExn(state.visited, dest) > 0) {
          step(get_adjacent, state);
        } else {
          ignore(state.visited[dest] = state.step + 1);
          let others =
            get_adjacent(dest)
            |> List.keepMap(_, x =>
                 if (Array.getExn(state.visited, x) === 0) {
                   Some((dest, x));
                 } else {
                   None;
                 }
               );
          {
            ...state,
            step: state.step + 1,
            edges: Set.add(state.edges, sortpair(src, dest)),
            frontier: Array.concat(List.toArray(others), nonEmptyArray),
          };
        }
      | _ => assert false
      }
    };

  /* hmm these can be shared */
  let rec loop_to_end = (get_adjacent, state) =>
    if (! finished(state)) {
      loop_to_end(get_adjacent, step(get_adjacent, state));
    } else {
      state;
    };

  let run = (size, get_adjacent) => loop_to_end(get_adjacent, init(size));
};
