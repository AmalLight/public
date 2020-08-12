#!/bin/bash

echo ''
echo 'Building unwrap'
echo ''

gcc other.c dec.c bin.c ott.c esa.c main.c
echo 'build now'

echo ''
echo 'exec unwrap'
echo ''
./a.out $@
echo ''