#!/usr/bin/expect

set timeout 10

set user [lindex $argv 0]

set password [lindex $argv 1]

spawn /home/travis/.nvm/v0.10.36/bin/particle cloud login
expect "? Please enter your email address: "
send "$user\r"

expect "? Please enter your password: "
send "$password\r"

interact
