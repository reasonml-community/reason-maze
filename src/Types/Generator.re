
module PairSet = Set.Make {
  type t = (int, int);
  let compare a b => compare a b;
};

module IntMap = Map.Make {
  type t = int;
  let compare a b => compare a b;
};

module type T = {
  type state;
  type get_adjacent = int => list int;

  let edges: state => PairSet.t;
  let visited: state => IntMap.t bool;

  /* just does everything */
  let run: int => state;

  /* more granular */
  let init: int => state;
  let step: get_adjacent => state => state;
  let loop_to_end: get_adjacent => state => state;
  let finished: state => bool;
};
