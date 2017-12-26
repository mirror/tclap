#!/bin/bash

../examples/test32 -a 5 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test96.out; then
	exit 0
else
	exit 1
fi
