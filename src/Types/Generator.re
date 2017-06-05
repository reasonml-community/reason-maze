
module Edge = {
  type t = {src: int, dest: int, age: int};
};

module type T = {
  type state;
  type get_adjacent = int => list int;
  /* just does everything */
  let run: int => list Edge.t;
  /* more granular */
  let init: int => state;
  let step: get_adjacent => state => state;
  let loop: get_adjacent => state => list Edge.t;
  let finished: state => bool;
  let edges: state => list Edge.t;
};
