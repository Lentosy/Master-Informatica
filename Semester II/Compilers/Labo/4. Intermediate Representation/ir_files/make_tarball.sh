#!/bin/bash -ue

PRACT=4
FILES="BoundsCheck/Pass.cpp REPORT.pdf test/*.c"

cd "$( dirname "${BASH_SOURCE[0]}" )"

if [[ $# < 2 ]]; then
	echo "Usage: $0 <GROUP> <MEMBERS>..." 1>&2
	exit 1
fi
GROUP=$1
shift

# write list of group members
rm -f AUTHORS
for member in "$@"; do
    echo $member >> AUTHORS
done

# create tarball
FILENAME=$(printf 'pract%.2i_group%.2i.tar.gz' $PRACT $GROUP)
tar -czvf ${FILENAME} ${FILES} AUTHORS
echo
echo Done, tarball is named \'${FILENAME}\'
