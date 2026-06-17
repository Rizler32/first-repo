#pragma once

typedef struct repetition_t {
    int sym;
    int rep_number; // starts from 1
} repetition_t;

void array_find_repetitions(int* in, int in_count, repetition_t** out_rep, int* out_rep_count);
