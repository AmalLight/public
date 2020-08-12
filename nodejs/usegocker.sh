#!/bin/bash

export PATH=/usr/local/node/bin/:$PATH

echo ''
echo `get unibop`
echo ''
echo 'restart site181981'
echo ''

sshpass -p `get unibop` ssh mohammad.fumagalli@filindo.cs.unibo.it -t "cd /home/web/site181981/html/; ssh gocker.cs.unibo.it"