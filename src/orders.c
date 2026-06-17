#include "orders.h"
#include <atil/common/log.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool alloc_output(int** out, int count) {
    *out = malloc(count * sizeof(int));
    if (*out == NULL) {
        ATIL_ERROR("failed to allocate output buffer");
        return false;
    }
    ATIL_DEBUG("output allocated");
    return true;
}

void order_array_dumb() {
    const int size = 20;
    int array[size];
    
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }

    int ordinato[size];

    for (int i = 0; i < size; ++i) {
        int item_min = 256;
        int index_min;

        for (int j = 0; j < size; ++j) {
            if (array[j] != -1 && array[j] < item_min) 
            {
                item_min = array[j];
                index_min = j;
            } 
        }
        array[index_min] = -1;
        
        ordinato[i] = item_min;
    }
}

void order_array_signed(int* in, int** out, int count) {
    // alloca output
    if (!alloc_output(out, count)) return;

    bool isnt_compute[count];

    for (int i = 0; i < count; i++) {
        isnt_compute[i] = true;
    }
    
    for (int i = 0; i < count; ++i) {
        int item_min = INT_MAX;
        int index_min;

        for (int j = 0; j < count; ++j) {
            if (isnt_compute[j] && in[j] < item_min) 
            {
                item_min = in[j];
                index_min = j;
            }
        }
        isnt_compute[index_min] = false;

        (*out)[i] = item_min;
    }
}

// __ERR__
void bubble_sort(int* in, int** out, int count) {
    // alloca output
    if (!alloc_output(out, count)) return;

    memcpy(*out, in, count * sizeof(int));

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i; ++j) {
            if ((*out)[j] > (*out)[j + 1]) {
                // scambia gli elementi
                int tmp = (*out)[j];
                (*out)[j] = (*out)[j + 1];
                (*out)[j + 1] = tmp;
            }
        }
    }
}
