#!/bin/sh
# success  tests whether * in UnlabeledValueArg passes 
./simple-test.sh `basename $0 .sh` test2 -i 1 -s asdf fff*fff
