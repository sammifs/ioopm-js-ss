main: hash_table.c hash_table.h
	gcc -pedantic -Wall -g -c hash_table.c
unit_tests: hash_table_test.c hash_table.c
	gcc -Wall hash_table.c hash_table_test.c -lcunit -o unit_tests

clean:
	rm -f *.o *.gch unit_tests

.PHONY: main clean