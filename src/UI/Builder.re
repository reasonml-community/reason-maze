let se = ReasonReact.stringToElement;

external refToCanvas : Dom.element => Canvas.canvasElement = "%identity";

let refToContext = canv =>
  switch (Js.Nullable.toOption(canv)) {
  | Some(canv) => Some(Canvas.getContext(refToCanvas(canv)))
  | None => None
  };

let show = (ctx, settings) => {
  open Types;
  open Settings.T;
  Random.init(settings.seed);
  let options = Settings.to_options(settings);
  module Board = (val Board.tomod(settings.board));
  module Gen = (val Alg.tomod(settings.algorithm));
  module Paint' = Paint.F(Board, Gen);
  module Show' = Show.F(Board, Gen);
  let state = Show'.init_state(options);
  Show'.loop(options, ctx, state);
};

let animate = (ctx, settings, onStop) => {
  Js.log("animate");
  open Types;
  open Settings.T;
  Random.init(settings.seed);
  let options = Settings.to_options(settings);
  module Board = (val Board.tomod(settings.board));
  module Gen = (val Alg.tomod(settings.algorithm));
  module Paint' = Paint.F(Board, Gen);
  module Show' = Show.F(Board, Gen);
  let state = Show'.init_state(options);
  let r: ref(int) =
    Show'.animate(ctx, settings.batch_size, 40, options, state, onStop);
  r;
};

