const bindings = require('bindings');

const { listWindows } = bindings('listOpenWindows');

module.exports.listOpenWindows = listWindows;
