module Board = {
  type t =
    | Circle
    | HexBox
    | Hexagon
    | Triangle
    | HexTriangle
    | SquareTriangle
    | FourSquare
    | Rect;

  let all = [|
    Circle,
    HexBox,
    Hexagon,
    Triangle,
    HexTriangle,
    Rect,
    SquareTriangle,
    FourSquare,
  |];

  let tomod = board =>
    switch (board) {
    | Circle => ((module Circle): (module SimpleBoard.T))
    | HexBox => (module HexBox)
    | Hexagon => (module HexHex)
    | Triangle => (module TriangleBoard)
    | HexTriangle => (module NewHexTriangle)
    | Rect => (module NewRect)
    | FourSquare => (module FourSquare)
    | SquareTriangle => (module SquareTriangle)
    };

  let name = board =>
    switch (board) {
    | Circle => "Circle"
    | HexBox => "HexBox"
    | Hexagon => "Hexagon"
    | Triangle => "Triangle"
    | HexTriangle => "HexTriangle"
    | SquareTriangle => "SquareTriangle"
    | FourSquare => "FourSquare"
    | Rect => "Rect"
    };

  let by_name = name =>
    switch (name) {
    | "Circle" => Some(Circle)
    | "HexBox" => Some(HexBox)
    | "Hexagon" => Some(Hexagon)
    | "Triangle" => Some(Triangle)
    | "HexTriangle" => Some(HexTriangle)
    | "SquareTriangle" => Some(SquareTriangle)
    | "FourSquare" => Some(FourSquare)
    | "Rect" => Some(Rect)
    | _ => None
    };
};

module Alg = {
  type t =
    | DFS
    | BFS
    | Random;

  let all = [|DFS, BFS, Random|];

  let tomod = alg =>
    switch (alg) {
    | DFS => (
        (module
         NewDepth.F(
           (
             NewDepth.RandomConfig({})
           ),
         )): (module Generator.T)
      )
    | BFS => (module NewBFS)
    | Random => (module Random2)
    };

  let name = alg =>
    switch (alg) {
    | DFS => "DFS"
    | BFS => "BFS"
    | Random => "Random"
    };

  let by_name = name =>
    switch (name) {
    | "DFS" => Some(DFS)
    | "BFS" => Some(BFS)
    | "Random" => Some(Random)
    | _ => None
    };
};
