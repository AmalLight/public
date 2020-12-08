#!/bin/bash

echo *** | sudo -S rm -f /usr/bin/launch
sudo ln -s /home/kaumi/SoSupersonic/scripts/launch.sh /usr/bin/launch

echo ''
sudo iptables -Z
sudo iptables -F
sudo iptables -X

sudo iptables -A INPUT  -s 192.168.56.1 -p udp --dport 8080 -j ACCEPT
sudo iptables -A INPUT  -s 192.168.56.1 -p tcp --dport 8080 -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.56.1 -p udp --sport 8080 -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.56.1 -p tcp --sport 8080 -j ACCEPT

sudo iptables -A INPUT  -p udp --dport 8080 -j DROP
sudo iptables -A INPUT  -p tcp --dport 8080 -j DROP
sudo iptables -A OUTPUT -p udp --sport 8080 -j DROP
sudo iptables -A OUTPUT -p tcp --sport 8080 -j DROP

sudo iptables -A INPUT  -s 192.168.56.1 -p udp --dport 22 -j ACCEPT
sudo iptables -A INPUT  -s 192.168.56.1 -p tcp --dport 22 -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.56.1 -p udp --sport 22 -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.56.1 -p tcp --sport 22 -j ACCEPT

sudo iptables -A INPUT  -p udp --dport 22 -j DROP
sudo iptables -A INPUT  -p tcp --dport 22 -j DROP
sudo iptables -A OUTPUT -p udp --sport 22 -j DROP
sudo iptables -A OUTPUT -p tcp --sport 22 -j DROP

sudo iptables -L -vn

dir=/home/kaumi/SoSupersonic/server
if (( ${#@} > 0 ));
then
    start=$1

    echo ''
    echo "Script run.. start:$start"
    echo ''

    if [[ ! -f "$dir/tsconfig.json" ]];
    then
        cd $dir ; tsc --init
    fi;

    if (( $start > 0 ));
    then
        xfce4-terminal --default-working-directory=$dir -e "tsc -w --allowSyntheticDefaultImports" &
        xfce4-terminal --default-working-directory=$dir -e "npm run sass" &
        
        /usr/bin/code /home/kaumi/SoSupersonic/server &
        nodemon $dir/dist/private/scripts/index.js
    fi
fi
