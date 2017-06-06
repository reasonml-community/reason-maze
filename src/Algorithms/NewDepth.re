
type state = {
  visited: array int,
  edges: Generator.PairSet.t,
  frontier: array (int, int),
  step: int,
  active: option ((int, int), int),
};

let init size => {
  let start = Random.int size;
  {
    visited: Array.make size 0,
    edges: Generator.PairSet.empty,
    frontier: [||],
    step: 0,
    active: Some ((start, start), 0)
  }
};

let edges state => state.edges;
let visited state => state.visited;
let max_age state => state.step;

let finished state => state.active == None;

let sortpair a b => a > b ? (b, a) : (a, b);

let maxHits = 1;
let joinOnHit = 0.9;

let add_edge edges src dest => 
  Generator.PairSet.add (sortpair src dest) edges;

let shouldHit prob => {
  switch prob {
  | 0.0 => false
  | 1.0 => true
  | _ => Random.float 1.0 < prob
  }
};

let get_new state => {
  let frontier = state.frontier;
  if (Array.length frontier === 0) {
    {...state, active: None}
  } else {
    switch (Js.Array.spliceInPlace pos::(Random.int (Array.length frontier)) remove::1 add::[||] frontier) {
      | [|item|] => {...state, frontier, active: Some (item, 0)}
      | _ => {...state, frontier}
    }
  }
};

let rec step get_adjacent state => {
  let step_count = state.step;
  switch (state.active) {
  | None => state
  | Some ((src, dest), hits) => {
    if (Array.get state.visited dest > 0) {
      step get_adjacent (get_new state)
    } else {
      let others = get_adjacent dest
        |> Utils.shuffle
        |> List.filter (fun x => x !== src)
        |> List.map (fun x => (dest, x));
      let step_count = step_count + 1;
      Array.set state.visited dest step_count;
      let edges = add_edge state.edges src dest;

      let rec loop adjacents hit => {
        switch adjacents {
        | [(esrc, edest), ...rest] => {
          if (Array.get state.visited edest > 0) {
            if (hits > maxHits) {
              let edges = (shouldHit joinOnHit)
              ? add_edge state.edges esrc edest
              : state.edges;
              get_new {...state, edges, step: step_count}
            } else {
              loop rest true
            }
          } else {
            let frontier = Array.append (Array.of_list rest) state.frontier;
            {...state, frontier, edges, step: step_count,
              active: Some ((esrc, edest), hit ? hits + 1 : hits)
            }
          }
        }
        | _ => get_new {...state, edges, step: step_count}
        }
      };
      loop others false;
    }
  }
  }
};

let rec step__ get_adjacent state => {
  switch (state.frontier) {
  | [||] => state
  | _ => {
    switch (Js.Array.spliceInPlace pos::(Random.int (Array.length state.frontier)) remove::1 add::[||] state.frontier) {
    | [|(src, dest)|] => {
      if (Array.get state.visited dest > 0) {
        step get_adjacent state
      } else {
        Array.set state.visited dest (state.step + 1);
        let others = get_adjacent dest
          |> List.filter (fun x => Array.get state.visited x === 0)
          |> List.map (fun x => (dest, x));
        {
          ...state,
          step: state.step + 1,
          edges: Generator.PairSet.add (sortpair src dest) state.edges,
          frontier: Array.append
            (Array.of_list others)
            state.frontier,
        }
      }
    }
    }
  }
  }
};

/* hmm these can be shared */
let rec loop_to_end get_adjacent state => {
  if (not (finished state)) {
    loop_to_end get_adjacent (step get_adjacent state)
  } else {
    state
  }
};

let run size get_adjacent => loop_to_end get_adjacent (init size)