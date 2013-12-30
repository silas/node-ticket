var assert = require('assert')
  , tickets = []

for (var i = 1; i <= 16; i++) {
  tickets[i] = require('./index')(i)
}

function expectNoCollisions() {
  var data = {}

  for (var i = 0; i < 8192; i++) {
    for (var j = 1; j <= 16; j++) {
      var id = tickets[j].get()

      if (data[id]) {
        throw new Error('Error: ' + id + ': ' + data[id])
      }
      data[id] = 1
    }
  }

  return Object.keys(data).length
}

function expectCollisions() {
  var ok = false

  try {
    for (var i = 0; i < 8192 * 16; i++) {
      var id = tickets[0].get()
    }
  } catch(e) {
    ok = true
  }

  return ok
}

assert.equal(expectNoCollisions(), 8192 * 16)
assert.ok(expectCollisions())
