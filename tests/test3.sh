#!/bin/sh

../examples/test1 -n mike -u > tmp.out 2>&1

if cmp -s tmp.out test3.out; then
	exit 0
else 
	exit 1
fi

