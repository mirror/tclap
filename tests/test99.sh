#!/bin/bash

../examples/test34 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test99.out; then
	exit 0
else
	exit 1
fi
