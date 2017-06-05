
module Ctx = Canvas.Ctx;

module F (Board: SimpleBoard.T) (Generator: Generator.T) => {

  let draw_wall ctx wall => {
    switch (wall)  {
      | Border.Line (p1, p2) => {
        Canvas.Ctx.line ctx p1 p2
      }
    }
  };

  let draw_shape ctx max_age (shape, age) => {
    if (age === 0) {
      Ctx.setFillStyle ctx "white";
    } else {
      let a = 100 - age * 100 / max_age;
      Ctx.setFillStyle ctx ("hsl(0, 100%, " ^ (string_of_int a) ^ "%)");
    };

    switch shape {
    | Shape.Polyline pts => {
      switch pts {
      | [] => ()
      | [(x, y), ...rest] => {
        Ctx.beginPath ctx;
        Ctx.moveTo ctx x y;
        List.iter
        (fun (x, y) => Ctx.lineTo ctx x y)
        rest;
        Ctx.fill ctx;
      }
      }
    }
    | Shape.Rect (x, y, w, h) => {
      Ctx.fillRect ctx x y w h;
    }
    | Shape.Circle ((x, y), r) => {
      Ctx.circle ctx x y r;
    }
    }
  };

  let draw_edge ctx (p1, p2) => {
    Ctx.line ctx p1 p2
  };
};
