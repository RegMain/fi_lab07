#include <stdio.h>
#include "queue.h"

int main() {
    queue *q = NULL;
    while (1) {
        printf("\nКУЕУЕ DEMONSTRATION\n");
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
        if (scanf("%d", &opcode) != 1) {
            printf("\nЗаходит однажды тестировщик в бар.\nЗабегает в бар.\nПролезает в бар.\nТанцует в бар.\nКрадется в бар.\nВрывается в бар.\nПрыгает в бар\n\nПосле чего делает заказ:\n— кружку пива\n— 2 кружки пива\n— 0 кружек пива\n— 999999999 кружек пива\n— ящерицу в стакане пива\n— минус одна кружка пива\n— qwertyuip кружек пива\n\nВсе тесты окончены, бар открывается для посетителей.\nПервый же посетитель подходит к бармену и спрашивает, как пройти в туалет.\nБар охватывает пламя.\n\nВот вы, товарищ, тот самый тестировщик...\n");
            if (q) {
                destroy(q);
            }
            return 0;
        }
        switch (opcode) {
            case 1: {
                if (q) {
                    destroy(q);
                }
                q = create();
                if (q) {
                    printf("Success!\n");
                } else {
                    printf("Error!\n");
                }
                break;
            }
            case 2: {
                pair tmp;
                printf("Print key (char) and value (double): ");
                if (scanf(" %c %lf", &tmp.key, &tmp.value) != 2) {
                    printf("Error!\n");
                    break;
                }
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
                    printf("Куеуе is empty.\n");
                } else {
                    printf("Куеуе is not empty.\n");
                }
                break;
            }
            case 5: {
                printf("Size of куеуе: %u\n", get_size(q));
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
                printf("Print key (char) and value (double): ");
                if (scanf(" %c %lf", &tmp.key, &tmp.value) != 2) {
                    printf("Error!\n");
                    break;
                }
                if (push_with_order(q, tmp, q_cmp)) {
                    printf("Error!\n");
                } else {
                    printf("Success!\n");
                }
                break;
            }
            case 10: {
                char key;
                printf("Print key (char): ");
                if (scanf(" %c", &key) != 1) {
                    printf("Error!\n");
                    break;
                }
                vec_double *vec = find_by_key(q, key);
                if (!vec) {
                    printf("Error!\n");
                } else {
                    for (int32_t i = 0; i < vec_double_get_size(vec); ++i) {
                        double value;
                        vec_double_get(vec, i, &value);
                        printf("%lf ", value);
                    }
                    vec_double_destroy(vec);
                }
                break;
            }
            case 11: {
                if (q) {
                    destroy(q);
                }
                return 0;
            }
            default: continue;
        }
    }
    destroy(q);
    return 0;
}
