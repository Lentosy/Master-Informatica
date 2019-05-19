if [[ $# < 1 ]]; then
	echo "Usage: $0 <FILE>" 1>&2
	exit 1
fi

for i in {1..30}
do
	/usr/bin/time -p '\t%U' $1
done
