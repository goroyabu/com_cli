#!/bin/sh
topdir=$(cd $(dirname ${BASH_SOURCE:-$0}); pwd)
export CPATH=$topdir/include:$CPATH
export LIBRARY_PATH=$topdir/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=$topdir/lib:$LD_LIBRARY_PATH
