
module Ctx = Canvas.Ctx;

module F (Board: SimpleBoard.T) (Generator: Generator.T) => {

  let draw_wall ctx (xm, ym) wall => {
    switch (wall)  {
      | Border.Line ((x, y), (a, b)) => {
        Canvas.Ctx.line ctx (x +. xm, y +. ym) (a +. xm, b +. ym)
      }
    }
  };

  let draw_shape ctx (xm, ym) max_age (shape, age) => {
    if (age === 0) {
      Ctx.setFillStyle ctx "white";
    } else {
      let a = 100 - age * 50 / max_age;
      Ctx.setFillStyle ctx ("hsl(80, 100%, " ^ (string_of_int a) ^ "%)");
    };

    switch shape {
    | Shape.Polyline pts => {
      switch pts {
      | [] => ()
      | [(x, y), ...rest] => {
        Ctx.beginPath ctx;
        Ctx.moveTo ctx (x +. xm) (y +. ym);
        List.iter
        (fun (x, y) => Ctx.lineTo ctx (x +. xm) (y +. ym))
        rest;
        Ctx.fill ctx;
      }
      }
    }
    | Shape.Rect (x, y, w, h) => {
      Ctx.fillRect ctx (x +. xm) (y +. ym) w h;
    }
    | Shape.Circle ((x, y), r) => {
      Ctx.circle ctx (x +. xm) (y +. ym) r;
    }
    }
  };

  let draw_edge ctx (xm, ym) ((x, y), (a, b)) => {
    Ctx.line ctx (x +. xm, y +. ym) (a +. xm, b +. ym)
  };
};
