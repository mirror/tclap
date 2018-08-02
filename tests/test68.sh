#!/bin/sh
# this tests whether we can parse args from
# a vector of strings and that combined switch
# handling doesn't get fooled if the delimiter
# is in the string
# success  
./simple-test.sh `basename $0 .sh` test13
