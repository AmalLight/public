#!/bin/bash

home=/home/kaumi
pass=`combo mohammad`
rm -f $home/.bash_history

reset
echo $pass | sudo -S bleachbit --preset -c
bleachbit --preset -c
history -c