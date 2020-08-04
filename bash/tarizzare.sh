#!/bin/bash

if (( ${#@} == 2 )) && [[ $1 == "c" ]];
then
   echo create
   tar -zcvf $2.tar.gz $2
   exit
fi

if ( (( ${#@} == 2 )) || (( ${#@} == 3 )) ) && [[ $1 == "x" ]];
then
   echo extract

   if (( ${#@} == 2 )); then tar -zxvf $2; fi

   if (( ${#@} == 3 )); then mkdir $3 -p; tar -zxvf $2 -C $3; fi

   exit
fi;

echo ''
echo 'args 2'
echo '___:create:c:'
echo '______arg1 :: c'
echo '______arg2 :: folder'
echo ''
echo '___:extract:x:'
echo '______arg1 :: x'
echo '______arg2 :: tar.gz'
echo ''
echo 'args 3'
echo '___:extract:x:'
echo '______arg1 :: x'
echo '______arg2 :: tar.gz'
echo '______arg2 :: folder'
echo ''