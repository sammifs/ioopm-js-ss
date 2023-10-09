# Initial Profiling Results
16k
1. _strcmp_sse2_unaligned (lib)
2. string_eq
3. _IO_file_overflow@@GLIBC_2.2.5 (lib)

10k
1. _strcmp_sse2_unaligned (lib)
2. string_eq
3. find_previous_entry & string_sum_hash

1k
1. _strcmp_sse2_unaligned (lib)
2. string_eq
3. string_sum_hash & find_previous_entry

small
1. _strcmp_sse2_unaligned (lib)
2. strcmp (lib)
3. _IO_file_xsputn@@GLIBC_2.2.5 (lib)
...
8. string_eq
10. cmpstringp
11. find_previous_entry

The top 3 functions declared by me are similar across the inputs. string_eq and find_previous_entry. String operations are obviously the trend here. Improving find_previous_entry by using k2>k1 instead of checking if k1 is NULL would lead to increased performance. 


# Coverage teste with freq_count on 10k-words.txt
freq_count.c 	98.5%98.5%

	98.5 % 	65 / 66 	100.0 % 	7 / 7

hash_table.c 	44.4%44.4%

	44.4 % 	67 / 151 	55.6 % 	10 / 18

iterator.c 	87.5%87.5%

	87.5 % 	14 / 16 	80.0 % 	4 / 5

linked_list.c 	28.7%28.7%

	28.7 % 	52 / 181 	47.4 % 	9 / 19


# Coverage test with hash_table_test.c
hash_table.c 	88.1%88.1%

	88.1 % 	133 / 151 	88.9 % 	16 / 18

hash_table_test.c 	85.9%85.9%

	85.9 % 	268 / 312 	86.1 % 	31 / 36

iterator.c 	68.8%68.8%

	68.8 % 	11 / 16 	60.0 % 	3 / 5

linked_list.c 	30.4%30.4%

	30.4 % 	55 / 181 	47.4 % 	9 / 19