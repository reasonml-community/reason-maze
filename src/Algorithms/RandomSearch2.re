open Belt;

module State = {
  type t = {
    adjacency_list: Shared.adjacency_list,
    visited: array(bool),
    current: list(int),
    next: list(int),
    age: int,
    traveled: list(Shared.Edge.edge),
  };

  let traveled = t => t.traveled;

  let current = t => t.current;

  let next = t => t.next;

  let age = t => t.age;

  let finished = t => t.current === [];
};

let rec add_adjacent_edges = (state, adjacents, next, traveled, age) => {
  let (visited, src) = state;
  switch (adjacents) {
  | [] => (next, traveled, age)
  | [dest, ...rest] =>
    if (Array.getExn(visited, dest)) {
      add_adjacent_edges(state, rest, next, traveled, age);
    } else {
      ignore(visited[dest] = true);
      add_adjacent_edges(
        state,
        rest,
        [dest, ...next],
        [Shared.Edge.{src, dest, age}, ...traveled],
        age + 1,
      );
    }
  };
};

let step = state => {
  open State;
  let {adjacency_list, visited, current, next, traveled, age} = state;
  switch (current) {
  | [] => state
  | [src] =>
    let adjacents = Array.getExn(adjacency_list, src);
    let (next, traveled, age) =
      add_adjacent_edges((visited, src), adjacents, next, traveled, age);
    {...state, current: Utils.shuffle(next), next: [], traveled, age};
  | [src, ...rest] =>
    let adjacents = Array.getExn(adjacency_list, src);
    let (next, traveled, age) =
      add_adjacent_edges((visited, src), adjacents, next, traveled, age);
    {...state, current: Utils.shuffle(rest @ next), traveled, age};
  };
};

let rec loop = state =>
  switch (step(state)) {
  | {current: [], traveled} => traveled
  | state => loop(state)
  };

let init = (vertices, adjacency_list) => {
  let visited = Array.make(vertices, false);
  let initial = Random.int(vertices);
  ignore(visited[initial] = true);
  State.{
    adjacency_list,
    visited,
    current: [initial],
    next: [],
    traveled: [],
    age: 0,
  };
};

let spanning_tree = (vertices, adjacency_list) =>
  loop(init(vertices, adjacency_list));
