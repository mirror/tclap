#!/bin/bash

../examples/test32 -b 5 -s foo > tmp.out 2>&1

if cmp -s tmp.out $srcdir/test97.out; then
	exit 0
else
	exit 1
fi
