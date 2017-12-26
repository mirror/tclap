#!/bin/bash

../examples/test29 -a 5 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test91.out; then
	exit 0
else
	exit 1
fi
