#include "fifo_macros.h"
#include <stdio.h>
#include <stdlib.h>

DEFINE_FIFO(int, IntFIFO, 20);

int main() {
    IntFIFO fifo1, fifo2;
    IntFIFO_init(&fifo1);
    IntFIFO_init(&fifo2);

    // 向 fifo1 添加元素
    for (int i = 1; i <= 5; i++) {
        int *item = malloc(sizeof(int));
        *item = i;
        IntFIFO_enqueue(&fifo1, item);
    }

    // 向 fifo2 添加元素
    for (int i = 6; i <= 19; i++) {
        int *item = malloc(sizeof(int));
        *item = i;
        IntFIFO_enqueue(&fifo2, item);
    }

    // 将 fifo2 附加到 fifo1
    IntFIFO_append(&fifo1, &fifo2);

    // 打印合并后的 fifo1
    int *item= malloc(sizeof(int));
    while (IntFIFO_dequeue(&fifo1, &item) == 0) {
        printf("Dequeued fifo1: %d\n", *item);
        free(item);
    }
    
    // 清理
    IntFIFO_free(&fifo1);
   ///IntFIFO_free(&fifo2);
    return 0;
}
