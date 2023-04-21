# hashtable

A little study on possible hashtable optimizations (educational task).

## Table of contents
* [Introduction](#introduction)
* [Hash functions](#hash-functions)
* [Perfomance](#perfomance)

## Introduction

In this particular study we will examine 
[hashtable](https://en.wikipedia.org/wiki/Hash_table "Read more about hashtables") with chaining. 
This implementation of hashtable is based on 
[lists](https://github.com/princess-oregano/list "See list source code"). Basically, 
hashtable is an array of lists with given function to calculate hash.

### TODO: more about file with words..
### TODO: more about limitation
### TODO: more about prerequisites
### TODO: more about programs used


## Hash functions
In real-case hashtables average lenght of list is one element. To ensure, that 
hash function will give even distribution, we will pick parameters, so average
length will be appoximatelly 15 elements. We will examine 7 hash functions:
1. `hash_one()` always returns 1,
2. `hash_first_ascii` returns ASCII-code of the first character of key,
3. `hash_len` returns length of key,
4. `hash_sum_ascii` returns sum of key's characters' ASCII-codes,
5. `hash_rol` uses implementation of 
[ROL](https://www.aldeid.com/wiki/X86-assembly/Instructions/rol "Read more about ROL") instruction. 
It is calculated by next formulas: 
> H_0 = 0; 
>
> H_(i+1) = rol(H_i)^s[i];

where i = [0; strlen(key)],

6. `hash_ror` is similar to `hash_rol`, excepts it uses ROR instruction instead,
7. `hash_crc32` is typical CRC32 implementation.

The distribution is shown on next graphs:

### TODO: insert GOOD graphs
    
As you can see, the CRC32 gives the best distribution. `hash_one()`, as exected,
gives the worst results. `hash_first_ascii()`, `hash_len()` and `hash_sum_ascii()`
are concentrated in one area, which is obviously bad. `hash_rol()` is the closest to even distribution
of CRC32, though still not good enough, and `hash_ror()` has sharp peaks on the whole
number line.

In the next part of this study we will use `hash_crc32` as the best option.

## Perfomance

In this section we will try to optimize `hash_search()` with different ways, such
as:
* inline assembly
* extern functions, written in assembly language
* [intrinsics](https://www.laruence.com/sse/ "Intel Intrinsic's Guide")

As this study is first and formost an educational task, usage of all ways is
mandatory, so some of them may seem a little... questionable. 

Our first prototype will be simple search function:
```c
char *
hash_search(hash_table_t *ht, const char *key)
{
        list_t *list = &ht->table[ht->hash(key) % TABLE_SIZE];
        int size = list->tail;

        int i = 1;
        for ( ; i <= size; i++) {
                if (strcmp(key, list->elem[i].data) == 0) {
                        return list->elem[i].data;
                }
        }

        return nullptr;
}
```
Even by looking at the function, you can see a visible bottleneck: `strcmp()`. 

Indeed, when analizing program with `perf`, you can see the proof of that:
### TODO: insert pic

The first and most obvious thought is to use intrinsics, as in we work with 
strings less than 32 bytes each, which is exactly the size of `__m256i`.
So, let's rework the fragment, using `strcmp()`:
```c
__m256i key_256i = _mm256_load_si256((__m256i *) key);
__m256i data_256i = _mm256_load_si256((__m256i *) list->elem[i].data);

__m256i cmp = _mm256_cmpeq_epi8(data_256i, key_256i);
if (_mm256_movemask_epi8(cmp) == (int) 0xFFFFFFFF)
        break;
```
But then we start to see the next problem: key is not always formatted up to 32 bytes.
Actually, almost in all cases, it won't. So, we need to come up with a way to 
format key to the size of 32 bytes. Again, let's start with the easiest choice:
```c
char format_key[32] = {0};
for (int i = 0; key[i] != 0; i++) {
        if (i == 31) {
                break;
        }
        format_key[i] = key[i];
}
```
The final version of hash_search() with this changes:
```c
char *
hash_search(hash_table_t *ht, const char *key)
{
        char format_key[32] = {};

        for (int i = 0; key[i] != 0; i++) {
                if (i == 31) {
                        break;
                }
                format_key[i] = key[i];
        }

        list_t *list = &ht->table[ht->hash(format_key) % TABLE_SIZE];
        int size = list->tail;

        int i = 1;
        for ( ; i <= size; i++) {
                // AVX/AVX2 optimization of strcmp().
                const __m256i key_256i = _mm256_load_si256((const __m256i *) format_key);
                const __m256i data_256i = _mm256_load_si256((const __m256i *) list->elem[i].data);

                __m256i cmp = _mm256_cmpeq_epi64(data_256i, key_256i);
                if (_mm256_movemask_epi8(cmp) == (int) 0xFFFFFFFF)
                        return list->elem[i].data;
        }
        
        return nullptr;
}
```

### TODO: insert analysis of this optimizations

The next visible bottneck conserns formatting. To solve this program, writing 
a function in assembly language is a good option. It is written in [format.s]

### TODO: insert link to file

### TODO: analysis of this optimizations

At this point, there is little to none possible options for optimizations:
most of the code is either intrinsics or asm. So we will step aside a little, and 
do something about hash functions.

There is a special intrinsic for that purposes (exactly CRC32), but according to task,
we must use inline asm. So, that we will do:
```nasm
        push rdx
        mov eax, 0xffffffff
.loop:
        mov dl, byte [rdi]
        cmp dl, 0
        je .ret
        crc32 eax, dl
        inc rdi
        jmp .loop
.ret:
        pop rdx
        ret
```

### TODO: analysis of this optimizations

In conclusion: we got total optimization by 

### TODO: insert conclusion

