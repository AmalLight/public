#!/bin/bash

echo *** | sudo -S rm -f /usr/bin/launch
sudo ln -s /home/kaumi/SoSupersonic/scripts/launch.sh /usr/bin/launch

sudo rm -f /usr/bin/ipAction
sudo ln -s /home/kaumi/SoSupersonic/scripts/Back/scripts/ipAction.sh /usr/bin/ipAction

echo ''

ipAction filter
ipAction nat

ipAction f v m t c 192.168.56.1 d i 8080 1 2 3 ACCEPT
ipAction f v m t c 192.168.56.1 d i 22 1 2 3 ACCEPT

ipAction f v m filter INPUT s d i 8080 1 2 3 DROP
ipAction f v m filter INPUT s d i 22 1 2 3 DROP

ipAction f filter

cd /home/kaumi/SoSupersonic/server/

if [[ ! -f tsconfig.json ]]; then tsc --init ; fi ;

/usr/bin/code /home/kaumi/SoSupersonic/server &

echo ''
read -sp 'press enter for finish'
echo ''
echo ''
