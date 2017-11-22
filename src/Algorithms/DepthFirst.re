module type Config = {let maxHits: int; let joinOnHit: float;};

let shouldHit = (prob) =>
  switch prob {
  | 0.0 => false
  | 1.0 => true
  | _ => Random.float(1.0) < prob
  };

module F = (Config: Config) => {
  module State = {
    type t = {
      adjacency_list: Shared.adjacency_list,
      visited: array(bool),
      current: array(Shared.Edge.edge),
      age: int,
      traveled: list(Shared.Edge.edge),
      active: option((Shared.Edge.edge, int))
    };
    let traveled = (t) => t.traveled;
    let current = (t) => List.map(({Shared.Edge.dest}) => dest, Array.to_list(t.current));
    let next = (t) =>
      switch t.active {
      | Some((x, _)) => [x.Shared.Edge.dest]
      | None => []
      };
    let age = (t) => t.age;
    let finished = (t) => t.active === None;
  };
  let adjacent_edges = (visited, src, adjacents) =>
    List.fold_left(
      (arr, dest) =>
        if (visited[dest]) {
          arr
        } else {
          [Shared.Edge.{src, dest, age: 0}, ...arr]
        },
      [],
      adjacents
    );
  let get_new = (state) => {
    open State;
    let current = state.current;
    if (Array.length(current) === 0) {
      {...state, active: None}
    } else {
      switch (
        Js.Array.spliceInPlace(
          ~pos=Random.int(Array.length(current)),
          ~remove=1,
          ~add=[||],
          current
        )
      ) {
      | [|item|] => {...state, current, active: Some((item, 0))}
      | _ => {...state, current}
      }
    }
  };
  let step = (state) => {
    open State;
    let {adjacency_list, visited, current, active, traveled, age} = state;
    switch active {
    | None => state
    | Some((src, hits)) =>
      if (visited[src.dest]) {
        get_new({...state, traveled})
      } else {
        let adjacents = adjacency_list[src.dest] |> Utils.shuffle;
        let edges = List.map((dest) => {Shared.Edge.src: src.dest, dest, age: 0}, adjacents);
        let edges = List.filter((x) => x.Shared.Edge.dest !== src.src, edges);
        let age = age + 1;
        visited[src.dest] = true;
        let traveled = [{...src, age}, ...traveled];
        let rec loop = (edges, state, hit) =>
          switch edges {
          | [edge, ...others] =>
            if (visited[edge.Shared.Edge.dest]) {
              if (hits > Config.maxHits /* || others === []*/) {
                let traveled =
                  shouldHit(Config.joinOnHit) ? [{...edge, age}, ...traveled] : traveled;
                get_new({...state, traveled, age})
              } else {
                loop(others, state, true)
              }
            } else {
              let current = Array.append(Array.of_list(others), current);
              /*Js.Array.unshift edge current |> ignore;*/
              {...state, traveled, age, current, active: Some((edge, hit ? hits + 1 : hits))}
            }
          | _ =>
            Js.log("ran out of edges");
            Js.log(List.length(edges));
            get_new({...state, traveled, age})
          };
        loop(edges, state, false)
      }
    }
  };
  let rec loop = (state) =>
    switch (step(state)) {
    | {active: None, traveled} => traveled
    | state => loop(state)
    };
  let init = (vertices, adjacency_list) => {
    let visited = Array.make(vertices, false);
    let initial = Random.int(vertices);
    State.{
      adjacency_list,
      visited,
      current: [||],
      active: Some(({Shared.Edge.dest: initial, src: initial, age: 0}, 0)),
      traveled: [],
      age: 0
    }
  };
  let spanning_tree = (vertices, adjacency_list) => loop(init(vertices, adjacency_list));
};
