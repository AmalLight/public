#!/bin/bash

# https://danielmiessler.com/study/tcpdump/

reset
g++ filter.c -o filterdump
chmod 777 filterdump

g++ xargs.c  -o myxargs
chmod 777 myxargs

pass=$1; interface=$2; ipservr=$3; iphome=$4

ruleip="(net $ipservr) and (not net $iphome)"
proto='(tcp or udp)'

pkill myxargs
echo $pass | sudo -S tcpdump -enNvt -i $interface $ruleip and $proto | ./myxargs './filterdump'