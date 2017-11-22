type capturer;

type blob;

let init: (int, string) => capturer = [%bs.raw
  {|
  function (framerate, name) {
    return new CCapture({framerate: framerate, name: name, format: 'webm'})
  }
|}
];

[@bs.send] external start : capturer => unit = "";

[@bs.send] external capture : (capturer, Canvas.canvasElement) => unit = "";

[@bs.send] external save : (capturer, blob => unit) => unit = "";

[@bs.val] external objUrl : blob => string = "window.URL.createObjectURL";
