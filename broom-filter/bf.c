#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "bf.h"

static uint64_t hashfn(uint64_t x) {
    return x;
}

static uint64_t prefix(uint64_t x, int n) {
    return x >> (sizeof(uint64_t) * 8 - n);
}

static uint64_t get_abits(uint64_t x, int baseline, int abits) {
    return (x << baseline) >> (64 - abits);
}

bool bf_init(broom_filter* bf, uint64_t n, double epsilon) {
    double dn = (double) n;
    bf->rbits = (int64_t) ceil(log2(1.0 / epsilon));

    // assert small remainder case
    printf("small remainder check: %d <= %f\n", bf->rbits, 2 * log2(log2(dn)));
    assert((double) bf->rbits <= 2 * log2(log2(dn)));

    double alpha = 0.2;
    int q1_size_log = (int) ceil(log2(dn * (1 + alpha)));
    int q1_size = 1 << q1_size_log;
    bf->level_1 = malloc(sizeof(struct quotient_filter));
    bf->level_2 = malloc(sizeof(struct quotient_filter));

    int q2_size_log = (int) (ceil(log2(dn/log2(dn) * 2.0)));
    int q2_size = 1 << q2_size_log;

    bf->max_probe = (int) ceil(log(dn) / (double) log2(1.0 / epsilon));

    qf_init(bf->level_1, q1_size_log, bf->rbits);
    qf_init(bf->level_2, q2_size_log, bf->rbits);

    bf->q1bits = q1_size_log;
    bf->q2bits = q2_size_log;

    printf("q1: %d, q2: %d, rbits: %d\n", q1_size, q2_size, bf->rbits);

    return true;
}

bool bf_may_contain(broom_filter* bf, uint64_t x) {
    uint64_t hash = hashfn(x);

    uint64_t p = prefix(hash, bf->q1bits + bf->rbits);
    bool l1 = qf_may_contain(bf->level_1, p, hash);
    if (l1) {
        /* int nbits = bf->adaptivity_1[loc].size; */
        /* uint32_t adapt_bits = bf->adaptivity_1[loc].bits; */
        // TODO
    }
    if (!l1) {
        p = prefix(hash, bf->q2bits + bf->rbits);
        /* bool l2 = qf_may_contain(bf->level_2, p); */
    }
    return l1;
}

bool bf_insert(broom_filter* bf, Set* dict, uint64_t x) {
    return false;
}
