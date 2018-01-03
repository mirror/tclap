#!/bin/sh

../examples/test35 -h -a 5 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test101.out; then
	exit 0
else
	exit 1
fi
