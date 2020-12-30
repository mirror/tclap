#!/bin/bash

../examples/test29 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test90.out; then
	exit 0
else
	exit 1
fi
