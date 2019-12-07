#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "qf.h"
#include "set.h"

typedef struct broom_filter {
    struct quotient_filter* level_1;
    struct quotient_filter* level_2;

    int q1bits;
    int q2bits;
    int rbits;
    int max_probe;
} broom_filter;

bool bf_init(broom_filter* bf, uint64_t n, double epsilon);
bool bf_may_contain(broom_filter* bf, uint64_t x);
bool bf_insert(broom_filter* bf, Set* dict, uint64_t x);
bool bf_adapt(broom_filter* bf, Set* dict, uint64_t x);
