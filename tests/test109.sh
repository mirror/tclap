#!/bin/bash

TEST_RESULT=`dirname $0`/test109

../examples/test41 -h 2>&1 | head -n 5 | tee tmp.out

if cmp -s tmp.out $TEST_RESULT.out; then
    echo "OK"
    exit 0
else
    echo "FAIL"
    diff tmp.out $TEST_RESULT.out
    exit 1
fi
