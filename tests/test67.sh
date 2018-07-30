#!/bin/sh
# this tests whether all required args are listed as
# missing when no arguments are specified
# failure  
./simple-test.sh `basename $0 .sh` test12 -v "a 1 0.3"
