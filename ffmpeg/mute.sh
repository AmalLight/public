#!/bin/bash

if (( ${#@} == 2 ));
then
    file=$1
    end=$2

    ffmpeg -i $file -c:v copy -an out.$end
else
    echo ''
    echo 'forgot arg1: file       ?'
    echo 'forgot arg2: extension  ?'
    echo ''
fi
