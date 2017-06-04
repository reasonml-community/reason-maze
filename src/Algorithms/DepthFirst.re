
module State = {
  type t = {
    adjacency_list: Shared.adjacency_list,
    visited: array bool,
    current: array Shared.Edge.edge,
    age: int,
    traveled: list Shared.Edge.edge,
    active: option Shared.Edge.edge,
  };
  let traveled t => t.traveled;
  let current t => List.map (fun {Shared.Edge.dest} => dest) (Array.to_list t.current);
  let next _ => [];
  let age t => t.age;
  let finished t => t.active === None;
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

let grab_random items len => {
  let idx = Random.int len;
  let rec loop i items => {

  };
};

let step state => {
  open State;
  let {adjacency_list, visited, current, active, traveled, age} = state;
  /*Js.log active;*/
  switch (active) {
    | None => state
    | Some src => {
      if (Array.get visited src.dest) {
        if (Array.length current === 0) {
          {...state, active: None}
        } else {
          let idx = Random.int (Array.length current);
          switch (Js.Array.spliceInPlace pos::idx remove::1 add::[||] current) {
            | [|item|] => {
                /*Js.Array.unshift item current |> ignore;*/
                {...state, current, active: Some item}
              }
            | _ => {...state, current}
          }
        }
      } else {
        let adjacents = Array.get adjacency_list src.dest |> Utils.shuffle;
        let edges = List.map (fun dest => {Shared.Edge.src: src.dest, dest, age: 0}) adjacents;
        switch (edges) {
        | [edge, ...others] => {
          let age = age + 1;
          Array.set visited src.dest true;
          let traveled = [{...src, age}, ...traveled];
          let current = Array.append (Array.of_list others) current;
          /*Js.Array.unshift edge current |> ignore;*/
          {...state, traveled, age, current, active: Some edge}
        }
        | _ => {...state, current}
        }
      }
    }
  }
};

let rec loop state => {
  switch (step state) {
    | {active: None, traveled} => traveled
    | state => loop state
  }
};

let init vertices adjacency_list => {
  let visited = Array.make vertices false;

  let initial = Random.int vertices;
  State.{
    adjacency_list,
    visited,
    current: [||],
    active: Some {Shared.Edge.dest: initial, src: initial, age: 0},
    traveled: [],
    age: 0
  }
};

let spanning_tree vertices adjacency_list => {
  loop (init vertices adjacency_list)
};
