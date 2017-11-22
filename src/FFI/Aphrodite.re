type styles;

type style;

[@bs.module "aphrodite"] external css_ : style => string = "css";

[@bs.module "aphrodite"] external csss_ : array(style) => string = "css";

let get: (styles, string) => style = [%bs.raw
  {|
  function (styles, name) {
    return styles[name]
  }
|}
];

let css = (styles, name) => css_(get(styles, name));

let csss = (styles, names) => csss_(Array.map(get(styles), names));

type styleSheet;

[@bs.val] [@bs.module "aphrodite"] external styleSheet : styleSheet = "StyleSheet";

[@bs.send] external create_ : (styleSheet, Js.t('a)) => styles = "create";

let create = (v) => create_(styleSheet, v);
/*external create: Js.t 'a => styles = "StyleSheet.create" [@@bs.val][@@bs.module "aphrodite"];*/
