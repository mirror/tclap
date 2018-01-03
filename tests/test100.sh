#!/bin/sh

../examples/test35 -h > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test100.out; then
	exit 0
else
	exit 1
fi
