#ifndef LISTE_H
#define LISTE_H

#include <stdint.h>

struct couleur {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct maillon {
    struct couleur c;
    struct maillon *suivant;
};

struct liste_couleurs {
    struct maillon *tete;
};

void init_liste(struct liste_couleurs *liste);
void insertion(const struct couleur *c, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);

#endif