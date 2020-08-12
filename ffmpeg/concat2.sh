#!/bin/bash

if (( ${#@} > 2 && ${#@} < 5 ));
then
    file1=$1
    file2=$2
    mp4=$3

    rm -f ./out.$mp4 ;

    if (( ${#@} < 4 ));
    then
        ffmpeg -i $file1 -i $file2 \
               -filter_complex "[0:a] [1:a] concat=n=2:v=0:a=1 [a]" \
               -map [a] out.$mp4
    else
        ffmpeg -i $file1 -i $file2 \
               -filter_complex "[0:v][0:a][1:v][1:a] concat=n=2:v=1:a=1 [v] [a]" \
               -map [v] -map [a] out.$mp4
    fi
else
    echo ''
    echo 'forgot arg1: file1 ?'
    echo 'forgot arg2: file2 ?'
    echo 'forgot arg3: extension ?'
    echo ''
    echo 'forgot arg4: * optional * concat for movie '
    echo ''
fi
