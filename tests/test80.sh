#!/bin/sh

# success
../examples/test22 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test80.out; then
	exit 0
else
	exit 1
fi

