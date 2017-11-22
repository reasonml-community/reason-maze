type canvas;

[@bs.new] [@bs.module] external canvas : (int, int) => canvas = "canvas";

[@bs.send] external getContext : (canvas, string) => Canvas.ctx = "";

type pngBuffer;

[@bs.send] external toBuffer : canvas => pngBuffer = "";

[@bs.module "fs"] external saveAs : (string, pngBuffer) => unit = "writeFileSync";
