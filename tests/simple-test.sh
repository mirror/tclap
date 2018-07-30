#!/bin/sh

if [ -z "$srcdir" ]; then
    srcdir=`dirname $0`
fi

TEST_RESULT=$srcdir/$1
shift

../examples/"$@" 2>&1 | tee tmp.out

if cmp -s tmp.out $TEST_RESULT.out; then
    echo "OK"
    exit 0
else
    echo "FAIL"
    diff tmp.out $TEST_RESULT.out
    exit 1
fi
