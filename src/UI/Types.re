
module Board = {
  type t =
    | Circle
    | HexBox
    | Hexagon
    | Triangle
    | HexTriangle
    | Rect;
  
  let all = [|Circle, HexBox, Hexagon, Triangle, HexTriangle, Rect|];

  let tomod board => switch board {
  | Circle => (module Circle: SimpleBoard.T)
  | HexBox => (module HexBox)
  | Hexagon => (module HexHex)
  | Triangle => (module TriangleBoard)
  | HexTriangle => (module NewHexTriangle)
  | Rect => (module NewRect)
  };

  let name board => switch board {
  | Circle => "Circle"
  | HexBox => "HexBox"
  | Hexagon => "Hexagon"
  | Triangle => "Triangle"
  | HexTriangle => "HexTriangle"
  | Rect => "Rect"
  };
};

module Alg = {
  type t =
    | DFS
    | BFS
    | Random;

  let all = [|DFS, BFS, Random|];

  let tomod alg => switch alg {
  | DFS => (module (NewDepth.F (NewDepth.RandomConfig ())): Generator.T)
  | BFS => (module NewBFS)
  | Random => (module Random2)
  };

  let name alg => switch alg {
  | DFS => "DFS"
  | BFS => "BFS"
  | Random => "Random"
  };
};
