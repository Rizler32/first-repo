#include "files.h"
#include <atil/common/log.h>

#include <stdio.h>
#include <stdlib.h>

void read_numbers_from_file(const char* filename, int** out_numbers, int* out_number_count) {
    FILE* file = fopen(filename, "r"); // read mode
    
    if (!file) { // check
        ATIL_ERROR("failed to open file '%s'", filename);
        return;
    }

    int number_count = 0;
    int* numbers = NULL;

    for (int i = 0; i < number_count; ++i) {
        numbers[i] = 0;
    }

    int i = 0;

    while (1) {
        long pos = ftell(file);   // salva la posizione corrente
        
        int number;
        int c = fscanf(file, "\n%d", &number);   // leggi numero

        // DBG
        ATIL_DEBUG("pos: %d, succ: %d, num: %d", ftell(file), c, number);

        if (c < 1) /* se il numero non è stato trovato */ {
            fseek(file, pos, SEEK_SET); // torna alla posizione iniziale
            
            char c = fgetc(file);
            if (c == EOF) {
                ATIL_ERROR("[%d] file ended without '-'", ftell(file));
            } else if ((c = fgetc(file)) == '-') {
                // break
            } else {
                ATIL_ERROR("[%d] unexpected error", ftell(file));
            }

            break;
        }
        
        // add a space
        int* new = realloc(numbers, sizeof(int) * ++number_count);
        numbers = new;
        
        numbers[i] = number;
        
        i++;
    }
    
    fclose(file);

    *out_numbers = numbers;
    *out_number_count = number_count;
}
