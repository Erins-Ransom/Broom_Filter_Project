#include <stdio.h>
#include <stdlib.h>

#include "set.h"

static size_t hashfn(size_t size, int key) {
    key = (key + 0x7ed55d16) + (key << 12);
    key = (key ^ 0xc761c23c) ^ (key >> 19);
    key = (key + 0x165667b1) + (key << 5);
    key = (key + 0xd3a2646c) ^ (key << 9);
    key = (key + 0xfd7046c5) + (key << 3);
    key = (key ^ 0xb55a4f09) ^ (key >> 16);
    return key % size;
}

static void insert_bucket(SetNode** head, SetNode* n) {
    n->next = *head;
    n->prev = NULL;
    if (*head)
        (*head)->prev = n;
    (*head) = n;
}

static void remove_bucket(SetNode** head, SetNode* n) {
    if (n->next)
        n->next->prev = n->prev;
    if (n->prev)
        n->prev->next = n->next;
    else
        (*head) = n->next;
}

int set_allocate(Set** s, int size) {
    Set* news = (Set*) malloc(sizeof(Set));
    if (!news) {
        return -1;
    }

    news->buckets = (SetNode**) calloc(sizeof(SetNode*), size);
    if (!news->buckets) {
        return -1;
    }

    news->size = size;
    (*s) = news;

    return 0;
}

int set_get_prefix(Set* s, int pre) {
    for (int b = 0; b < s->size; b++) {
        SetNode* head = s->buckets[b];
        while (head) {
            for (int i = 0; i < head->size; i++) {

            }
            head = head->next;
        }
    }
}

int set_put(Set* s, int key) {
    size_t bucketn = hashfn(s->size, key);
    SetNode* head = s->buckets[bucketn];

    while (head && head->size >= SET_NODE_SIZE) {
        head = head->next;
    }

    SetNode* n;
    if (head && head->size < SET_NODE_SIZE) {
        // current SetNode is not full
        n = head;
    } else {
        // allocate new SetNode
        n = malloc(sizeof(SetNode));

        if (!n) {
            return -1;
        }

        n->size = 0;
        insert_bucket(&s->buckets[bucketn], n);
    }

    n->k[n->size] = key;
    n->size++;

    return 0;
}

bool set_has(Set* s, int key) {
    size_t bucketn = hashfn(s->size, key);
    SetNode* b = s->buckets[bucketn];

    while (b) {
        for (int i = 0; i < b->size; i++) {
            if (key == b->k[i]) {
                return true;
            }
        }
        b = b->next;
    }

    return false;
}

void set_erase(Set* s, int key) {
    size_t bucketn = hashfn(s->size, key);
    SetNode* b = s->buckets[bucketn];

    while (b) {
        SetNode* old = NULL;
        // scan from the back of the SetNode to avoid unnecessary shifting
        for (int i = b->size - 1; i >= 0; i--) {
            if (key == b->k[i]) {
                if (b->size - i + 1 != 0) {
                    memcpy(&b->k[i], &b->k[i + 1], b->size - i + 1);
                }
                b->size--;

                if (b->size == 0) {
                    remove_bucket(&s->buckets[bucketn], b);
                    old = b;
                }
            }
        }

        b = b->next;
        free(old);  // free on NULL does nothing
    }
}

int set_deallocate(Set* s) {
    for (size_t i = 0; i < s->size; i++) {
        SetNode* b = s->buckets[i];
        while (b) {
            SetNode* old = b;
            b = b->next;
            free(old);
        }
    }
    free(s->buckets);
    free(s);
    return 0;
}
