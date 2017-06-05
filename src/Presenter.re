
module F (Board: SimpleBoard.T) (Generator: Generator.T) => {

  let draw_wall ctx wall => {
    switch (wall)  {
      | Border.Line (p1, p2) => {
        Canvas.Ctx.line ctx p1 p2
      }
    }
  };

  let draw_walls ctx canvas_size walls => {
    List.iter (draw_wall ctx) walls;
  };

  /*
  let outer_borders state => {
    open Manager.State;
    let x = Board.coordinates state.shape;
    let nstate = Generator.step state.gen_state;
  };
  */
};
