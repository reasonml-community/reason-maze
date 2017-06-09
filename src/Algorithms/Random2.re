
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

let choose arr => Array.get arr (Random.int (Array.length arr));

let jump_to_new_block state => {
  let remaining = [%bs.raw "[]"];
  Array.iteri (fun i age => {
    if (age === 0) {
      Js.Array.push i remaining |> ignore;
    }
  }) state.visited;
  switch remaining {
  | [||] => state
  | _ => {
    let start = choose remaining;
    {...state, frontier: [|(start, start)|]}
  }
  }
};

let rec step get_adjacent state => {
  switch (state.frontier) {
  | [||] => state
  | _ => {
    switch (Js.Array.spliceInPlace pos::(Random.int (Array.length state.frontier)) remove::1 add::[||] state.frontier) {
    | [|(src, dest)|] => {
      if (Array.get state.visited dest > 0) {
        step get_adjacent 
        (switch (Array.length state.frontier) {
        | 0 => jump_to_new_block state
        | _ => state
        })
      } else {
        Array.set state.visited dest (state.step + 1);
        let others = get_adjacent dest
          |> List.filter (fun x => Array.get state.visited x === 0)
          |> List.map (fun x => (dest, x));
        let frontier = Array.append
            (Array.of_list others)
            state.frontier;
        let state = {
          ...state,
          step: state.step + 1,
          edges: Generator.PairSet.add (sortpair src dest) state.edges,
          frontier,
        };
        switch (Array.length state.frontier) {
        | 0 => jump_to_new_block state
        | _ => state
        }
      }
    }
    | _ => state
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