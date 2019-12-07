#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "qf.h"
#include "set.h"

typedef struct adapt_bucket {
    uint32_t size;
    uint32_t bits;
} adapt_bucket;

typedef struct adapt_bits {
    adapt_bucket* buckets;
} adapt_bits;

typedef struct broom_filter {
    struct quotient_filter* level_1;
    struct quotient_filter* level_2;
    adapt_bucket* adaptivity_1;
    adapt_bucket* adaptivity_2;

    int q1bits;
    int q2bits;
    int rbits;
    int max_probe;
} broom_filter;

bool bf_init(broom_filter* bf, uint64_t n, double epsilon);
bool bf_may_contain(broom_filter* bf, uint64_t x);
bool bf_insert(broom_filter* bf, Set* dict, uint64_t x);
bool bf_adapt(broom_filter* bf, Set* dict, uint64_t x);
