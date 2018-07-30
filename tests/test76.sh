#!/bin/sh
# failure  validates that the correct error message
# is displayed for XOR'd args
./simple-test.sh `basename $0 .sh` test20 -ba
