if [[ $# < 1 ]]; then
	echo "Usage: $0 <FILE>" 1>&2
	exit 1
fi
TIMEFORMAT="%E"
TOTAL=0
for i in {1..30}
do
	RES=$({ time $1; } 2>&1 | grep -oP "\d.\d{3}" | tr -d '\n')
	echo $RES
	TOTAL=$(echo "$TOTAL + $RES" | bc)
done
echo $(( $TOTAL / 30 ))
