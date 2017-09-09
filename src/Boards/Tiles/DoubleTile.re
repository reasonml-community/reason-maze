/*
 // triangle triangle
 type tiles =
   | Up
   | Down;

 // square triangle
 Tile modules == [
   TopLeftSquareHalf,
   BottomRightSquareHalf
 ]

 type tiles =
   | Tile1
   | Tile2

 type direction =
   | Tile1 TopLeftSquareHalf.tile
   | Tile2 BottomRightSquareHalf.tile


 sooo the problem is that I don't know how many tiles I'll have?

 type doubleTile =
   | One
   | Two;

 module type TileWhich = {
   // How to associate w/ the types below
   let whichTile: Coord.t => tile;
 };

 let module TwoTiledTexan (Tile1: Tile) (Tile2: Tile) (Which: TileWhich) => {

   type directions =
     | Tile1 Tile1.direction
     | Tile2 Tile2.direction;

   let adjacents coord => switch (Which.tile coord) {
   | One => Tile1.adjacents coord
   | Two => Tile2.adjacents coord
 };

   let adjacent_coord coord direction => switch (direction) {
   | Tile1 dir => Tile1.adjacent_coord coord dir
   | Tile2 dir => Tile2.adjacent_coord coord dir
   };

   let direction_to_border coord direction => switch direction {
   | Tile1 dir => Tile1.direction_to_border coord dir
   | Tile2 dir => Tile2.direction_to_border coord dir
   };

   let to_shape coord => switch (Which.tile coord) {
   | One => Tile1.to_shape coord
   | Two => Tile2.to_shape coord
   };

 }




















 module type Tiled = {
   module Coord: Coord.T;
   type tile;
   let adjacents: Coord.t =>
   /*type direction = ()*/
 };
 */
