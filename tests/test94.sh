#!/bin/bash

../examples/test31 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test94.out; then
	exit 0
else
	exit 1
fi
