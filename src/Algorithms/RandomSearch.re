
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
  let next _ => [];
  let age t => t.age;
  let finished t => t.current === [];
};

let adjacent_edges visited src adjacents => {
  List.fold_left 
  (fun arr dest => {
    if (Array.get visited dest) {
      arr
    } else {
      [Shared.Edge.{src, dest, age: 0}, ...arr]
    }
  })
  []
  adjacents
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
        let next = rest @ adjacent_edges visited src.dest adjacents;
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
    current: [{Shared.Edge.dest: initial, src: initial, age: 0}],
    traveled: [],
    age: 0
  }
};

let spanning_tree vertices adjacency_list => {
  loop (init vertices adjacency_list)
};

