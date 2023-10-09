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
