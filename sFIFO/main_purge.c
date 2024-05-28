
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "fifo_macros.h"
#include "register_macros.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    uint32_t opcode;
    uint32_t operand1;
    uint32_t operand2;
    uint32_t srcPCindex;
    uint32_t targetRFindex;
    uint32_t Result;
    bool isreadyforcommit;
    uint32_t targetMemindex;
    bool ispredicate;
    uint32_t predicateIndex;
} RoB_ITEM;

DEFINE_REGISTER(RoB_ITEM, ReorderBuffer, 10);
DEFINE_FIELD_MATCH_BY(RoB_ITEM,predicateIndex,uint32_t);

int main() {
     NEED_REGISTER(ReorderBuffer,RoB);
    // 创建并初始化第一个RoB项
    RoB_ITEM *rob1 = malloc(sizeof(RoB_ITEM));

      if (!rob1) {
        perror("Memory allocation failed for rob1");
        return EXIT_FAILURE;
    }
    rob1->opcode = 1;
    rob1->operand1 = 2;
    rob1->operand2 = 3;
    rob1->srcPCindex = 4;
    rob1->targetRFindex = 5;
    rob1->Result = 6;
    rob1->ispredicate = false;
    rob1->isreadyforcommit = true;
    rob1->targetMemindex = 7;
    rob1->predicateIndex = 8;
    REGISTER_enqueue(ReorderBuffer, RoB, rob1);
    REFRESH_REGISTER(ReorderBuffer, RoB);
    // 创建并初始化第二个RoB项
    RoB_ITEM *rob2 = malloc(sizeof(RoB_ITEM));
    if (!rob2) {
        perror("Memory allocation failed for rob2");
        return EXIT_FAILURE;
    }
    rob2->opcode = 11;
    rob2->operand1 = 12;
    rob2->operand2 = 13;
    rob2->srcPCindex = 14;
    rob2->targetRFindex = 15;
    rob2->Result = 16;
    rob2->ispredicate = true;
    rob2->isreadyforcommit = false;
    rob2->targetMemindex = 17;
    rob2->predicateIndex = 8;
    REGISTER_enqueue(ReorderBuffer, RoB, rob2);
    REFRESH_REGISTER(ReorderBuffer, RoB);
    // 创建并初始化第三个RoB项
    RoB_ITEM *rob3 = malloc(sizeof(RoB_ITEM));
    rob3->opcode = 21;
    rob3->operand1 = 22;
    rob3->operand2 = 23;
    rob3->srcPCindex = 24;
    rob3->targetRFindex = 25;
    rob3->Result = 26;
    rob3->ispredicate = true;
    rob3->isreadyforcommit = false;
    rob3->targetMemindex = -1;
    rob3->predicateIndex = 5;
    REGISTER_enqueue(ReorderBuffer, RoB, rob3);
    REFRESH_REGISTER(ReorderBuffer, RoB);
    // 创建并初始化第四个RoB项
    RoB_ITEM *rob4 = malloc(sizeof(RoB_ITEM));
    rob4->opcode = 31;
    rob4->operand1 = 32;
    rob4->operand2 = 33;
    rob4->srcPCindex = 34;
    rob4->targetRFindex = 35;
    rob4->Result = 36;
    rob4->ispredicate = true;
    rob4->isreadyforcommit = false;
    rob4->targetMemindex = -1;
    rob4->predicateIndex = 9;
    REGISTER_enqueue(ReorderBuffer, RoB, rob4);
    REFRESH_REGISTER(ReorderBuffer, RoB);

    int value = 5;
   // REGISTER_PURGE_WITH_CONDITION(ReorderBuffer,RoB,predicateIndexPURGE_BY,&value)


    // 出队并打印
    RoB_ITEM *dequeuedItem= malloc(sizeof(RoB_ITEM));
   
    int count = 1;  // 用于追踪循环的次数，也用于标记输出中的 Dequeued 编号
while (REGISTER_dequeue(ReorderBuffer, RoB, &dequeuedItem) == 0) {
    printf("Dequeued%d OpCode: %d, operand1: %d, operand2: %d, srcPCindex: %d, targetRFindex: %d, Result: %d, ispredicate: %d,\n isreadyforcommit: %d, targetMemindex: %d\n   predicateIndex: %d\n",
           count, dequeuedItem->opcode, dequeuedItem->operand1, dequeuedItem->operand2,
           dequeuedItem->srcPCindex, dequeuedItem->targetRFindex, dequeuedItem->Result,
           dequeuedItem->ispredicate, dequeuedItem->isreadyforcommit, dequeuedItem->targetMemindex, dequeuedItem->predicateIndex    );
    //free(dequeuedItem);  // 如果需要，取消注释
    count++;
}
printf("Dequeued%d failed\n", count);

int count1 = 1;  // 用于追踪循环的次数，也用于标记输出中的 Dequeued 编号
while (ReorderBuffer_dequeue(&RoBSrcR, &dequeuedItem) == 0) {
    printf("SrcR Dequeued%d OpCode: %d, operand1: %d, operand2: %d, srcPCindex: %d, targetRFindex: %d, Result: %d, ispredicate: %d,\n isreadyforcommit: %d, targetMemindex: %d\n   predicateIndex: %d\n",
           count1, dequeuedItem->opcode, dequeuedItem->operand1, dequeuedItem->operand2,
           dequeuedItem->srcPCindex, dequeuedItem->targetRFindex, dequeuedItem->Result,
           dequeuedItem->ispredicate, dequeuedItem->isreadyforcommit, dequeuedItem->targetMemindex, dequeuedItem->predicateIndex);
    //free(dequeuedItem);  // 如果需要，取消注释
    count1++;
}
printf("SrcR Dequeued%d failed\n", count1);

    // 清理
    free(dequeuedItem);
    REGISTER_free(ReorderBuffer, RoB);
    return 0;
    

}