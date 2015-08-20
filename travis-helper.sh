#!/usr/bin/expect
#I hope this works!!!!!!
set timeout 20

spawn /home/travis/.nvm/v0.10.36/bin/particle cloud login
expect "? Please enter your email address: "
send $EMAIL

expect "? Please enter your password: "
send $PASS

spawn /home/travis/.nvm/v0.10.36/bin/particle compile photon firmware/
