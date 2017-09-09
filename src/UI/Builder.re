let se = ReasonReact.stringToElement;

external refToCanvas : Dom.element => Canvas.canvasElement = "%identity";

let refToContext canv =>
  switch (Js.Null.to_opt canv) {
  | Some canv => Some (Canvas.getContext (refToCanvas canv))
  | None => None
  };

let show ctx settings => {
  open Types;
  open Settings.T;
  Random.init settings.seed;
  let options = Settings.to_options settings;
  module Board = (val Board.tomod settings.board);
  module Gen = (val Alg.tomod settings.algorithm);
  module Paint' = Paint.F Board Gen;
  module Show' = Show.F Board Gen;
  let state = Show'.init_state options;
  Show'.loop options ctx state
};

let animate ctx settings onStop => {
  Js.log "animate";
  open Types;
  open Settings.T;
  Random.init settings.seed;
  let options = Settings.to_options settings;
  module Board = (val Board.tomod settings.board);
  module Gen = (val Alg.tomod settings.algorithm);
  module Paint' = Paint.F Board Gen;
  module Show' = Show.F Board Gen;
  let state = Show'.init_state options;
  let r: ref int = Show'.animate ctx settings.batch_size 40 options state onStop;
  r
};

let record settings ctx onDone _ => {
  let capturer = CCapture.init 25 "animation.webm";
  CCapture.start capturer;
  show ctx settings;
  CCapture.capture capturer (Canvas.Ctx.canvas ctx);
  /*let encoder = Whammy.init 25;*/
  open Types;
  open Settings.T;
  Random.init settings.seed;
  let options = Settings.to_options settings;
  module Board = (val Board.tomod settings.board);
  module Gen = (val Alg.tomod settings.algorithm);
  module Paint' = Paint.F Board Gen;
  module Show' = Show.F Board Gen;
  let state = Show'.init_state options;
  let rec step state => {
    let state = Show'.batch state settings.batch_size;
    Show'.show ctx options state;
    CCapture.capture capturer (Canvas.Ctx.canvas ctx);
    Show'.Man.finished state ?
      CCapture.save capturer (fun blob => onDone (CCapture.objUrl blob)) : step state
  };
  step state
};

let now_date: unit => string = [%bs.raw
  {|
  function () {
    return new Date().toLocaleString().replace(/[^\w]/g, '-')
  }
|}
];

module Page = {
  type state = {
    settings: Settings.T.t,
    ctx: option Canvas.ctx,
    animation: option (ref int),
    downloadUrl: option string
  };
  let component = ReasonReact.statefulComponent "Page";
  let updateCtx ref state _ =>
    state.ctx === None ?
      ReasonReact.Update {...state, ctx: refToContext ref} : ReasonReact.NoUpdate;
  let styles =
    Aphrodite.create {"container": {"flex-direction": "row", "align-self": "stretch", "flex": 1}};
  let process_new_settings settings state suppress_equal =>
    ReasonReact.Update {...state, settings, animation: None};
  let update update_settings suppress_equal payload state _ => {
    let settings = update_settings payload state.settings;
    process_new_settings settings state suppress_equal
  };
  let clearAnimation _ state _ => ReasonReact.Update {...state, animation: None};
  let toggle_animating _ state self =>
    switch state.animation {
    | Some id =>
      Window.clearTimeout !id;
      ReasonReact.Update {...state, animation: None}
    | None =>
      switch state.ctx {
      | Some ctx =>
        let id = animate ctx state.settings (self.ReasonReact.update clearAnimation);
        ReasonReact.Update {...state, animation: Some id}
      | None => ReasonReact.NoUpdate
      }
    };
  let listen_for_hash: (string => unit) => unit = [%bs.raw
    {|
    function (fn) {
      window.addEventListener('hashchange', function(evt) {
        var string;
        try {
          string = atob(window.location.hash.slice(1))
        } catch (e) {
          return null
        }
        fn(string)
      })
    }
  |}
  ];
  let set_hash: string => unit = [%bs.raw
    {|
    function (val) {
      window.location.hash = btoa(val)
    }
  |}
  ];
  let get_hash: unit => string = [%bs.raw
    {| function () { try {return atob(window.location.hash.slice(1));}catch (e) {return ''} } |}
  ];
  external now : unit => int = "Date.now" [@@bs.val];
  let throttle fn time => {
    let last = ref None;
    fun v => {
      switch !last {
      | Some t => Js.Global.clearTimeout t
      | None => ()
      };
      last := Some (Js.Global.setTimeout (fun () => fn v) time)
    }
  };
  let update_hash =
    throttle
      (
        fun settings =>
          switch (Settings.to_json settings) {
          | None => ()
          | Some str => set_hash str
          }
      )
      500;
  let make _children => {
    ...component,
    didUpdate: fun ::previousState ::currentState _ => {
      update_hash currentState.settings;
      if (currentState.settings != previousState.settings) {
        switch previousState.animation {
        | Some id => Window.clearTimeout !id
        | _ => ()
        };
        switch currentState.ctx {
        | Some ctx => show ctx currentState.settings
        | None => ()
        }
      }
    },
    didMount: fun state self => {
      listen_for_hash (
        self.update (
          fun str state _ =>
            switch (Settings.from_json str) {
            | None => ReasonReact.NoUpdate
            | Some settings =>
              if (state.settings == settings) {
                ReasonReact.NoUpdate
              } else {
                process_new_settings settings state false
              }
            }
        )
      );
      switch state.ctx {
      | Some ctx =>
        ReasonReact.Update {
          ...state,
          animation: Some (animate ctx state.settings (self.update clearAnimation))
        }
      | None => ReasonReact.NoUpdate
      }
    },
    initialState: fun () => {
      settings:
        switch (Settings.from_json (get_hash ())) {
        | Some settings => settings
        | None => Settings.initial
        },
      animation: None,
      downloadUrl: None,
      ctx: None
    },
    render: fun state self => {
      let updater =
        SettingsPage.{
          update: fun update_settings suppress_equal =>
            self.update (update update_settings suppress_equal)
        };
      <div className=(Aphrodite.css styles "container")>
        <div style=(ReactDOMRe.Style.make flex::"1" ())>
          <canvas
            width=(string_of_int state.settings.Settings.T.canvas_size ^ "px")
            height=(string_of_int state.settings.Settings.T.canvas_size ^ "px")
            className="canvas"
            ref=(self.update updateCtx)
          />
        </div>
        <div>
          <button onClick=(self.update toggle_animating) style=Styles.button>
            (se (state.animation === None ? "Animate" : "Stop"))
          </button>
          <SettingsPage state=state.settings updater />
          <button
            onClick=?(
                       switch state.ctx {
                       | None => None
                       | Some ctx =>
                         Some (
                           record
                             state.settings
                             ctx
                             (
                               self.update (
                                 fun blobUrl state _ =>
                                   ReasonReact.Update {...state, downloadUrl: Some blobUrl}
                               )
                             )
                         )
                       }
                     )
            style=Styles.button>
            (se "Record animation")
          </button>
          (
            switch state.downloadUrl {
            | None => ReasonReact.nullElement
            | Some url =>
              /* TODO make a nice name */
              <a download=("animation-" ^ now_date () ^ ".webm") href=url>
                (se "Download animation")
              </a>
            }
          )
        </div>
      </div>
    }
  };
};

let run () => ReactDOMRe.renderToElementWithId <Page /> "index";
