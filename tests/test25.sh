#!/bin/sh

# success
../examples/test5 --aaa asdf -c fdas --fff blah > tmp.out 2>&1

if cmp -s tmp.out test25.out; then
	exit 0
else 
	exit 1
fi

