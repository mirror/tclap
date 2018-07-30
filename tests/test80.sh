#!/bin/sh
# success (everything but -n mike should be ignored)
./simple-test.sh `basename $0 .sh` test22 asdf -n mike asdf fds xxx
