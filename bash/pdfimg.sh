#!/bin/bash

# sudo apt-get install poppler-utils

if (( ${#@} == 3 ));
then
    pdf_file=$1

    img_dir=$2
    img_end=$3

    convert -quality 100 -density 300 -alpha remove $pdf_file $img_dir/img_da_pdf.$img_end
else
    echo 'first  arg pdf_file'
    echo 'second arg img_dir'
    echo 'third  arg img_end'
fi
