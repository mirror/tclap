#!/bin/sh

# success
../examples/test2 -v > tmp.out 2>&1

if cmp -s tmp.out test8.out; then
	exit 0
else 
	exit 1
fi

