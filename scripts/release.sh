#!/bin/bash

TCLAP_DIR=$1
DEST=$2

if [ "$TCLAP_DIR" == "" ]; then
    echo "Need one TCLAP dir"
    echo "Usage: release.sh tclap-dir dest-dir"
    exit 1
fi

if [ "$DEST" == "" ]; then
    echo "Need one destination dir"
    echo "Usage: release.sh tclap-dir dest-dir"
    exit 1
fi

if [ ! -f "$TCLAP_DIR/test_runner.py" ]; then
    echo "$TCLAP_DIR doesn't look like a TCLAP dir"
fi

FILES="AUTHORS ChangeLog CMakeLists.txt config.h.in COPYING docs examples include INSTALL NEWS README tests"

rsync -r --chmod=ugo+r,go-w --exclude "__*__" $FILES $DEST
