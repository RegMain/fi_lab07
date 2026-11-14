#pragma once
#include <stdint.h>
#include "vec_double.h"

typedef struct {
    char key;
    double value;
} pair;

struct queue_node {
    pair value;
    struct queue_node *next;
};
typedef struct queue_node queue_node;

typedef struct {
    queue_node *front;
    queue_node *back;
    uint32_t size;
} queue;

queue *init();

int destroy(queue *q);

int push(queue *q, pair value);

int pop(queue *q, pair *pop_value);

int is_empty(queue *q);

uint32_t get_size(queue *q);

int print_internal(queue *q);

int print(queue *q);

int q_cmp(pair a, pair b);

int sort(queue *q, int(*cmp)(pair a, pair b));

int is_sorted(queue *q, int(*cmp)(pair a, pair b));

int push_with_order(queue *q, pair value, int(*cmp)(pair a, pair b));

vec_double *find_by_key(queue *q, char key);
