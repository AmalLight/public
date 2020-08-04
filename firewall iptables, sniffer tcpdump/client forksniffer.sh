#!/bin/bash

pass=`get ovhk`
devi=`get ovhdev`

oftime="$1"

sudo apt-get install curl
iphome=`curl ifconfig.me`
ipserv=`get ovhip`

name=PyServer

cmd="cd $name/sniffer; ./forksniffer.sh $pass $devi $ipserv $iphome $oftime"

sshpass -p $pass ssh -t $ipserv $cmd
sshpass -p $pass scp    $ipserv:$name/sniffer/nohup.out ./
