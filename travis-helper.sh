#!/usr/bin/expect
#I hope this works!!!!
set timeout 20

spawn "$(which particle) cloud login"
expect "? Please enter your email address: "
send ${EMAIL}

expect "? Please enter your password: "
send ${PASS}

spawn "$(which particle) compile photon firmware/"
