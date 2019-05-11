if [[ $# < 1 ]]; then
	echo "Usage: $0 <PROGRAM>" 1>&2
	exit 1
fi
PROGRAM=$1

opt -dot-cfg test/${PROGRAM}.ll

