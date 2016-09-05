#!/bin/sh
# Linux start script
# Exec kanaedit from anywhere
KANA_DIR=$(dirname "$0")
cd "${KANA_DIR}"
export LD_LIBRARY_PATH=`pwd`
./kanaedit
