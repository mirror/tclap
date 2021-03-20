#!/bin/sh
# this tests whether all required args are listed as
# missing when no arguments are specified
# failure  
`dirname $0`/simple-test.sh `basename $0 .sh` test11 -v "1 2 3"
