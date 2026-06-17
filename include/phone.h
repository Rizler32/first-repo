#pragma once

typedef struct phone_contact_s {
    int phone_number;
    const char *name, *surname;
} phone_contact_t;

/* searching functions */
phone_contact_t* get_phone_contact_by_name(const char* name, phone_contact_t* contacts, int contact_count); // return NULL if finds nothing
phone_contact_t* get_phone_contact_by_surname(const char* surname, phone_contact_t* contacts, int contact_count); // return NULL if finds nothing
