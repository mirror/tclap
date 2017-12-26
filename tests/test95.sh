#!/bin/bash

../examples/test32 -h > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test95.out; then
	exit 0
else
	exit 1
fi
