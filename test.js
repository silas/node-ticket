var assert = require('assert')
  , tickets = []

for (var i = 1; i <= 16; i++) {
  tickets[i] = require('./ticket')(i)
}

function check_ok() {
  var data = {}

  for (var i = 0; i < 8192; i++) {
    for (var j = 1; j <= 16; j++) {
      var id = tickets[j].get()

      if (data[id]) {
        throw new Error('Error: ' + id + ': ' + data[id])
      } else {
        data[id] = 1
      }
    }
  }

  return Object.keys(data).length
}

function check_not_ok() {
  var ok = false

  try {
    for (var i = 0; i < 131072; i++) {
      var id = tickets[0].get()
    }
  } catch(e) {
    ok = true
  }

  return ok
}

assert.equal(check_ok(), 131072)
assert.ok(check_not_ok())
