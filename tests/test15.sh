#!/bin/sh

# failure
../examples/test3  -s bbb homer marge bart -- -hv two > tmp.out 2>&1

if cmp -s tmp.out test15.out; then
	exit 0
else 
	exit 1
fi

