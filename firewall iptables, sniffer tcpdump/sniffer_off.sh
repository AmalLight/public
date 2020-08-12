#!/bin/bash

pass=`get ovhk`
ip="kaumi@`get ovhip`"

sshpass -p $pass ssh -t $ip 'pkill myxargs'
