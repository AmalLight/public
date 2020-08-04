#!/bin/bash

if (( ${#@} > 3 && ${#@} < 6 ));
then
    file=$1
    start=$2
    end=$3
    mp4=$4

    rm -f ./out1.$mp4 ./out2.$mp4 ; sync

    reduce $file 00:0 $start   $mp4 ; sync ; mv ./out.$mp4 ./out1.$mp4 ; sync
    reduce $file $end 20:20:20 $mp4 ; sync ; mv ./out.$mp4 ./out2.$mp4 ; sync

    if (( ${#@} > 4 )) ; then concat2 out1.$mp4 out2.$mp4 $mp4 $5 ; fi
    if (( ${#@} < 5 )) ; then concat2 out1.$mp4 out2.$mp4 $mp4    ; fi

    rm -f  ./out1.$mp4 ./out2.$mp4 ; sync

else
    echo ''
    echo 'forgot arg1: file ?'
    echo 'forgot arg2: start_time ?'
    echo 'forgot arg3: end___time ?'
    echo 'forgot arg4: extension_ ?'
    echo ''
    echo 'forgot arg5 ? concat2 for movie '
    echo ''
fi