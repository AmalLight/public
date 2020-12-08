#!/bin/bash

echo *** | sudo -S rm -f /usr/bin/end
sudo ln -s /home/kaumi/SoSupersonic/scripts/end.sh /usr/bin/end

rm -f /home/kaumi/.bash_history

reset
sudo bleachbit --preset -c
bleachbit --preset -c
history -c
