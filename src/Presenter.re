
module Ctx = Canvas.Ctx;

let hsl h s l => (
  "hsl(" ^ (string_of_int h) ^
  ", " ^ (string_of_int s) ^
  "%, " ^ (string_of_int l) ^
  "%)");

module F (Board: SimpleBoard.T) (Generator: Generator.T) => {

  let draw_wall ctx (xm, ym) wall => {
    switch (wall)  {
      | Border.Line ((x, y), (a, b)) => {
        Canvas.Ctx.line ctx (x +. xm, y +. ym) (a +. xm, b +. ym)
      }
    }
  };

  let draw_walli ctx (xm, ym) i wall => {
    draw_wall ctx (xm, ym) wall;
    switch (wall)  {
      | Border.Line ((x, y), (a, b)) => {
        let cx = (a +. x) *. 0.5 +. xm;
        let cy = (b +. y) *. 0.5 +. ym;
        let txt = string_of_int i;
        Ctx.setFillStyle ctx "black";
        Ctx.fillText ctx txt cx cy;
      }
    }
  };

  let center pts => {
    let tx = ref 0.0;
    let ty = ref 0.0;
    let c = ref 0;
    List.iter (fun (x, y) => {
      tx := !tx +. x;
      ty := !ty +. y;
      c := !c + 1;
    }) pts;
    (!tx /. (float_of_int !c), !ty /. (float_of_int !c))
  };

  let draw_shape ctx (xm, ym) get_color max_age (shape, age) => {
    if (age === 0) {
      Ctx.setFillStyle ctx "white";
    } else {
      let a = 100 - age * 50 / max_age;
      /*Ctx.setFillStyle ctx ("hsl(80, 100%, " ^ (string_of_int a) ^ "%)");*/
      Ctx.setFillStyle ctx (get_color a);
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

  let draw_shapei ctx (xm, ym) get_color max_age i (shape, age) => {
    draw_shape ctx (xm, ym) get_color max_age (shape, age);
    switch shape {
    | Shape.Polyline pts => {
      let (cx, cy) = center pts;
      Ctx.setFillStyle ctx "black";
      Ctx.fillText ctx (string_of_int i) (cx +. xm) (cy +. ym);
    }
    | _ => ()
    }
  };

  let draw_edge ctx (xm, ym) ((x, y), (a, b)) => {
    Ctx.line ctx (x +. xm, y +. ym) (a +. xm, b +. ym)
  };
};
