
type canvas;
external canvas: int => int => canvas = "canvas" [@@bs.new][@@bs.module];
external getContext: canvas => string => Canvas.ctx = "" [@@bs.send];
type pngBuffer;
external toBuffer: canvas => pngBuffer = "" [@@bs.send];
external saveAs: string => pngBuffer => unit = "writeFileSync" [@@bs.module "fs"];