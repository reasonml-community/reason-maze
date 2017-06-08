const path = require('path');

module.exports = {
  entry: './lib/js/src/randomMaze.js',
  output: {
    library: true,
    libraryTarget: 'commonjs2',
    path: path.join(__dirname, "bundledOutputs"),
    filename: 'node.js',
  },
};

