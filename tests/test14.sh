#!/bin/sh

../examples/test3  -s=aaa homer marge bart -- one two > tmp.out 2>&1

if cmp -s tmp.out test14.out; then
	exit 0
else 
	exit 1
fi

