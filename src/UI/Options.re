
let se = ReasonReact.stringToElement;
let si = string_of_int;

let component = ReasonReact.statelessComponent "Buttons";

let styles = Aphrodite.create {
  "container": {
    "display": "flex",
    "align-items": "stretch",
    "border": "1px solid #aaa",
    "margin": 5,
    "align-self": "stretch",
  }
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
          (fun option => 
          <SelectableButton
            key=(get_title option)
            title=(get_title option)
            onClick=(fun () => on_change option)
            selected=(current === option)
          />
          /*
          <button
            key=(get_title option)
            onClick=(fun _ => on_change option)
            className=(className (current === option))
          >
            (se (get_title option))
          </button>
          */
          )
          options
        ))
      </div>
  }
};
