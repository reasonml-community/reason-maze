type element;
type document;
type keyboardEvent;

external createElement : string => element = "document.createElement" [@@bs.val];
external appendChild : element => element = "document.body.appendChild" [@@bs.val];
external addEventListener : element => string => (unit => unit) => unit = "addEventListener" [@@bs.send];

external getWidth : element => int = "innerWidth" [@@bs.get];
external getHeight : element => int = "innerHeight" [@@bs.get];

external setWidth : element => int => unit = "width" [@@bs.set];
external setHeight : element => int => unit = "height" [@@bs.set];

external getElementById : document => string => option element =
  "" [@@bs.return null_to_opt] [@@bs.send];

/*
external addEventListener :
  document => string => ( => Js.boolean) => Js.boolean => unit =
  "" [@@bs.send];
  */

external keyboardEventToJsObj : keyboardEvent => Js.t {..} = "%identity";
