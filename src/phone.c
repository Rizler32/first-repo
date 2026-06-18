#include "phone.h"
#include <atil/common/log.h>

#include <string.h>

phone_contact_t* get_phone_contact_by_name(const char* name, phone_contact_t* contacts, int contact_count) {
    const int name_len = strlen(name);
    
    for (int i = 0; i < contact_count; ++i) {
        if (strncmp(contacts[i].name, name, name_len) == 0)
            return &contacts[i];
    }
    
    return NULL; // contatto non esistente
}

phone_contact_t* get_phone_contact_by_surname(const char* surname, phone_contact_t* contacts, int contact_count) {
    const int surname_len = strlen(surname);

    for (int i = 0; i < contact_count; ++i) {
        if (strncmp(contacts[i].surname, surname, surname_len) == 0)
            return &contacts[i];
    }

    return NULL; // contatto non esistente
}
