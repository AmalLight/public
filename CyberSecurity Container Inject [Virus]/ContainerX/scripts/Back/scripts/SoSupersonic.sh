#!/bin/bash

echo ''
echo 'START and CONNECT'
echo ''

pass=***

echo $pass | sudo -S sysctl net.ipv4.conf.all.forwarding=1
sudo sysctl -a | grep ipv4 | grep forwarding | grep 1

sudo rm -f /usr/bin/SoSupersonic
sudo ln -s /home/kaumi/Back/scripts/SoSupersonic.sh /usr/bin/SoSupersonic

sudo rm -f /usr/bin/ipAction
sudo ln -s /home/kaumi/Back/scripts/ipAction.sh /usr/bin/ipAction

cono=/home/kaumi/Back/scripts/cono.sh

echo ''
echo 'FLUSH'
echo ''

ipAction nat
ipAction filter

echo ''
echo 'INPUT/OUTPUT'
echo ''

ipAction f v m t c 192.168.43.1 d i u 1 2 3 ACCEPT
ipAction f v m t c 192.168.56.103 d i u 1 2 3 ACCEPT

ipAction f v m t c 192.168.43.0/24 d i u 1 2 3 DROP
ipAction f v m t c 192.168.56.0/24 d i u 1 2 3 DROP

ipAction f filter

echo ''
echo 'NAT PREROUTING and MASK'
echo ''

ipAction f v m nat PREROUTING 192.168.43.0/24 d i 80 192.168.56.103:8080
ipAction f v vboxnet0
ipAction f nat


echo ''
echo 'VBOX TIME'
echo ''

outSo=`pgrep VirtualBoxVM`
if (( ${#outSo} < 1 ));
then
    sudo -S mkdir -p /media/kaumi/Hack
    sudo -S chmod 777 /media/kaumi/Hack
    sudo -S mount /dev/sdb1 /media/kaumi/Hack

    sleep 10
    xfce4-terminal -e '/usr/lib/virtualbox/VirtualBoxVM --startvm "{41c79128-74de-4b17-8805-ed8d47dd6032}"' &
    sleep 5
    xfce4-terminal -e $cono &
fi

read -sp 'press enter for finish: '
echo ''
echo ''
