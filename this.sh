#!/bin/sh
cd `dirname ${BASH_ARGV[0]}`
topdir=`pwd | xargs echo -n`
export CPATH=$topdir/include:$CPATH
export LIBRARY_PATH=$topdir/lib:$LIBRARY_PATH
cd `cd -`
