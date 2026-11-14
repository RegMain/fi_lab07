#include <stdio.h>
#include "queue.h"

int main() {
    queue *q = NULL;
    while (1) {
        printf("\nQUEUE DEMONSTRATION\n");
        printf("[1] Create\n");
        printf("[2] Push\n");
        printf("[3] Pop\n");
        printf("[4] Is empty?\n");
        printf("[5] Get size\n");
        printf("[6] Print internal presentation\n");
        printf("[7] Print values\n");
        printf("[8] Sort values\n");
        printf("[9] Push with order\n");
        printf("[10] Find by key\n");
        printf("[11] Exit\n");
        int opcode;
        scanf("%d", &opcode);
        switch (opcode) {
            case 1: {
                q = init();
                if (q) {
                    printf("Queue is created successfully.\n");
                } else {
                    printf("Error while creating queue.\n");
                }
                break;
            }
            case 2: {
                pair tmp;
                scanf("Print key (char) and value (double): %c %lf", &tmp.key, &tmp.value);
                if (push(q, tmp)) {
                    printf("Error!\n");
                } else {
                    printf("Success!\n");
                }
                break;
            }
            case 3: {
                pair tmp;
                if (pop(q, &tmp)) {
                    printf("Error!\n");
                } else {
                    printf("Success: key=%c, value=%lf\n", tmp.key, tmp.value);
                }
                break;
            }
            case 4: {
                if (is_empty(q)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Queue is not empty.\n");
                }
                break;
            }
            case 5: {
                printf("Size of queue: %d\n", get_size(q));
                break;
            }
            case 6: {
                if (print_internal(q)) {
                    printf("Error!\n");
                }
                break;
            }
            case 7: {
                if (print(q)) {
                    printf("Error!\n");
                }
                break;
            }
            case 8: {
                if (sort(q, q_cmp)) {
                    printf("Error!\n");
                }
                break;
            }
            case 9: {
                pair tmp;
                scanf("Print key (char) and value (double): %c %lf", &tmp.key, &tmp.value);
                if (push_with_order(q, tmp, q_cmp)) {
                    printf("Error!\n");
                } else {
                    printf("Success!\n");
                }
                break;
            }
            case 10: {
                char key;
                scanf("Print key (char): %c", &key);
                vec_double *vec = find_by_key(q, key);
                if (!vec) {
                    printf("Error!\n");
                } else {
                    for (int32_t i = 0; i < vec_double_get_size(vec); ++i) {
                        double value;
                        vec_double_get(vec, i, &value);
                        printf("%lf ", value);
                    }
                }
                break
            }
            case 11: {
                return 0;
            }
            default: continue;
        }
    }
    return 0;
}
