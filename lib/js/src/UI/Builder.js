'use strict';

var Show = require("../Maze/Show.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Paint = require("../Maze/Paint.js");
var Types = require("./Types.js");
var React = require("react");
var Random = require("bs-platform/lib/js/random.js");
var Styles = require("./Styles.js");
var CCapture = require("../FFI/CCapture.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Settings = require("./Settings.js");
var Aphrodite = require("../FFI/Aphrodite.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReactDOMRe = require("reason-react/lib/js/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");
var SettingsPage = require("./SettingsPage.js");

function se(prim) {
  return prim;
}

function refToContext(canv) {
  if (canv == null) {
    return /* None */0;
  } else {
    return /* Some */[canv.getContext("2d")];
  }
}

function show(ctx, settings) {
  Random.init(settings[/* seed */8]);
  var options = Settings.to_options(settings);
  var Board = Types.Board[/* tomod */1](settings[/* board */0]);
  var Gen = Types.Alg[/* tomod */1](settings[/* algorithm */1]);
  Paint.F(Board)(Gen);
  var Show$prime = Show.F(Board)(Gen);
  var state = Curry._1(Show$prime[/* init_state */6], options);
  return Curry._3(Show$prime[/* loop */8], options, ctx, state);
}

function animate(ctx, settings, onStop) {
  console.log("animate");
  Random.init(settings[/* seed */8]);
  var options = Settings.to_options(settings);
  var Board = Types.Board[/* tomod */1](settings[/* board */0]);
  var Gen = Types.Alg[/* tomod */1](settings[/* algorithm */1]);
  Paint.F(Board)(Gen);
  var Show$prime = Show.F(Board)(Gen);
  var state = Curry._1(Show$prime[/* init_state */6], options);
  return Curry._6(Show$prime[/* animate */5], ctx, settings[/* batch_size */5], 40, options, state, onStop);
}

function record(settings, ctx, onDone) {
  var capturer = Curry._2(CCapture.init, 25, "animation.webm");
  capturer.start();
  show(ctx, settings);
  capturer.capture(ctx.canvas);
  Random.init(settings[/* seed */8]);
  var options = Settings.to_options(settings);
  var Board = Types.Board[/* tomod */1](settings[/* board */0]);
  var Gen = Types.Alg[/* tomod */1](settings[/* algorithm */1]);
  Paint.F(Board)(Gen);
  var Show$prime = Show.F(Board)(Gen);
  var state = Curry._1(Show$prime[/* init_state */6], options);
  var _state = state;
  while(true) {
    var state$1 = _state;
    var state$2 = Curry._2(Show$prime[/* batch */4], state$1, settings[/* batch_size */5]);
    Curry._3(Show$prime[/* show */2], ctx, options, state$2);
    capturer.capture(ctx.canvas);
    var match = Curry._1(Show$prime[/* Man */0][/* finished */6], state$2);
    if (match !== 0) {
      capturer.save((function (blob) {
              return Curry._1(onDone, window.URL.createObjectURL(blob));
            }));
      return /* () */0;
    } else {
      _state = state$2;
      continue ;
      
    }
  };
}

var now_date = (
  function () {
    return new Date().toLocaleString().replace(/[^\w]/g, '-')
  }
);

var component = ReasonReact.reducerComponent("Page");

function setCtxRef(r, param) {
  param[/* state */2][/* ctx */3][0] = refToContext(r);
  return /* () */0;
}

var styles = Aphrodite.create({
      container: {
        "flex-direction": "row",
        "align-self": "stretch",
        flex: 1
      }
    });

function process_new_settings(settings, state) {
  return /* Update */Block.__(0, [/* record */[
              /* settings */settings,
              /* animation : None */0,
              /* downloadUrl */state[/* downloadUrl */2],
              /* ctx */state[/* ctx */3]
            ]]);
}

function update(update_settings, payload, param) {
  var state = param[/* state */2];
  var settings = Curry._2(update_settings, payload, state[/* settings */0]);
  return process_new_settings(settings, state);
}

var listen_for_hash = (
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
  );

var set_hash = (
    function (val) {
      window.location.hash = btoa(val)
    }
  );

var get_hash = ( function () { try {return atob(window.location.hash.slice(1));}catch (e) {return ''} } );

function throttle(fn, time) {
  var last = [/* None */0];
  return (function (v) {
      var match = last[0];
      if (match) {
        clearTimeout(match[0]);
      }
      last[0] = /* Some */[setTimeout((function () {
                return Curry._1(fn, v);
              }), time)];
      return /* () */0;
    });
}

var update_hash = throttle((function (settings) {
        var match = Settings.to_json(settings);
        if (match) {
          return Curry._1(set_hash, match[0]);
        } else {
          return /* () */0;
        }
      }), 500);

function make() {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function (self) {
      var state = self[/* state */2];
      Curry._1(listen_for_hash, Curry._1(self[/* reduce */1], (function (str) {
                  return /* HashChange */Block.__(1, [str]);
                })));
      var match = state[/* ctx */3][0];
      if (match) {
        var ctx = match[0];
        Curry._2(self[/* reduce */1], (function () {
                return /* DidMount */Block.__(2, [/* Some */[animate(ctx, state[/* settings */0], Curry._1(self[/* reduce */1], (function () {
                                        return /* ClearAnimation */0;
                                      })))]]);
              }), /* () */0);
      }
      return /* NoUpdate */0;
    });
  newrecord[/* didUpdate */5] = (function (param) {
      var newSelf = param[/* newSelf */1];
      var oldSelf = param[/* oldSelf */0];
      Curry._1(update_hash, newSelf[/* state */2][/* settings */0]);
      if (Caml_obj.caml_notequal(newSelf[/* state */2][/* settings */0], oldSelf[/* state */2][/* settings */0])) {
        var match = oldSelf[/* state */2][/* animation */1];
        if (match) {
          clearTimeout(match[0][0]);
        }
        var match$1 = newSelf[/* state */2][/* ctx */3][0];
        if (match$1) {
          return show(match$1[0], newSelf[/* state */2][/* settings */0]);
        } else {
          return /* () */0;
        }
      } else {
        return 0;
      }
    });
  newrecord[/* render */9] = (function (self) {
      var state = self[/* state */2];
      var match = +(state[/* animation */1] === /* None */0);
      var match$1 = state[/* downloadUrl */2];
      return React.createElement("div", {
                  className: Aphrodite.css(styles, "container")
                }, React.createElement("div", {
                      style: {
                        flex: "1"
                      }
                    }, React.createElement("canvas", {
                          ref: Curry._1(self[/* handle */0], setCtxRef),
                          className: "canvas",
                          height: Pervasives.string_of_int(state[/* settings */0][/* canvas_size */7]) + "px",
                          width: Pervasives.string_of_int(state[/* settings */0][/* canvas_size */7]) + "px"
                        })), React.createElement("div", undefined, React.createElement("button", {
                          style: Styles.button,
                          onClick: Curry._1(self[/* reduce */1], (function () {
                                  return /* ToggleAnimating */1;
                                }))
                        }, match !== 0 ? "Animate" : "Stop"), ReasonReact.element(/* None */0, /* None */0, SettingsPage.make(state[/* settings */0], Curry._1(self[/* reduce */1], (function (settings) {
                                    return /* SettingsUpdate */Block.__(4, [settings]);
                                  })), /* array */[])), React.createElement("button", {
                          style: Styles.button,
                          onClick: Curry._1(self[/* reduce */1], (function () {
                                  return /* Click */2;
                                }))
                        }, "Record animation"), match$1 ? React.createElement("a", {
                            download: "animation-" + (Curry._1(now_date, /* () */0) + ".webm"),
                            href: match$1[0]
                          }, "Download animation") : null));
    });
  newrecord[/* initialState */10] = (function () {
      var match = Settings.from_json(Curry._1(get_hash, /* () */0));
      return /* record */[
              /* settings */match ? match[0] : Settings.initial,
              /* animation : None */0,
              /* downloadUrl : None */0,
              /* ctx */[/* None */0]
            ];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      var exit = 0;
      if (typeof action === "number") {
        switch (action) {
          case 0 : 
              return /* Update */Block.__(0, [/* record */[
                          /* settings */state[/* settings */0],
                          /* animation : None */0,
                          /* downloadUrl */state[/* downloadUrl */2],
                          /* ctx */state[/* ctx */3]
                        ]]);
          case 1 : 
              var match = state[/* animation */1];
              if (match) {
                var id = match[0];
                return /* UpdateWithSideEffects */Block.__(3, [
                          /* record */[
                            /* settings */state[/* settings */0],
                            /* animation : None */0,
                            /* downloadUrl */state[/* downloadUrl */2],
                            /* ctx */state[/* ctx */3]
                          ],
                          (function () {
                              clearTimeout(id[0]);
                              return /* () */0;
                            })
                        ]);
              } else {
                var match$1 = state[/* ctx */3][0];
                if (match$1) {
                  var ctx = match$1[0];
                  return /* SideEffects */Block.__(2, [(function (self) {
                                var id = animate(ctx, state[/* settings */0], Curry._1(self[/* reduce */1], (function () {
                                            return /* ClearAnimation */0;
                                          })));
                                return Curry._2(self[/* reduce */1], (function () {
                                              return /* SetAnimating */Block.__(5, [/* Some */[id]]);
                                            }), /* () */0);
                              })]);
                } else {
                  return /* NoUpdate */0;
                }
              }
              break;
          case 2 : 
              var match$2 = state[/* ctx */3][0];
              if (match$2) {
                var ctx$1 = match$2[0];
                return /* SideEffects */Block.__(2, [(function (self) {
                              return record(state[/* settings */0], ctx$1, Curry._1(self[/* reduce */1], (function (blobUrl) {
                                                return /* SaveBlob */Block.__(3, [blobUrl]);
                                              })));
                            })]);
              } else {
                return /* NoUpdate */0;
              }
              break;
          case 3 : 
              return /* NoUpdate */0;
          
        }
      } else {
        switch (action.tag | 0) {
          case 0 : 
              return /* Update */Block.__(0, [/* record */[
                          /* settings */action[0],
                          /* animation : None */0,
                          /* downloadUrl */state[/* downloadUrl */2],
                          /* ctx */state[/* ctx */3]
                        ]]);
          case 1 : 
              var match$3 = Settings.from_json(action[0]);
              if (match$3) {
                var settings = match$3[0];
                if (Caml_obj.caml_equal(state[/* settings */0], settings)) {
                  return /* NoUpdate */0;
                } else {
                  return /* Update */Block.__(0, [/* record */[
                              /* settings */settings,
                              /* animation : None */0,
                              /* downloadUrl */state[/* downloadUrl */2],
                              /* ctx */state[/* ctx */3]
                            ]]);
                }
              } else {
                return /* NoUpdate */0;
              }
              break;
          case 3 : 
              return /* Update */Block.__(0, [/* record */[
                          /* settings */state[/* settings */0],
                          /* animation */state[/* animation */1],
                          /* downloadUrl : Some */[action[0]],
                          /* ctx */state[/* ctx */3]
                        ]]);
          case 4 : 
              return /* Update */Block.__(0, [/* record */[
                          /* settings */action[0],
                          /* animation */state[/* animation */1],
                          /* downloadUrl */state[/* downloadUrl */2],
                          /* ctx */state[/* ctx */3]
                        ]]);
          case 2 : 
          case 5 : 
              exit = 1;
              break;
          
        }
      }
      if (exit === 1) {
        return /* Update */Block.__(0, [/* record */[
                    /* settings */state[/* settings */0],
                    /* animation */action[0],
                    /* downloadUrl */state[/* downloadUrl */2],
                    /* ctx */state[/* ctx */3]
                  ]]);
      }
      
    });
  return newrecord;
}

var Page = /* module */[
  /* component */component,
  /* setCtxRef */setCtxRef,
  /* styles */styles,
  /* process_new_settings */process_new_settings,
  /* update */update,
  /* listen_for_hash */listen_for_hash,
  /* set_hash */set_hash,
  /* get_hash */get_hash,
  /* throttle */throttle,
  /* update_hash */update_hash,
  /* make */make
];

function run() {
  return ReactDOMRe.renderToElementWithId(ReasonReact.element(/* None */0, /* None */0, make(/* array */[])), "index");
}

exports.se = se;
exports.refToContext = refToContext;
exports.show = show;
exports.animate = animate;
exports.record = record;
exports.now_date = now_date;
exports.Page = Page;
exports.run = run;
/* now_date Not a pure module */
