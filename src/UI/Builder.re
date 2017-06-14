
let se = ReasonReact.stringToElement;

external refToCanvas: Dom.element => Canvas.canvasElement = "%identity";

let show ctx settings => {
  open Types;
  open Settings.T;

  let canvas_size = (1000.0, 1000.0);
  let options = RandomMaze.random_options canvas_size;

  let module Board = (val (Board.tomod settings.board));
  let module Gen = (val (Alg.tomod settings.algorithm));
  let module Paint' = Paint.F Board Gen;

  let module Show' = Show.F Board Gen;

  let state = Show'.init_state options;

  Show'.loop options ctx state;
};

let refToContext canv => {
  switch (Js.Null.to_opt canv) {
  | Some canv => Some (Canvas.getContext (refToCanvas canv))
  | None => None
  }
};

module Page = {
  type state = {
    settings: Settings.T.t,
    ctx: option Canvas.ctx,
  };
  let component = ReasonReact.statefulComponent "Page";

  let updateCtx ref state _ => ReasonReact.SilentUpdate {...state, ctx: refToContext ref};

  let styles = Aphrodite.create {
    "container": {
      "flex-direction": "row"
    }
  };

  let make _children => {
    ...component,
    initialState: fun () => {
      settings: Settings.initial,
      ctx: None,
    },
    render: fun state self => {
      let updater = Settings.{
        update: fun f => self.update (fun x state _ => {
          let settings = f x state.settings;
          switch (state.ctx) {
          | Some ctx => show ctx settings
          | None => ()
          };
          ReasonReact.Update {...state, settings}
        })
      };
      <div className=(Aphrodite.css styles "container")>
        <canvas width="1000px" height="1000px" className="canvas" ref=(self.update updateCtx)/>
        <Settings.Settings
          state=state.settings
          updater=updater
        />
      </div>
    },
  };
};

let run () => {
  ReactDOMRe.renderToElementWithId <Page /> "index";
};
