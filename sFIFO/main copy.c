#include "fifo_macros.h"
#include "register_macros.h"
#include <stdio.h>
#include <stdlib.h>

// 定义操作码
typedef enum {
    ADD, SUB,
} OpCode;

// 定义IssueQueue结构体
typedef struct {
    OpCode Opcode;
    int s1; // RF addr1
    int s2; // RF addr2
    int r;  // result
} IssueQueue;

// 定义一个FIFO，用来处理IssueQueue类型

DEFINE_REGISTER(IssueQueue, IssueQueueFIFO, 10);
int main() {
    NEED_REGISTER(IssueQueueFIFO,myFifo);
    

    // 创建并初始化第一个IssueQueue项
    IssueQueue *iq1 = malloc(sizeof(IssueQueue));
    iq1->Opcode = ADD;
    iq1->s1 = 1;
    iq1->s2 = 2;
    iq1->r = 3;
    IssueQueueFIFO_enqueue(&myFifoSrcR, iq1);

    // 创建并初始化第二个IssueQueue项
    IssueQueue *iq2 = malloc(sizeof(IssueQueue));
    iq2->Opcode = SUB;
    iq2->s1 = 4;
    iq2->s2 = 5;
    iq2->r = 6;
    IssueQueueFIFO_enqueue(&myFifoSrcR, iq2);
    // 将 fifo2 附加到 fifo1
    //IssueQueueFIFO_append(&myFifoDestR, &myFifoSrcR);
    REFRESH_REGISTER(IssueQueueFIFO,myFifo);
    // 出队并打印
    IssueQueue *dequeuedItem;
    if (IssueQueueFIFO_dequeue(&myFifoDestR, &dequeuedItem) == 0) {
        printf("myFifoDestR Dequeued OpCode: %d, s1: %d, s2: %d, r: %d\n", dequeuedItem->Opcode, dequeuedItem->s1, dequeuedItem->s2, dequeuedItem->r);
        free(dequeuedItem);
    }

    if (IssueQueueFIFO_dequeue(&myFifoDestR, &dequeuedItem) == 0) {
        printf("myFifoDestR Dequeued2 OpCode: %d, s1: %d, s2: %d, r: %d\n", dequeuedItem->Opcode, dequeuedItem->s1, dequeuedItem->s2, dequeuedItem->r);
        free(dequeuedItem);
    }

    // 清理
    //IssueQueueFIFO_free(&myFifoDestR);
    REGISTER_free(IssueQueueFIFO,myFifo);
    return 0;
}
