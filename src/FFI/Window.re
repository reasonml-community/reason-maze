type window;

let window: window = [%bs.raw "window"];

[@bs.val] external setTimeout : (unit => unit, int) => int = "";

[@bs.val] external clearTimeout : int => unit = "";

[@bs.val] external requestAnimationFrame : (float => unit) => int = "";

[@bs.val] external cancelAnimationFrame : int => unit = "";

external windowToJsObj : window => Js.t({..}) = "%identity";
