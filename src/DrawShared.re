module Ctx = Canvas.Ctx;

let draw_wall ctx wall => {
  switch (wall)  {
    | Shared.Line ((x, y), (a, b)) => {
      Ctx.beginPath ctx;
      Ctx.moveTo ctx x y;
      Ctx.lineTo ctx a b;
      Ctx.stroke ctx;
    }
  }
};

let sf = string_of_float;
let si = string_of_int;
let hsl h s l => "hsl(" ^ (si h) ^ ", " ^ (si s) ^ "%, " ^ (si l) ^ "%)";

let draw_point ctx age (x, y) => {
  Ctx.setFillStyle ctx (hsl 0 100 (100 - age));
  Ctx.beginPath ctx;
  Ctx.circle ctx x y 10.0;
  Ctx.fill ctx;
};

