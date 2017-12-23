#!/bin/bash

../examples/test28 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test89.out; then
	exit 0
else
	exit 1
fi
