#!/bin/bash

if (( ${#@} > 1 && ${#@} < 3 ));
then
    file=$1
    volume=$2

    rm -f ./out.mp3 ; sync

    ffmpeg -i $file -filter:a "volume=0.$volume" out.mp3

else
    echo ''
    echo 'forgot arg1: file   ?'
    echo 'forgot arg2: volume ?'
    echo ''
fi