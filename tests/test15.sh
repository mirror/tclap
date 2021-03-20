#!/bin/sh
# failure
`dirname $0`/simple-test.sh `basename $0 .sh` test3  --stringTest bbb homer marge bart -- -hv two
