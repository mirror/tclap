#!/bin/sh

# success
../examples/test5 -b asdf -c fdas -g asdf > tmp.out 2>&1

if cmp -s tmp.out test21.out; then
	exit 0
else 
	exit 1
fi

