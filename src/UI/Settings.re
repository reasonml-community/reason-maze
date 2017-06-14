
let se = ReasonReact.stringToElement;

module Buttons = {
  let component = ReasonReact.statelessComponent "Buttons";

  let styles = Aphrodite.create {
    "container": {
      "display": "flex",
      "align-items": "stretch",
      "border": "1px solid #aaa",
      "margin": 5,
      "align-self": "stretch",
    },
    "button": {
      "background-color": "white",
      "border": "none",
      "padding": "10px 20px",
      "flex": 1,
      "cursor": "pointer",
      "outline": "none",
      ":hover": {
        "background-color": "#eee"
      }
    },
    "selected": {
      "background-color": "#aaa"
    },
  };

  let className is_current => Aphrodite.(csss styles [|
    "button",
    is_current ? "selected" : "nonselected"
  |]);

  let make ::options ::get_title ::current ::on_change _children => {
    {
      ...component,
      render: fun () _self =>
        <div className=Aphrodite.(css styles "container")>
          (ReasonReact.arrayToElement (Array.map
            (fun option => <button
              key=(get_title option)
              onClick=(fun _ => on_change option)
              className=(className (current === option))
            >
              (se (get_title option))
            </button>)
            options
          ))
        </div>
    }
  };
};

module T = {
  type t = {
    board: Types.Board.t,
    algorithm: Types.Alg.t,
  }
};

let initial = T.{
  board: Types.Board.Hexagon,
  algorithm: Types.Alg.Random,
};


type updater = {
  update: 'a .('a => T.t => T.t) => ReasonReact.Callback.t 'a
};

module Settings = {
  let component = ReasonReact.statelessComponent "Settings";

  open T;
  open Types;
  let set_board board state => {...state, board};
  let set_alg algorithm state => {...state, algorithm};

  let make ::state ::updater _children => {
    ...component,
    render: fun () self => {
      <div className="settings">
        <Buttons
          get_title=(Board.name)
          options=(Board.all)
          current=(state.board)
          on_change=(updater.update set_board)
        />

        <Buttons
          get_title=(Alg.name)
          options=(Alg.all)
          current=(state.algorithm)
          on_change=(updater.update set_alg)
        />
      </div>
    },
  };
};
