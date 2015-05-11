#!/bin/bash

../examples/test27 -v "1 2 3" > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test88.out; then
	exit 0
else
	exit 1
fi
