#include "register_macros.h"
#include "fifo_macros.h"
#include <stdbool.h>


void initialize_all_registers(void) {
    #define X(TYPE, NAME, BASE_NAME, CAPACITY) NEED_REGISTER(NAME, BASE_NAME)
    REGISTER_LIST
    #undef X
}

void free_all_registers(void) {
    #define X(TYPE, NAME, BASE_NAME, CAPACITY) REGISTER_free(NAME, BASE_NAME)
    REGISTER_LIST
    #undef X
}