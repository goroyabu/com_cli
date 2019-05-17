#!/bin/sh
topdir=$(cd $(dirname ${BASH_SOURCE:-$0}); pwd)
#echo $topdir
export CPATH=$topdir/include:$CPATH
export LIBRARY_PATH=$topdir/lib:$LIBRARY_PATH
#echo $CPATH
#echo $LIBRARY_PATH
#cd `cd -`
