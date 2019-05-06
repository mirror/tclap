#!/bin/sh
# failure
# This used to fail on the "Too many arguments!" but now fails sooner,
# and on a more approriate error.
./simple-test.sh `basename $0 .sh` test5 --aaa asdf -c fdas --fff blah -i one -i two -j huh
