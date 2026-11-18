#include "queue.h"
#include "vec_double.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int begin(queue *q, iter *it) {
    if (!q || !it) {
        return 1;
    }
    it->q = q;
    it->el = q->front;
    it->prev = NULL;
    return 0;
}

int end(queue *q, iter *it) {
    if (!q || !it) {
        return 1;
    }
    it->q = q;
    it->el = NULL;
    it->prev = q->back;
    return 0;
}

int is_equal(iter a, iter b) {
    return (a.q == b.q && a.el == b.el);
}

int get_prev(iter a, pair *value) {
    if (!a.prev || !value) {
        return 1;
    }
    *value = a.prev->value;
    return 0;
}

int next(iter *a) {
    if (!a || !a->el) {
        return 1;
    }
    a->prev = a->el;
    a->el = a->el->next;
    return 0;
}

int get(iter it, pair *value) {
    if (!it.el || !value) {
        return 1;
    }
    *value = it.el->value;
    return 0;
}

int get_next(iter a, pair *value) {
    next(&a);
    if (get(a, value)) {
        return 1;
    }
    return 0;
}

int set(iter it, pair value) {
    if (!it.el) {
        return 1;
    }
    it.el->value = value;
    return 0;
}

queue* create() {
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
    iter it;
    iter it_end;
    begin(q, &it);
    end(q, &it_end);
    while (!is_equal(it, it_end)) {
        queue_node *tmp = it.el;
        next(&it);
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
    if (!node) {
        return 2;
    }
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
        return 3;
    }
    q->back->next = node;
    q->back = node;
    return 0;
}

int insert(iter it, pair value) {
    iter it_next = it;
    iter it_end;
    end(it.q, &it_end);
    if (next(&it_next)) {
        return 1;
    }
    if (is_equal(it_next, it_end)) {
        push(it.q, value);
        return 0;
    }
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    if (!node) {
        return 2;
    }
    node->value = value;
    node->next = it_next.el;
    it.el->next = node;
    it.q->size++;
    return 0;
}

int pop(queue *q, pair *pop_value) {
    if (!q || !pop_value) {
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
    printf("queue (adr %p): size=%u, front=%p, back=%p\n", (void *)q, q->size, (void *)q->front, (void *)q->back);
    iter it;
    iter it_end;
    begin(q, &it);
    end(q, &it_end);
    while (!is_equal(it, it_end)) {
        printf("node (adr %p): value={key=%c, value=%lf}, next=%p\n", (void *)it.el, it.el->value.key, it.el->value.value, (void *)it.el->next);
        next(&it);
    }
    return 0;
}

int print(queue *q) {
    if (!q) {
        return 1;
    }
    iter it, it_end;
    begin(q, &it);
    end(q, &it_end);
    while (!is_equal(it, it_end)) {
        printf("<%c, %lf> ", it.el->value.key, it.el->value.value);
        next(&it);
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
    if (!q || !cmp) {
        return 1;
    }
    iter it_end, it_i;
    end(q, &it_end);
    begin(q, &it_i);
    for (; !is_equal(it_i, it_end) ; next(&it_i)) {
        iter it_j = it_i;
        next(&it_j);
        for (; !is_equal(it_j, it_end) ; next(&it_j)) {
            pair a, b;
            get(it_i, &a);
            get(it_j, &b);
            if (!cmp(a, b)) {
                set(it_i, b);
                set(it_j, a);
            }
        }
    }
    return 0;
}

int is_sorted(queue *q, int(*cmp)(pair a, pair b)) {
    if (!q || q->size < 2 || !cmp) {
        return 1;
    }
    iter it_i, it_j, it_end;
    begin(q, &it_i);
    end(q, &it_end);
    it_j = it_i;
    next(&it_j);
    while (!is_equal(it_j, it_end)) {
        pair a, b;
        get(it_i, &a);
        get(it_j, &b);
        if (!cmp(a, b)) {
            return 0;
        }
        next(&it_i);
        next(&it_j);
    }
    return 1;
}

int push_with_order(queue *q, pair value, int(*cmp)(pair a, pair b)) {
    if (!q || !cmp) {
        return 1;
    }
    if (!is_sorted(q, cmp)) {
        return 2;
    }
    iter it, it_prev, it_end, it_begin;
    begin(q, &it);
    it_begin = it;
    end(q, &it_end);
    if (is_equal(it, it_end)) {
        push(q, value);
        return 0;
    }
    while (!is_equal(it, it_end)) {
        pair next_value;
        pair prev_value;
        pair it_value;
        get(it, &it_value);
        if (is_equal(it, it_begin) && cmp(value, it_value)) {
            if (push(q, value)) {
                return 3;
            }
            while (!is_equal(it, it_end)) {
                get(it, &it_value);
                if (is_equal(it, it_begin)) {
                    set(it, value);
                } else {
                    set(it, prev_value);
                }
                prev_value = it_value;
                next(&it);
            }
            return 0;
        } else if (is_equal(it, it_begin)) {
            it_prev = it;
            next(&it);
            continue;
        }
        if (cmp(it_value, value) && !get_next(it, &next_value)) {
            if (push(q, value)) {
                return 3;
            }
            return 0;
        }
        if (cmp(prev_value, value) && cmp(value, it_value)) {
            if (insert(it_prev, value)) {
                return 4;
            }
            return 0;
        }
        it_prev = it;
        next(&it);
    }
    return 42;
}

vec_double *find_by_key(queue *q, char key) {
    if (!q) {
        return NULL;
    }
    iter it;
    iter it_end;
    begin(q, &it);
    end(q, &it_end);
    vec_double *vec = vec_double_init(0, 0);
    while (!is_equal(it, it_end)) {
        pair it_value;
        get(it, &it_value);
        if (it_value.key == key) {
            vec_double_push_back(vec, it_value.value);
        }
        next(&it);
    }
    return vec;
}
