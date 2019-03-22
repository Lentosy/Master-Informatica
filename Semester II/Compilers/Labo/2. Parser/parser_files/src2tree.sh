if [[ $# < 1 ]]; then
	echo "Usage: $0 <FILE>" 1>&2
	exit 1
fi
FILE=$1
./cheetah test/${FILE}.c > ${FILE}.dot && dot -Tpng ${FILE}.dot > ${FILE}.png && echo Generated ${FILE}.png