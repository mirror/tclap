#!/bin/sh

# failure
../examples/test8  -s=one homer -B > tmp.out 2>&1

if cmp -s tmp.out test51.out; then
	exit 0
else 
	exit 1
fi

