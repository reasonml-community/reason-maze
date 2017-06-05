
module Edge = {
  type t = {src: int, dest: int, age: int};
};

module type T = {
  type state;
  /* just does everything */
  let run: int => list Edge.t;
  /* more granular */
  let init: int => state;
  let step: state => state;
  let loop: state => list Edge.t;
  let finished: state => bool;
  let edges: state => list Edge.t;
};
