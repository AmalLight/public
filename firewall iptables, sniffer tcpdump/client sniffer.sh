#!/bin/bash

pass=`get ovhk`
devi=`get ovhdev`

sudo apt-get install curl

iphome=`curl ifconfig.me`
ipserv=`get ovhip`

name=PyServer

cmd="cd $name/sniffer; ./sniffer.sh $pass $devi $ipserv $iphome"

sshpass -p $pass ssh -t $ipserv $cmd
