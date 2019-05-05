if [[ $# <1 ]]; then
	echo "Usage: $0 <FILE>" 1>&2
	exit 1
fi
FILE=$1
make && ./cheetah -o test/${FILE}.S test/${FILE}.c && cc CMakeFiles/runtime.dir/src/runtime.c.o -o test/${FILE} test/${FILE}.S && gdb ./test/${FILE}
