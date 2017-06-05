
type state = {
  visited: array int,
  edges: Generator.PairSet.t,
  frontier: array (int, int),
  step: int,
};

let init size => {
  let start = Random.int size;
  /*let start = 0;*/
  {
    visited: Array.make size 0,
    edges: Generator.PairSet.empty,
    frontier: [|(start, start)|],
    step: 0,
  };
};

let edges state => state.edges;
let visited state => state.visited;
let max_age state => state.step;

let sortpair a b => a > b ? (b, a) : (a, b);

let rec step get_adjacent state => {
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

let finished state => state.frontier == [||];

/* hmm these can be shared */
let rec loop_to_end get_adjacent state => {
  if (not (finished state)) {
    loop_to_end get_adjacent (step get_adjacent state)
  } else {
    state
  }
};
let run size get_adjacent => loop_to_end get_adjacent (init size)