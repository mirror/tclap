#!/bin/bash

../examples/test33 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test98.out; then
	exit 0
else
	exit 1
fi
