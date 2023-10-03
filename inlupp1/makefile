ht: hash_table.c hash_table.h simple_linked_list-1.c linked_list.h
	gcc -pedantic -Wall -g -c hash_table.c simple_linked_list-1.c
list: simple_linked_list-1.c linked_list.h common.h
	gcc -pedantic -Wall -g -c simple_linked_list-1.c
iterator: iterator.c iterator.h simple_linked_list-1.c linked_list.h common.h
	gcc -pedantic -Wall -g -c simple_linked_list-1.c iterator.c

unit_tests: hash_table_test.c hash_table.c simple_linked_list-1.c iterator.c
	gcc -Wall hash_table.c simple_linked_list-1.c hash_table_test.c iterator.c -lcunit -o unit_tests
updated_tests: updated_tests.c hash_table.c simple_linked_list-1.c iterator.c
	gcc -Wall simple_linked_list-1.c hash_table.c iterator.c updated_tests.c -lcunit -o updated_tests
memtest:
	valgrind --leak-check=full ./unit_tests

clean:
	rm -f *.o *.gch unit_tests
	rm -f *.o *.gch updated_tests

.PHONY: main clean
