
module Ctx = Canvas.Ctx;

let hsl h s l => (
  "hsl(" ^ (string_of_int h) ^
  ", " ^ (string_of_int s) ^
  "%, " ^ (string_of_int l) ^
  "%)");

let hslf h s l => (
  "hsl(" ^ (Js.String.make h) ^
  ", " ^ (Js.String.make s) ^
  "%, " ^ (Js.String.make l) ^
  "%)");

module F (Board: SimpleBoard.T) (Generator: Generator.T) => {

  let draw_wall ctx (xm, ym) wall => {
    switch (wall)  {
      | Border.Line ((x, y), (a, b)) => {
        Canvas.Ctx.line ctx (x +. xm, y +. ym) (a +. xm, b +. ym)
      }
      | Border.Arc (x, y, r, t1, t2) => {
        Ctx.beginPath ctx;
        Ctx.arc ctx (x +. xm) (y +. ym) r t1 t2;
        Ctx.stroke ctx;
      }
    }
  };

  let draw_walli ctx (xm, ym) i wall => {
    draw_wall ctx (xm, ym) wall;
    let txt = string_of_int i;
    switch (wall)  {
      | Border.Line ((x, y), (a, b)) => {
        let cx = (a +. x) *. 0.5 +. xm;
        let cy = (b +. y) *. 0.5 +. ym;
        Ctx.setFillStyle ctx "black";
        Ctx.fillText ctx txt cx cy;
      }
      | Border.Arc (x, y, r, t1, t2) => {
        let ct = (t1 +. t2) /. 2.0;
        let dx = r *. cos ct;
        let dy = r *. sin ct;
        Ctx.setFillStyle ctx "black";
        Ctx.fillText ctx txt (x +. dx +. xm) (y +. dy +. ym);
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

  let (||>) (x, y) b => b x y;

  let polar r t => (r *. cos t, r *. sin t);
  let offset (x, y) a b => (x +. a, y +. b);

  let draw_shape ctx (xm, ym) get_color current_age max_age (shape, age) => {
    if (age === 0) {
      Ctx.setFillStyle ctx "white";
    } else {
      let a = 100.0 -. (float_of_int age) *. 50.0 /. (float_of_int max_age);
      /*Ctx.setFillStyle ctx ("hsl(80, 100%, " ^ (string_of_int a) ^ "%)");*/
      Ctx.setFillStyle ctx
        (get_color
          (float_of_int age /. float_of_int current_age)
          (float_of_int age /. float_of_int max_age));
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
    | Shape.Arc ((cx, cy), y1, y2, t1, t2) => {
      Ctx.beginPath ctx;
      (polar y1 t1) ||> offset (cx +. xm, cy +. ym) ||> Ctx.moveTo ctx ;
      Ctx.arc ctx (cx +. xm) (cy +. ym) y1 t1 t2;
      (polar y2 t2) ||> offset (cx +. xm, cy +. ym) ||> Ctx.lineTo ctx ;
      Ctx.arc_rev ctx (cx +. xm) (cy +. ym) y2 t2 t1;
      Ctx.fill ctx;
    }
    }
  };

  let draw_shapei ctx (xm, ym) get_color current_age max_age i (shape, age) => {
    draw_shape ctx (xm, ym) get_color current_age max_age (shape, age);
    Ctx.setFillStyle ctx "black";
    let txt = (string_of_int i);
    switch shape {
    | Shape.Polyline pts => {
      let (cx, cy) = center pts;
      Ctx.fillText ctx txt (cx +. xm) (cy +. ym);
    }
    | Shape.Rect (x, y, w, h) => {
      Ctx.fillText ctx txt (x +. xm +. w /. 2.0) (y +. ym +. h /. 2.0);
    }
    | Shape.Circle ((x, y), r) => {
      Ctx.fillText ctx txt (x +. xm) (y +. ym);
    }
    | Shape.Arc ((cx, cy), y1, y2, t1, t2) => {
      let r = (y1 +. y2) /. 2.0;
      let ct = (t1 +. t2) /. 2.0;
      let dx = r *. cos ct;
      let dy = r *. sin ct;
      Ctx.setFillStyle ctx "black";
      Ctx.fillText ctx txt (cx +. dx +. xm) (cy +. dy +. ym);
    }
    }
  };

  let draw_edge ctx (xm, ym) ((x, y), (a, b)) => {
    Ctx.line ctx (x +. xm, y +. ym) (a +. xm, b +. ym)
  };
};
