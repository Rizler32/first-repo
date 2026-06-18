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


#define CONTACT_COUNT 10

static inline void _add_contact(phone_contact_t* contacts, int phone, const char* name, const char* surname) {
    static int i = 0;
    contacts[i++] = (phone_contact_t){
        .phone_number = phone,
        .name         = name,
        .surname      = surname
    };
}

static inline void _search_contact(const char* name, phone_contact_t* contacts) {
    phone_contact_t* found = get_phone_contact_by_name(name, contacts, CONTACT_COUNT);
    if (found)
        printf("the phone number of contact with name \"%s\" is %d\n", name, found->phone_number);
    else
        printf("no contact with the name \"%s\" was found\n", name);
}

int program_phone() {
    phone_contact_t* contacts = malloc(CONTACT_COUNT * sizeof(phone_contact_t));

#define ADD_CONTACT(i) _add_contact(contacts, 100+i, "name"#i, "surname"#i)
    
    ADD_CONTACT(0);
    ADD_CONTACT(1);
    ADD_CONTACT(2);
    ADD_CONTACT(3);
    ADD_CONTACT(4);
    ADD_CONTACT(5);
    ADD_CONTACT(6);
    ADD_CONTACT(7);
    ADD_CONTACT(8);
    ADD_CONTACT(9);
    
    printf("contact 0's name: %d\n", contacts[0].phone_number);
    
#define SEARCH_CONTACT(i) _search_contact("name"#i, contacts)

    SEARCH_CONTACT(0);
    SEARCH_CONTACT(1);
    SEARCH_CONTACT(2);
    SEARCH_CONTACT(3);
    SEARCH_CONTACT(11); // non dovrebbe trovarlo

    free(contacts);
}
