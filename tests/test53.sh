#!/bin/sh
# failure
`dirname $0`/simple-test.sh `basename $0 .sh` test8 -f=9 -f=1.0.0 -s=asdf asdf asdf
