var Ticketer = require('./build/Release/ticket').Ticketer

module.exports = function(id) {
  return new Ticketer(id)
}
