let main = () => {
  /*let csize = (1000.0, 1000.0);*/
  let canvas = NodeCanvas.canvas(1000, 1000);
  let ctx = NodeCanvas.getContext(canvas, "2d");
  /*main();*/
  ignore(RandomMaze.run(ctx, (1000.0, 1000.0)));
  NodeCanvas.saveAs("./out.png", NodeCanvas.toBuffer(canvas));
};

main();
