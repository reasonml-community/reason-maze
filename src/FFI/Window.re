type window;

let window: window = [%bs.raw "window"];

external setTimeout : (unit => unit) => int => int = "" [@@bs.val];

external clearTimeout : int => unit = "" [@@bs.val];

external requestAnimationFrame : (float => unit) => int = "" [@@bs.val];

external cancelAnimationFrame : int => unit = "" [@@bs.val];

external windowToJsObj : window => Js.t {..} = "%identity";
