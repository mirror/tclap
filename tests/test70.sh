#!/bin/sh
# Checks that parsing exceptions are properly
# propagated to the caller.
./simple-test.sh `basename $0 .sh` test18 --help