let record = (settings, ctx, onDone) => {
  let capturer = CCapture.init(25, "animation.webm");
  CCapture.start(capturer);
  show(ctx, settings);
  CCapture.capture(capturer, Canvas.Ctx.canvas(ctx));
  /*let encoder = Whammy.init 25;*/
  open Types;
  open Settings.T;
  Random.init(settings.seed);
  let options = Settings.to_options(settings);
  module Board = (val Board.tomod(settings.board));
  module Gen = (val Alg.tomod(settings.algorithm));
  module Paint' = Paint.F(Board, Gen);
  module Show' = Show.F(Board, Gen);
  let state = Show'.init_state(options);
  let rec step = state => {
    let state = Show'.batch(state, settings.batch_size);
    Show'.show(ctx, options, state);
    CCapture.capture(capturer, Canvas.Ctx.canvas(ctx));
    Show'.Man.finished(state) ?
      CCapture.save(capturer, blob => onDone(CCapture.objUrl(blob))) :
      step(state);
  };
  step(state);
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
    animation: option(ref(int)),
    downloadUrl: option(string),
    ctx: ref(option(Canvas.ctx)),
  };

  type action =
    | ClearAnimation
    | ToggleAnimating
    | ProcessNewSettings(Settings.T.t)
    | HashChange(string)
    | DidMount(option(ref(int)))
    | SaveBlob(string)
    | SettingsUpdate(Settings.T.t)
    /*| UpdateSomething (int => Settings.T.t => Settings.T.t)*/
    | SetAnimating(option(ref(int)))
    | Click
    | Noop;

  let component = ReasonReact.reducerComponent("Page");

  let setCtxRef = (r, {ReasonReact.state}) => state.ctx := refToContext(r);

  let styles =
    Aphrodite.create({
      "container": {
        "flex-direction": "row",
        "align-self": "stretch",
        "flex": 1,
      },
    });

  let process_new_settings = (settings, state) =>
    ReasonReact.Update({...state, settings, animation: None});

  let update = (update_settings, payload, {ReasonReact.state}) => {
    let settings = update_settings(payload, state.settings);
    process_new_settings(settings, state);
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

  let throttle = (fn, time) => {
    let last = ref(None);
    v => {
      switch (last^) {
      | Some(t) => Js.Global.clearTimeout(t)
      | None => ()
      };
      last := Some(Js.Global.setTimeout(() => fn(v), time));
    };
  };

  let update_hash =
    throttle(
      settings =>
        switch (Settings.to_json(settings)) {
        | None => ()
        | Some(str) => set_hash(str)
        },
      500,
    );

  let make = _children => {
    ...component,
    initialState: () => {
      settings:
        switch (Settings.from_json(get_hash())) {
        | Some(settings) => settings
        | None => Settings.initial
        },
      animation: None,
      downloadUrl: None,
      ctx: ref(None),
    },
    reducer: (action, state) =>
      switch (action) {
      | ClearAnimation => ReasonReact.Update({...state, animation: None})
      | Noop => ReasonReact.NoUpdate
      | ToggleAnimating =>
        switch (state.animation) {
        | Some(id) =>
          ReasonReact.UpdateWithSideEffects(
            {...state, animation: None},
            (_self => Window.clearTimeout(id^)),
          )
        | None =>
          switch (state.ctx^) {
          | Some(ctx) =>
            ReasonReact.SideEffects(
              (
                self => {
                  let id =
                    animate(
                      ctx,
                      state.settings,
                      self.reduce(_ => ClearAnimation),
                    );
                  self.reduce(() => SetAnimating(Some(id)), ());
                }
              ),
            )
          | None => ReasonReact.NoUpdate
          }
        }
      | SetAnimating(id) => ReasonReact.Update({...state, animation: id})
      | ProcessNewSettings(settings) =>
        ReasonReact.Update({...state, settings, animation: None})
      | DidMount(animation) => ReasonReact.Update({...state, animation})
      | Click =>
        switch (state.ctx^) {
        | None => ReasonReact.NoUpdate
        | Some(ctx) =>
          ReasonReact.SideEffects(
            (
              self =>
                record(
                  state.settings,
                  ctx,
                  self.reduce(blobUrl => SaveBlob(blobUrl)),
                )
            ),
          )
        }
      | SettingsUpdate(settings) => ReasonReact.Update({...state, settings})
      | SaveBlob(blobUrl) =>
        ReasonReact.Update({...state, downloadUrl: Some(blobUrl)}) /*      | UpdateSomething update_settings =>
        let settings = update_settings payload state.settings;
        ReasonReact.Update {...state, settings, animation: None}
*/
      | HashChange(str) =>
        switch (Settings.from_json(str)) {
        | None => ReasonReact.NoUpdate
        | Some(settings) =>
          if (state.settings == settings) {
            ReasonReact.NoUpdate;
          } else {
            ReasonReact.Update({...state, settings, animation: None});
          }
        }
      },
    didUpdate: ({oldSelf, newSelf}) => {
      update_hash(newSelf.state.settings);
      if (newSelf.state.settings != oldSelf.state.settings) {
        switch (oldSelf.state.animation) {
        | Some(id) => Window.clearTimeout(id^)
        | _ => ()
        };
        switch (newSelf.state.ctx^) {
        | Some(ctx) => show(ctx, newSelf.state.settings)
        | None => ()
        };
      };
    },
    didMount: ({state} as self) => {
      listen_for_hash(self.reduce(str => HashChange(str)));
      switch (state.ctx^) {
      | Some(ctx) =>
        self.reduce(
          () =>
            DidMount(
              Some(
                animate(
                  ctx,
                  state.settings,
                  self.reduce(_ => ClearAnimation),
                ),
              ),
            ),
          (),
        )
      | None => ()
      };
      ReasonReact.NoUpdate;
    },
    render: ({state, reduce} as self) =>
      /* let updater =
         SettingsPage.{update: fun update_settings => self.update (update update_settings)}; */
      <div className=(Aphrodite.css(styles, "container"))>
        <div style=(ReactDOMRe.Style.make(~flex="1", ()))>
          <canvas
            width=(
              string_of_int(state.settings.Settings.T.canvas_size) ++ "px"
            )
            height=(
              string_of_int(state.settings.Settings.T.canvas_size) ++ "px"
            )
            className="canvas"
            ref=(self.handle(setCtxRef))
          />
        </div>
        <div>
          <button
            onClick=(self.reduce(_ => ToggleAnimating)) style=Styles.button>
            (se(state.animation === None ? "Animate" : "Stop"))
          </button>
          <SettingsPage
            settings=state.settings
            update=(reduce(settings => SettingsUpdate(settings)))
          />
          /*          <SettingsPage
                                  state=state.settings
                                  updater=(self.reduce (fun settings => UpdateSomething settings))
                                />

                      */
          <button onClick=(self.reduce(_ => Click)) style=Styles.button>
            (se("Record animation"))
          </button>
          (
            switch (state.downloadUrl) {
            | None => ReasonReact.nullElement
            | Some(url) =>
              /* TODO make a nice name */
              <a download=("animation-" ++ now_date() ++ ".webm") href=url>
                (se("Download animation"))
              </a>
            }
          )
        </div>
      </div>,
  };
};

let run = () => ReactDOMRe.renderToElementWithId(<Page />, "index");
