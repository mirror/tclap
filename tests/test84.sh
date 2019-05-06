#!/bin/sh
# docbookoutput. The when this test fails due to e.g. formatting
# changes the results needs to be manually reviewed and the test84.out
# updated
./simple-test.sh `basename $0 .sh` test25 -h x
