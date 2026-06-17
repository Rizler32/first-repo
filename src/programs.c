#include "programs.h"
#include "files.h"
#include "orders.h"
#include "math.h"
#include "repetitions.h"
#include "strings.h"
#include "phone.h"

#include <stdlib.h>
#include <stdio.h>

int program_read_numbers_from_file_and_order() {
    int* numbers;
    int number_count;
    
    read_numbers_from_file("test.txt", &numbers, &number_count);

    printf("Numeri letti (%u):\n", number_count);
    for (int i = 0; i < number_count; ++i) {
        printf("  %d\n", numbers[i]);
    }

    int* ordered;

    bubble_sort(numbers, &ordered, number_count);
    
    printf("Numeri ordinati:\n");
    for (int i = 0; i < number_count; ++i) {
        printf("  %d\n", ordered[i]);
    }
}

int program_gcd_and_lcm() {
    int a = 16;
    int b = 20;

    printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    printf("lcm(%d, %d) = %d\n", a, b, lcm(a, b));

    return 0;
}

int program_repetitions() {
#define INPUT_COUNT 10
    int input[INPUT_COUNT] = {5, 3, 8, 3, 9, 5, 1, 2, 8, 5};

    repetition_t* output;
    int output_count;
    array_find_repetitions(input, INPUT_COUNT, &output, &output_count);

    printf("Ripetizioni:\n");
    int n = 0;
    for (int i = 0; i < output_count; ++i) {
        printf("  s=%d, n=%u\n", output[i].sym, output[i].rep_number);
        n += output[i].rep_number;
    }
    if (n != INPUT_COUNT) {
        printf("errore: il numero di simboli presenti nella lista di ripetizioni (%d) "
               "non corrisponde al numero di simboli di input (%u)\n", n, INPUT_COUNT);
        return 1;
    }
    free(output);
#undef INPUT_COUNT
    return 0;
}

int program_order_array() {
#define INPUT_COUNT 10
    int input[INPUT_COUNT] = {5, 3, 8, 3, 9, 5, 1, 2, 8, 5};

    int* out = malloc(sizeof(input));
    
    printf("ordinando array...\n");
    bubble_sort(input, &out, INPUT_COUNT);

    printf("array ordinato:\n");
    for (int i = 0; i < INPUT_COUNT; ++i) {
        printf("  %d\n", out[i]);
    }
    printf("fine\n");
    
    return 0;
#undef INPUT_COUNT
}

int program_string_length() {
    const char* str = "123456789";
    printf("length of string \"%s\" is %u\n", str, string_length(str));
    return 0;
}


static inline void CREATE_CONTACT(phone_contact_t* contact) {
    static int counter = 0;
    *contact = {
        .phone_number = 100 + counter,
        .name         = "nome" + counter,
        .surname      = "cognome" + counter
    };
    counter++;
}

    
int program_phone() {
    const int contact_count = 10;
    phone_contact_t* contacts = malloc(contact_count * sizeof(phone_contact_t));

    CREATE_CONTACT(0)
    CREATE_CONTACT(1)
    CREATE_CONTACT(2)
    CREATE_CONTACT(3)
    CREATE_CONTACT(4)
    CREATE_CONTACT(5)
    CREATE_CONTACT(6)
    CREATE_CONTACT(7)
    CREATE_CONTACT(7)
    CREATE_CONTACT(8)
    CREATE_CONTACT(10)

    printf("contact 0's name: %d\n", contacts[0].phone_number);

#define SEARCH_CONTACT(_name) {                                                                        \
    const char* name = "nome"#_name;                                                            \
    phone_contact_t* found = get_phone_contact_by_name(name, contacts, contact_count);          \
    if (found)                                                                                  \
        printf("il numero di telefono del contatto con nome \"%s\" è %d\n", name, found);       \
    else                                                                                        \
        printf("non è stato trovato alcun contatto con nome \"%s\"\n", name);                   \
}
    
    SEARCH_CONTACT(0)
    SEARCH_CONTACT(1)
    SEARCH_CONTACT(2)
    SEARCH_CONTACT(3)
    SEARCH_CONTACT(11) // non dovrebbe trovarlo

    free(contacts);
    
#undef CREATE_CONTACT
#undef SEARCH_CONTACT
}
