#!/bin/sh

../examples/test3  -s one homer -B -Bh > tmp.out 2>&1

if cmp -s tmp.out test16.out; then
	exit 0
else 
	exit 1
fi

