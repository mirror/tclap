#!/bin/bash

../examples/test30 -p "1 2.3" > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test91.out; then
	exit 0
else
	exit 1
fi
