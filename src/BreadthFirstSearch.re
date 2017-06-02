
let rec inner state adjacents next traveled age => {
  let (visited, src) = state;
  switch (adjacents) {
    | [] => (next, traveled, age)
    | [dest, ...rest] => {
      if (Array.get visited dest) {
        inner state rest next traveled age;
      } else {
        Array.set visited dest true;
        inner state rest [dest, ...next] [Shared.Edge.{src, dest, age}, ...traveled] (age + 1);
      }
    }
  }
};

let step state => {
  open Shared.State;
  let {adjacency_list, visited, current, next, traveled, age} = state;
  switch (current) {
    | [] => state

    | [src] => {
      let adjacents = Array.get adjacency_list src;
      let (next, traveled, age) = inner (visited, src) adjacents next traveled age;
      {...state, current: next, next: [], traveled, age}
    }

    | [src, ...rest] => {
      let adjacents = Array.get adjacency_list src;
      let (next, traveled, age) = inner (visited, src) adjacents next traveled age;
      {...state, current: Utils.shuffle rest, next, traveled, age}
    }
  }
};

let init vertices adjacency_list => {
  let visited = Array.make vertices false;

  let initial = Random.int vertices;
  Array.set visited initial true;
  Shared.State.{adjacency_list, visited, current: [initial], next: [], traveled: [], age: 0}
};

let rec loop state => {
  switch (step state) {
    | {current: [], traveled} => traveled
    | state => loop state
  }
};

let spanning_tree vertices adjacency_list => {
  init vertices adjacency_list |> loop
};

