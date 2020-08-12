#!/bin/bash

file=$1
time=$2
pass=$3
end=$4

if (( ${#file} > 0 && ${#time} > 0 && ${#pass} > 0 && ${#end} > 0 ));
then
    rm -f ./out.$end ; sync
    ffmpeg -i ./$file -c copy -ss $time -t $pass ./out.$end ; sync

else
    echo
    echo 00:00:00 come esempio di tempo, il programma crea ./out.$end
    echo
    echo 'file, file in input (1)'
    echo 'time, tempo di inizio (2)'
    echo 'pass, quanto tempo passa (3)'
    echo 'end, estensione di conversione (4)'
    echo
fi