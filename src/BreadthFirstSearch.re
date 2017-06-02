
let shuffle d => {
    let nd = List.map (fun c => (Random.bits (), c)) d;
    let sond = List.sort compare nd;
    List.map snd sond;
};

let rec inner state adjacents next tree => {
  let (visited, first) = state;
  switch (adjacents) {
    | [] => (next, tree)
    | [one, ...rest] => {
      if (Array.get visited one) {
        inner state rest next tree;
      } else {
        Array.set visited one true;
        inner state rest [one, ...next] [(first, one), ...tree];
      }
    }
  }
};

open Shared.StepResponse;

let step adjacency_list visited current next tree => {
  switch (current) {
    | [] => {
      switch (next) {
        | [] => Done tree
        | _ => Epoch ((shuffle next), tree)
      }
    }

    | [first, ...rest] => {
      let adjacents = Array.get adjacency_list first;
      let (next, tree) = inner (visited, first) adjacents next tree;
      Step (rest, next, tree)
    }
  }
};

let spanning_tree vertices adjacency_list => {
  let visited = Array.make vertices false;

  let initial = Random.int vertices;
  Array.set visited initial true;

  let rec loop current next tree => {
    switch (step adjacency_list visited current next tree) {
      | Done tree => tree
      | Epoch (next, tree) => loop next [] tree
      | Step (current, next, tree) => loop current next tree
    }
  };

  loop [initial] [] [];
};

