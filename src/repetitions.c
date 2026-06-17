#include "repetitions.h"
#include "orders.h"
#include <atil/common/log.h>

#include <stdlib.h>

void array_find_repetitions(int* in, int in_count, repetition_t** out_rep, int* out_rep_count) {
    int* ordered;

    ATIL_INFO("ordering input numbers");
    order_array_signed(in, &ordered, in_count);

    ATIL_TRACE("ordered input numbers:");
    for (int i = 0; i < in_count; ++i) {
        ATIL_TRACE("  %d", ordered[i]);
    }

    // alloca output come worst case
    *out_rep = malloc(in_count * sizeof(repetition_t));
    if (*out_rep == NULL) {
        ATIL_ERROR("failed to allocate memory for repetitions");
        return;
    }
    ATIL_DEBUG("repetitions memory allocated");

    // variabili per il ciclo
    int prev = ordered[0];
    int current_rep = 0;

    // inizializza la prima ripetizione
    (*out_rep)[current_rep].sym = ordered[0];
    (*out_rep)[current_rep].rep_number = 1;
    
    for (int i = 1; i < in_count; ++i) {
        // se il numero corrente è uguale al precedente aumenta il numero di ripetizioni
        if (ordered[i] == prev) {
            (*out_rep)[current_rep].rep_number++;
            continue;
        }
        // se il numero cambia...
        
        // inizializza la prossima ripetizione
        current_rep++;
        (*out_rep)[current_rep].sym = ordered[i];
        (*out_rep)[current_rep].rep_number = 1;

        // aggiorna prev
        prev = ordered[i];
    }

    // aggiorna il repetition count
    *out_rep_count = current_rep + 1;

    // aggiorna la memoria allocata per le ripetizioni, se necessario
    if (*out_rep_count < in_count) {
        int* temp = realloc(*out_rep, *out_rep_count * sizeof(repetition_t));
        if (temp == NULL) {
            ATIL_ERROR("failed to reallocate memory for repetitions");
            return;
        }
        ATIL_DEBUG("repetitions memory reallocated");
    } 

    // libera la memoria di ordered
    free(ordered);
}
