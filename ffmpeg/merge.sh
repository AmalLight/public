#!/bin/bash

if (( ${#@} > 1 && ${#@} < 3 ));
then
    file1=$1
    file2=$2

    rm -f  ./out.mp3 ; sync

    ffmpeg -i $file1 -i $file2 -filter_complex amerge=inputs=2 out.mp3

else
    echo ''
    echo 'la lunghezza varia a seconda del file più corto'
    echo ''
    echo 'forgot arg1: file1 ?'
    echo 'forgot arg2: file2 ?'
    echo ''
fi