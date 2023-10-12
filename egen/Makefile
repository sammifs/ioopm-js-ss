hash_table_test: hash_table_test.c hash_table.c
	gcc -Wall hash_table_test.c hash_table.c linked_list.c iterator.c -lcunit -o hash_table_test

linked_list_test: linked_list_test.c linked_list.c
	gcc -Wall linked_list_test.c linked_list.c -lcunit -o linked_list_test

iterator_test: iterator_test.c iterator.c linked_list.c
	gcc -Wall iterator_test.c iterator.c linked_list.c -lcunit -o iterator_test

freq_count: 
	gcc -Wall freq_count.c hash_table.c iterator.c linked_list.c -o freq_count

clean:
	rm -f linked_list_test hash_table_test iterator_test freq_count a.out test *.html *.css *.png *.info  *.out.* *.o *.gcno *.gcda

lcov_test:
	lcov --directory . --capture --output-file app.info

.PHONY: hash_table_test linked_list_test iterator_test freq_count clean