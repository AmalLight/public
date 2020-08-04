#!/bin/bash

git fetch --all
git pull origin master

rm -rf ../backup ; sync ; cp -r ../public ../backup
