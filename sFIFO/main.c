#include "fifo_macros.h"
#include <stdio.h>
#include <stdlib.h>

DEFINE_FIFO(int, IntFIFO, 5);

int main() {
   IntFIFO myFifo;
    IntFIFO_init(&myFifo);

    int values[] = {41,42, 43,44,45,46,47}; // 可以添加更多的值进行测试
    int index = 0; // 用于跟踪 values 数组的索引
    while (!IntFIFO_IS_FULL(&myFifo)) {
        int *item = malloc(sizeof(int));
        if (item == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            index++; // 移动到下一个元素
            continue; // 跳过当前的入队尝试
        }
        *item = values[index];
        if (IntFIFO_enqueue(&myFifo, item) == -1) {
            printf("Failed to enqueue item: FIFO is full\n");
            free(item); // 确保即使入队失败也要释放分配的内存
        } else {
            printf("Enqueued: %d\n", values[index]);
        }
        index++; // 移动到下一个元素
    }
    printf("FIFO is full. Cannot enqueue more items.\n");
    int *dequeuedItem;
    while (IntFIFO_dequeue(&myFifo, &dequeuedItem) == 0) {
        printf("Dequeued: %d\n", *dequeuedItem);
        free(dequeuedItem); // 正确释放之前分配的内存
    }

    IntFIFO_free(&myFifo);
    return 0;
}