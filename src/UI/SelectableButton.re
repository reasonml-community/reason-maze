
let se = ReasonReact.stringToElement;
let si = string_of_int;

let component = ReasonReact.statelessComponent "SelectableButton";

let styles = Aphrodite.create {
  "button": {
    "background-color": "white",
    "border": "none",
    "padding": "10px 20px",
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

let make ::title ::selected ::onClick _children => {
  {
    ...component,
    render: fun () _self =>
      <button
        onClick=(fun _ => onClick ())
        className=(className selected)
      >
        (se title)
      </button>
  }
};
