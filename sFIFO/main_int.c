#include "fifo_macros.h"
#include <stdio.h>
#include <stdlib.h>

DEFINE_FIFO(int, IntFIFO, 10);

int main() {
    IntFIFO myFifo;
    IntFIFO_init(&myFifo);

    int value = 42;
    int value2 = 43;
    int *item = malloc(sizeof(int));
    *item = value;
    IntFIFO_enqueue(&myFifo, item);
    IntFIFO_enqueue(&myFifo, &value2);

    int *dequeuedItem;
    if (IntFIFO_dequeue(&myFifo, &dequeuedItem) == 0) {
        printf("Dequeued: %d\n", *dequeuedItem);
        free(dequeuedItem);
        /*这里，value 被赋值给了一个通过 malloc 分配的堆内存地址，存储在 item 中。
        因此，当你通过 free(dequeuedItem) 释放这块内存时，这是合法的，
        因为 dequeuedItem 指向的是通过 malloc 获取的有效堆内存。*/
    }
    if (IntFIFO_dequeue(&myFifo, &dequeuedItem) == 0) {
        printf("Dequeued2: %d\n", *dequeuedItem);
        //free(dequeuedItem);
        /*这里，&value2 直接传递的是局部变量 value2 的地址。
        这个地址指向的是栈内存，而非堆内存。栈内存是自动管理的，
        不应该被手动释放。当你尝试对从 FIFO 中得到的这个地址调用 free() 函数时，
        你尝试释放一个栈内存地址，这是非法的，导致了运行时错误。*/
    }
    IntFIFO_free(&myFifo);
    return 0;
}
