#!/usr/bin/expect
#I hope this works!!!!!!
set timeout 20

spawn "particle cloud login"
expect "? Please enter your email address: "
send ${EMAIL}

expect "? Please enter your password: "
send ${PASS}

spawn "particle compile photon firmware/"
