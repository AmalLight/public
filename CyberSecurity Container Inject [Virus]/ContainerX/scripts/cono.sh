#!/bin/bash

echo *** | sudo -S rm -f /usr/bin/cono
sudo ln -s /home/kaumi/SoSupersonic/scripts/cono.sh /usr/bin/cono

sudo /sbin/shutdown now
