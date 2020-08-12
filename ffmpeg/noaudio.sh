#!/bin/bash

if (( ${#@} > 0 && ${#@} < 2 ));
then
    file=$1

    rm -f ./out.mp3 ; sync

    ffmpeg -i $file -f mp3 out.mp3

else
    echo ''
    echo 'forgot arg1: file  ?'
    echo ''
fi