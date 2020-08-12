#!/bin/bash

word=''
grep=''
sig=15

if (( ${#@}<1 )); then
    exit
elif (( ${#@}<2 )); then
    word="$1"
    grep=`pgrep $word`
else
    word="$2"
    grep=`pgrep $word`
    sig=$1
fi;

while (( ${#grep}>0 ));
do
   kill -$sig $grep
   grep=`pgrep $word`
done