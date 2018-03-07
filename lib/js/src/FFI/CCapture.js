'use strict';


var init = (
  function (framerate, name) {
    return new CCapture({framerate: framerate, name: name, format: 'webm'})
  }
);

exports.init = init;
/* init Not a pure module */
