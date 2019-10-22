#!/bin/bash
if [[ "$#" -ne 1 ]]; then
	echo "./run_tests \$BUFFER_SIZE";
else
	gcc main.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=$1;
	./generate_tests.sh;
	./a.out tests/*.txt;
	for file in tests/*.txt; do
		diff -q "$file" "output/output_$(basename $file)" >> diffs;
	done
	[ -s diffs ] && cat diffs || echo "No diffs found between input and output. GG <3 !!";
	./clean.sh;
fi