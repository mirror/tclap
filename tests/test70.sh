#!/bin/sh
# Checks that parsing exceptions are properly
# propagated to the caller.
`dirname $0`/simple-test.sh `basename $0 .sh` test18 --help
