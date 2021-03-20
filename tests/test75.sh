#!/bin/sh
# failure  validates that the correct error message
# is displayed for XOR'd args
`dirname $0`/simple-test.sh `basename $0 .sh` test20 -b -a
