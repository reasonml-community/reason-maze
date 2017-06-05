
module F (Board: SimpleBoard.T) (Generator: Generator.T) => {

  let draw_wall ctx wall => {
    switch (wall)  {
      | Border.Line (p1, p2) => {
        Canvas.Ctx.line ctx p1 p2
      }
    }
  };

  let draw_edge ctx (p1, p2) => {
    Canvas.Ctx.line ctx p1 p2
  };
};
