#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "qf.h"

typedef struct adapt_bits {
    uint64_t* data;
} adapt_bits;

typedef struct broom_filter {
    struct quotient_filter* level_1;
    struct quotient_filter* level_2;
    adapt_bits adaptivity_1;
    adapt_bits adaptivity_2;
} broom_filter;

bool bf_init(broom_filter* bf, uint64_t n);
