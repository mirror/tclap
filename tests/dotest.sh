#!/bin/bash

for T in `ls test*.sh`; do
    bash "$T" > /dev/null
    if [ $? -ne 0 ]; then
        echo "FAIL: $T"
    else
        echo "PASS: $T"
    fi
done
