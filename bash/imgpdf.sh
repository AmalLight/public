#!/bin/bash

# sudo apt-get install poppler-utils

if (( ${#@} == 4 ));
then
    img_dir=$1
    img_end=$2

    pdf_dir=$3
    pdf_name=$4

    convert -quality 100 -density 300 $img_dir/*.$img_end $pdf_dir/$pdf_name.pdf
else
    echo 'first  arg img_dir'
    echo 'second arg img_end'
    echo 'third  arg pdf_dir'
    echo 'fourth arg pdf_name'
fi