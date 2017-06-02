const path = require('path');

module.exports = {
  entry: './lib/js/src/main.js',
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: '[name].js',
  },
};
