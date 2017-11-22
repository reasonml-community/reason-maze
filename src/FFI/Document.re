type element;

type document;

type keyboardEvent;

[@bs.val] external createElement : string => element = "document.createElement";

[@bs.val] external appendChild : element => element = "document.body.appendChild";

[@bs.send]
external addEventListener : (element, string, unit => unit) => unit = "addEventListener";

[@bs.get] external getWidth : element => int = "innerWidth";

[@bs.get] external getHeight : element => int = "innerHeight";

[@bs.set] external setWidth : (element, int) => unit = "width";

[@bs.set] external setHeight : (element, int) => unit = "height";

[@bs.return null_to_opt] [@bs.send]
external getElementById : (document, string) => option(element) = "";

/*
 external addEventListener :
   document => string => ( => Js.boolean) => Js.boolean => unit =
   "" [@@bs.send];
   */
external keyboardEventToJsObj : keyboardEvent => Js.t({..}) = "%identity";
