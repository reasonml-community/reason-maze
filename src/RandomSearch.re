
module State = {
  type t = {
    adjacency_list: Shared.adjacency_list,
    visited: array bool,
    current: list Shared.Edge.edge,
    age: int,
    traveled: list Shared.Edge.edge,
  };
  let traveled t => t.traveled;
  let current t => List.map (fun {Shared.Edge.dest} => dest) t.current;
  let next t => [];
  let age t => t.age;
};

let rec add_adjacent_edges state adjacents next age => {
  let (visited, src) = state;
  switch (adjacents) {
    | [] => (next, age)
    | [dest, ...rest] => {
      if (Array.get visited dest) {
        add_adjacent_edges state rest next age;
      } else {
        add_adjacent_edges state rest
          [Shared.Edge.{src, dest, age}, ...next]
          age;
      }
    }
  }
};

let step state => {
  open State;
  let {adjacency_list, visited, current, traveled, age} = state;
  switch (current) {
    | [] => state

    | [src, ...rest] => {
      if (Array.get visited src.dest) {
        {...state, current: rest}
      } else {
        let adjacents = Array.get adjacency_list src.dest;
        Array.set visited src.dest true;
        let age = age + 1;
        let traveled = [{...src, age}, ...traveled];
        let (next, age) = add_adjacent_edges (visited, src.dest) adjacents rest age;
        {...state, current: Utils.shuffle next, traveled, age}
      }
    }
  }
};

let rec loop state => {
  switch (step state) {
    | {current: [], traveled} => traveled
    | state => loop state
  }
};

let init vertices adjacency_list => {
  let visited = Array.make vertices false;

  let initial = Random.int vertices;
  State.{
    adjacency_list,
    visited,
    current: [Shared.Edge.{dest: initial, src: initial, age: 0}],
    traveled: [],
    age: 0
  }
};

let spanning_tree vertices adjacency_list => {
  loop (init vertices adjacency_list)
};

