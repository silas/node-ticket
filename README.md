# Ticket

Create "unique" 64-bit integers.

## Install

    npm install ticket

## Usage

    var ticket = require('ticket')(1)

    for (var i = 0; i < 1024; i++) {
      console.log(ticket.get())
    }
