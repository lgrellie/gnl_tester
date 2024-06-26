#!/bin/bash
if [[ "$#" -ne 1 ]]; then
	echo "./run_tests \$BUFFER_SIZE";
else
	./clean.sh
	gcc -Wall -Wextra -Werror main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -D BUFFER_SIZE=$1 -o test_it_bonus;
	./generate_tests.sh;
	[ -d output ] || mkdir output;
	valgrind --main-stacksize=100000000 ./test_it_bonus tests/*.txt;
	for file in tests/*.txt; do
		diff "$file" "output/output_$(basename $file)" >> diffs;
		diff -q "$file" "output/output_$(basename $file)" >> diffs_files;
	done
	[ -s diffs ] && cat diffs_files || echo "No diffs found between input and output. GG <3 !!" && rm -f diffs;
	rm -f ./test_it_bonus;
fi
