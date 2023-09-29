main: hash_table.c hash_table.h
	gcc -pedantic -Wall -g -c hash_table.c
unit_tests: hash_table_test.c hash_table.c linked_list.h iterator.c
	gcc -Wall hash_table.c hash_table_test.c iterator.c simple_linked_list-1.c -lcunit -o unit_tests

memtest:
	valgrind --leak-check=full ./unit_tests

clean:
	rm -f *.o *.gch unit_tests

.PHONY: main unit_tests clean
