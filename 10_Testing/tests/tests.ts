#include <check.h>
#include "buf.h"

#suite Initialization
#tcase size
#test capacity_init_test
    float *a = 0;
    ck_assert_uint_eq(buf_capacity(a), 0);
    buf_free(a);

#test size_init
    float *a = 0;
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);

#test size_1
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    buf_free(a);

#tcase value
#test value
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert_float_eq(a[0], (float)1.3f);
    buf_free(a);

#tcase clear
#test clear
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);

#test clear_not_free
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_ptr_ne(a, 0);
    buf_free(a);

#test free_test
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    buf_free(a);
    ck_assert_ptr_eq(a, 0);

#test clear_empty
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    buf_free(a);
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);

#test clear_no_op
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    buf_free(a);
    buf_clear(a);
    ck_assert_ptr_eq(a, 0);

#suite Access
#tcase push
#test size_10000
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_uint_eq(buf_size(ai), 10000);
    buf_free(ai);

#test match_10000
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000);
    buf_free(ai);

#tcase grow
#test grow_1000
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    buf_free(ai);

#test size_0_grow
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_size(ai), 0);
    buf_free(ai);

#test trunc_100
    long *ai = 0;
    buf_grow(ai, 1000);
    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);
    buf_free(ai);

#tcase pop
#test size_4
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_uint_eq(buf_size(a), 4);
    buf_free(a);

#test pop_3
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_float_eq(buf_pop(a), (float)1.4f);
    buf_free(a);

#test size_3
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    buf_pop(a);
    buf_trunc(a, 3);
    ck_assert_uint_eq(buf_size(a), 3);
    buf_free(a);

#test pop_2
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    buf_pop(a);
    buf_trunc(a, 3);
    ck_assert_float_eq(buf_pop(a), (float)1.3f);
    buf_free(a);

#test pop_1
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    buf_pop(a);
    buf_trunc(a, 3);
    buf_pop(a);
    ck_assert_float_eq(buf_pop(a), (float)1.2f);
    buf_free(a);

#test pop_0
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    buf_pop(a);
    buf_trunc(a, 3);
    buf_pop(a);
    buf_pop(a);
    ck_assert_float_eq(buf_pop(a), (float)1.1f);
    buf_free(a);

#test size_0_pop
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    buf_pop(a);
    buf_trunc(a, 3);
    buf_pop(a);
    buf_pop(a);
    buf_pop(a);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);