#!/bin/bash

pass=$1
dev=$2
ip=$3

echo $pass | sudo -S iptables -N SSH
echo $pass | sudo -S iptables -F SSH
echo $pass | sudo -S iptables -I SSH -i $dev -p tcp --dport 22 -s $ip -j ACCEPT
echo $pass | sudo -S iptables -I SSH -o $dev -p tcp --sport 22 -d $ip -j ACCEPT
echo $pass | sudo -S iptables -A SSH -i $dev -j DROP
echo $pass | sudo -S iptables -A SSH -o $dev -j DROP