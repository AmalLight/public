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

cd /home/kaumi/SoSupersonic/server/

if [[ ! -f tsconfig.json ]]; then tsc --init ; fi ;

/usr/bin/code /home/kaumi/SoSupersonic/server &

sleep 3
