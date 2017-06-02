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

