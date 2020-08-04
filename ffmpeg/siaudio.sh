#!/bin/bash

if (( ${#@} > 2 && ${#@} < 4 ));
then
    file=$1
    audio=$2
    end=$3

    rm -f ./out.$end ; sync

    ffmpeg -i $file -i $audio -c copy -map 0:0 -map 1:0 out.$end

else
    echo ''
    echo 'la lunghezza varia a seconda del file più lungo'
    echo ''
    echo 'forgot arg1: file  ?'
    echo 'forgot arg2: audio ?'
    echo 'forgot arg3: end   ?'
    echo ''
fi