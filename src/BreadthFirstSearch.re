
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

let rec loop state current next tree => {
  let (adjacency_list, visited) = state;
  switch (current) {
    | [] => {
      switch (next) {
        | [] => tree
        | _ => loop state (shuffle next) [] tree
      }
    }

    | [first, ...rest] => {
      let adjacents = Array.get adjacency_list first;
      let (next, tree) = inner (visited, first) adjacents next tree;
      loop state rest next tree
    }
  }
};

let spanning_tree vertices adjacency_list => {
  let visited = Array.make vertices false;

  let initial = Random.int vertices;
  Array.set visited initial true;

  loop (adjacency_list, visited) [initial] [] [];
};

