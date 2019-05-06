#!/bin/sh
# failure...  no hex here, but see test19.cpp for how to use hex 
./simple-test.sh `basename $0 .sh` test2 -i 0xA -f 4.2 -s asdf asdf
