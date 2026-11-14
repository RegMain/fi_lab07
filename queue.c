#include "queue.h"
#include "vec_double.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

queue* init() {
    queue *q = (queue *)malloc(sizeof(queue));
    if (!q) {
        return NULL;
    }
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

int destroy(queue *q) {
    if (!q) {
        return 1;
    }
    queue_node *iter = q->front;
    while (iter) {
        queue_node *tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    free(q);
    return 0;
}

int push(queue *q, pair value) {
    if (!q) {
        return 1;
    }
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    node->value = value;
    node->next = NULL;
    q->size += 1;
    if (!q->front) {
        q->front = node;
        q->back = node;
        return 0;
    }
    if (!q->back) {
        q->size -= 1;
        free(node);
        return 2;
    }
    q->back->next = node;
    q->back = node;
    return 0;
}

int pop(queue *q, pair *pop_value) {
    if (!q) {
        return 1;
    }
    if (!q->size) {
        return 1;
    }
    q->size -= 1;
    queue_node *tmp = q->front;
    if (!q->size) {
        q->front = NULL;
        q->back = NULL;
    } else {
        q->front = q->front->next;
    }
    *pop_value = tmp->value;
    free(tmp);
    return 0;
}

int is_empty(queue *q) {
    if (!q || q->size == 0) {
        return 1;
    }
    return 0;
}

uint32_t get_size(queue *q) {
    if (!q) {
        return 0;
    }
    return q->size;
}

int print_internal(queue *q) {
    if (!q) {
        return 1;
    }
    printf("queue (adr %p): size=%d, front=%p, back=%p\n", (void *)q, q->size, (void *)q->front, (void *)q->back);
    queue_node *iter = q->front;
    while (iter) {
        printf("node (adr %p): value={key=%c, value=%lf}, next=%p\n", (void *)iter, iter->value.key, iter->value.value, (void *)iter->next);
        iter = iter->next;
    }
    return 0;
}

int print(queue *q) {
    if (!q) {
        return 1;
    }
    queue_node *iter = q->front;
    while (iter) {
        printf("<%c, %lf> ", iter->value.key, iter->value.value);
        iter = iter->next;
    }
    printf("\n");
    return 0;
}

int q_cmp(pair a, pair b) {
    if (a.key != b.key) {
        return (a.key < b.key);
    }
    return a.value <= b.value;
}

int sort(queue *q, int(*cmp)(pair a, pair b)) {
    if (!q) {
        return 1;
    }
    queue_node *iter_i = q->front;
    for (uint32_t i = 0; i < get_size(q); ++i) {
        queue_node *iter_j = iter_i->next;
        for (uint32_t j = i + 1; j < get_size(q); ++j) {
            if (!cmp(iter_i->value, iter_j->value)) {
                pair tmp = iter_i->value;
                iter_i->value = iter_j->value;
                iter_j->value = tmp;
            }
            iter_j = iter_j->next;
        }
        iter_i = iter_i->next;
    }
    return 0;
}

int is_sorted(queue *q, int(*cmp)(pair a, pair b)) {
    if (!q || q->size < 2) {
        return 1;
    }
    queue_node *iter_i = q->front;
    queue_node *iter_j = q->front->next;
    while (iter_j) {
        if (!cmp(iter_i->value, iter_j->value)) {
            return 0;
        }
        iter_i = iter_j;
        iter_j = iter_j->next;
    }
    return 1;
}

int push_with_order(queue *q, pair value, int(*cmp)(pair a, pair b)) {
    if (!q) {
        return 1;
    }
    if (!is_sorted(q, cmp)) {
        return 2;
    }
    queue_node *p_iter = NULL;
    queue_node *iter = q->front;
    if (!iter) {
        push(q, value);
        return 0;
    }
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    node->value = value;
    q->size += 1;
    while (iter) {
        if (p_iter == NULL && cmp(value, iter->value)) {
            q->front = node;
            node->next = iter;
            return 0;
        } else if (p_iter == NULL) {
            p_iter = iter;
            iter = iter->next;
            continue;
        }
        if (cmp(iter->value, value) && iter->next == NULL) {
            q->back = node;
            iter->next = node;
            node->next = NULL;
            return 0;
        }
        if (cmp(p_iter->value, value) && cmp(value, iter->value)) {
            p_iter->next = node;
            node->next = iter;
            return 0;
        }
        p_iter = iter;
        iter = iter->next;
    }
    free(node);
    return 2;
}

vec_double *find_by_key(queue *q, char key) {
    if (!q) {
        return NULL;
    }
    queue_node *iter = q->front;
    vec_double *vec = vec_double_init(0, 0);
    while (iter) {
        if (iter->value.key == key) {
            vec_double_push_back(vec, iter->value.value);
        }
        iter = iter->next;
    }
    return vec;
}
