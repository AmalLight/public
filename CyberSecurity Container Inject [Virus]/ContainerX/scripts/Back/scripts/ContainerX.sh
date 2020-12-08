#!/bin/bash

#**FIREWALL---START---**#

pass=***

echo $pass | sudo -S sysctl net.ipv4.conf.all.forwarding=1
sudo sysctl -a | grep ipv4 | grep forwarding | grep 1

sudo rm -f /usr/bin/SoSupersonic
sudo ln -s /home/kaumi/Back/scripts/SoSupersonic.sh /usr/bin/SoSupersonic

#**FLUSH**#

sudo iptables -Z
sudo iptables -F
sudo iptables -X

sudo iptables -t nat -Z
sudo iptables -t nat -F
sudo iptables -t nat -X

#**INPUT/OUTPUT**#

sudo iptables -A INPUT  -s 192.168.43.1   -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.43.1   -j ACCEPT
sudo iptables -A INPUT  -s 192.168.56.103 -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.56.103 -j ACCEPT

sudo iptables -A INPUT  -s 192.168.43.0/24 -j DROP
sudo iptables -A OUTPUT -d 192.168.43.0/24 -j DROP
sudo iptables -A INPUT  -s 192.168.56.0/24 -j DROP
sudo iptables -A OUTPUT -d 192.168.56.0/24 -j DROP

#**PREROUTING**#

echo ''
echo 'NAT'
echo ''

sudo iptables -t nat -A PREROUTING -s 192.168.43.0/24 -p tcp --dport 80 -j DNAT --to-destination 192.168.56.103:8080
sudo iptables -t nat -A PREROUTING -s 192.168.43.0/24 -p udp --dport 80 -j DNAT --to-destination 192.168.56.103:8080
sudo iptables -t nat -A POSTROUTING -o vboxnet0 -j MASQUERADE

sudo iptables -L -vn -t nat

echo ''
echo 'INPUT/OUTPUT'
echo ''

sudo iptables -L -vn

echo ''

# -j DNAT for prer , has need of ip ; REDIRECT doesn't have need of it
# -j SNAT for post ,
# --dport for inpout --sport for input!=output ? | input  => -s  src!=dest <= iM
# --sport for output --dport for output!=input   | output => -d dest!=src  <= iM

#**VBOX---TIME---**#

outSo=`pgrep VirtualBoxVM`

if (( ${#outSo} < 1 ));
then
    sudo -S mkdir -p /media/kaumi/Hack
    sudo -S chmod 777 /media/kaumi/Hack
    sudo -S mount /dev/sdb1 /media/kaumi/Hack

    sleep 10
    /usr/lib/virtualbox/VirtualBoxVM --comment "SoSupersonic" --startvm "{41c79128-74de-4b17-8805-ed8d47dd6032}" &
    sleep 5
fi

bool=`pgrep VirtualBoxVM`
until (( ${#bool} < 1 ));
do
    echo 'v exists'
    sleep 60
    bool=`pgrep VirtualBoxVM`
done
echo '! exists'
stop

