#!/bin/sh

../examples/test36 -h > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test102.out; then
	exit 0
else
	exit 1
fi
