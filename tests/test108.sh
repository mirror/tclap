#!/bin/bash

TEST=`basename $0 .sh`

../examples/test40 > tmp.out 2>&1

if cmp -s tmp.out $srcdir/$TEST.out; then
	exit 0
else
	exit 1
fi
