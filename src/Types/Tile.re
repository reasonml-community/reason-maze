
module type T = {
  module Coord: Coord.T;
  type direction;
  let adjacents: Coord.t => list direction;
  let adjacent_coord: Coord.t => direction => Coord.t;
  let direction_to_border: Coord.t => direction => Border.t;
};

module type Simple = {
  module Coord: Coord.T;
  type direction;
  let adjacents: list direction;
  let adjacent_coord: direction => Coord.t;
  let direction_to_border: direction => Border.t;
};

module FromSimple (Simple: Simple)/*: (T with module Coord := Simple.Coord)*/ => {
  module Coord = Simple.Coord;
  type direction = Simple.direction;
  let adjacents _ => Simple.adjacents;
  let adjacent_coord _ direction => {
    (Simple.adjacent_coord direction)
    /*Coord.offset coord (Simple.adjacent_coord direction)*/
  };
  let direction_to_border _ => Simple.direction_to_border;
};

/*
module type Transform = { type a; type b; let f: a => b; };
module type Relative = 

ok, so I need to be able to constrain these so that 
module FromRelative (Relative: Relative) (Transform: Transform): T => {
  module Coord = Relative.Coord;
  type direction = Relative.direction;
  let adjacents
};
*/