#!/bin/bash

if (( ${#@} == 5 ));
then
    folder=$1
    file_name=$2
    extension=$3
    fps=$4
    seconds_for_one_fps=$5

    ffmpeg -r 1/$seconds_for_one_fps -i $folder/$file_name%03d.$extension -c:v libx264 -vf fps=$fps -pix_fmt yuv420p out.mp4

else
    echo ''
    echo 'forgot arg1: folder ?'
    echo 'forgot arg2: file name ? NNN after the name'
    echo 'forgot arg3: extension ?'
    echo 'forgot arg4: fps ?'
    echo 'forgot arg4: seconds for one fps ?'
    echo ''
fi
