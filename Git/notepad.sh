#!/bin/bash

# sudo apt install wine
# sudo dpkg --add-architecture i386
# sudo apt update
# sudo apt install wine32

dir=/home/kaumi/Git/notepad

pass=`combo mohammad`

echo $pass | sudo -S rm -f /usr/bin/notepad
echo $pass | sudo -S ln -s $dir/../notepad.sh /usr/bin/notepad

wine $dir/notepad++.exe "$@"
