#!/bin/bash

aclocal -I config  
autoconf
autoheader
automake -a
