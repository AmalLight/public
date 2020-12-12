#!/bin/bash

# implicit not in until condition

bool=`pgrep VirtualBoxVM`
until ! (( ${#bool} > 0 ));
do
    echo -n ' : exists '
    sleep 60
    bool=`pgrep VirtualBoxVM`
done
echo ''
echo ' : not exists'
stop
