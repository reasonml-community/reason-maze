type get_adjacent = int => list(int);

module type T = {
  type state;
  let edges: state => Utils.intPairSet; /* pairs are *ordered*, lower first */
  let visited: state => array(int); /* 0 means unvisited */
  let max_age: state => int;
  /* just does everything */
  let run: (int, get_adjacent) => state;
  /* more granular */
  let init: int => state;
  let step: (get_adjacent, state) => state;
  let loop_to_end: (get_adjacent, state) => state;
  let finished: state => bool;
};
