#!/usr/bin/expect
#I hope this works!!!
set timeout 20

spawn "$PARTICLE cloud login"
expect "? Please enter your email address: "
send $EMAIL

expect "? Please enter your password: "
send $PASS

spawn "/usr/bin/particle compile photon firmware/"
