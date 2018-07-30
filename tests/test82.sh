#!/bin/sh
# success - all unmatched args get slurped up in the UnlabeledMultiArg
./simple-test.sh `basename $0 .sh` test23 blah --blah -s=bill -i=9 -i=8 -B homer marge bart
