#!/bin/sh

CURDIR="$(dirname "$0")"
cd $CURDIR
CURDIR="$(pwd)"

set -e -x

find resources/ -type f -name "*.h.zip" -exec unzip -d include/ {} ';'
cd build/
../configure
make

set +x

echo ""
echo "  Done. Start kana-edit by running \""$CURDIR"/build/src/kanaedit\""
echo ""

exit 0
