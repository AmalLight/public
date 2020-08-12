#!/bin/bash

pass=`get ovhk`
devi=`get ovhdev`

g++ firewall.c -o myfirewall
chmod 777 myfirewall

./myfirewall $pass $devi
