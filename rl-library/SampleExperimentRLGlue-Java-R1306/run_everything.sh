for (( i = 0; i < 50; i++ )); do
	echo "Starting $i"
	./run.bash >> log.txt
done