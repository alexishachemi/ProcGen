#!/usr/bin/bash

make debug
export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
./procgen
