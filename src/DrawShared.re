module Ctx = Canvas.Ctx;

let draw_wall ctx wall => {
  switch (wall)  {
    | Shared.Line (p1, p2) => {
      Ctx.line ctx p1 p2
    }
  }
};

let sf = string_of_float;
let si = string_of_int;
let hsl h s l => "hsl(" ^ (si h) ^ ", " ^ (si s) ^ "%, " ^ (si l) ^ "%)";

let draw_point ctx count age (x, y) => {
  Ctx.setFillStyle ctx (hsl 0 100 (100 * (count - age) / count));
  Ctx.beginPath ctx;
  Ctx.circle ctx x y 15.0;
  Ctx.fill ctx;
};

