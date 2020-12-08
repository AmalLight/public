#!/bin/bash

echo *** | sudo -S rm -f /usr/bin/back
sudo ln -s /home/kaumi/SoSupersonic/scripts/back.sh /usr/bin/back

rm  -rf /home/kaumi/SoSupersonic/scripts/Back

echo ''
read -sp 'password: ' pass

echo ''
echo 'CP BACK START'
echo ''

sshpass -p $pass scp -r 192.168.56.1:/home/kaumi/Back /home/kaumi/SoSupersonic/scripts/

echo ''
echo 'CP BACK DONE'
echo ''

sshpass -p $pass ssh -t 192.168.56.1 'rm -rf /home/kaumi/SoSupersonic'

echo ''
echo 'CP THIS START'
echo ''

sshpass -p $pass scp -r /home/kaumi/SoSupersonic 192.168.56.1:/home/kaumi/

echo ''
echo 'CP THIS DONE'
echo ''
