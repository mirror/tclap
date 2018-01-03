#!/bin/sh

../examples/test37 -h > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test104.out; then
	exit 0
else
	exit 1
fi
