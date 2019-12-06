#pragma once

#include <stdbool.h>
#include <string.h>

#define SET_NODE_SIZE 32

typedef struct SetNode {
    struct SetNode* next;
    struct SetNode* prev;
    int k[SET_NODE_SIZE];
    int size;
} SetNode;

// hashtable is an array of buckets
typedef struct Set {
    SetNode** buckets;
    size_t size;
} Set;

int set_allocate(Set** s, int size);
int set_put(Set* s, int key);
bool set_has(Set* s, int key);
void set_erase(Set* s, int key);
int set_deallocate(Set* s);
