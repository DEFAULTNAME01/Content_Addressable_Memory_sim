#include "fifo_macros.h"
#include <stdio.h>
#include <stdlib.h>

DEFINE_FIFO(int, IntFIFO, 10);

int main() {
    IntFIFO myFifo;
    IntFIFO_init(&myFifo);

    // 测试向FIFO中添加超过其容量的元素
    for (int i = 0; i < 12; i++) { // 尝试添加12个元素，超出容量10
        int *item = malloc(sizeof(int));
        *item = i + 1; // 为了区分，赋予不同的值
        if (IntFIFO_enqueue(&myFifo, item) == -1) {
            printf("FIFO is full, cannot enqueue %d\n", i + 1);
            free(item); // 如果无法入队，释放分配的内存
        }
    }

    // 出队并打印所有元素
    int *dequeuedItem;
    while (IntFIFO_dequeue(&myFifo, &dequeuedItem) == 0) {
        printf("Dequeued: %d\n", *dequeuedItem);
        free(dequeuedItem);
    }

    // 尝试从空的FIFO中再次出队
    if (IntFIFO_dequeue(&myFifo, &dequeuedItem) !=0) {
        printf("Cannot dequeue, FIFO is empty.\n");
    }

    // 清理FIFO资源
    IntFIFO_free(&myFifo);
    return 0;
}
