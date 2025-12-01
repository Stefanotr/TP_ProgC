#include "liste.h"
#include <stdlib.h>
#include <stdio.h>

void init_liste(struct liste_couleurs *liste) {
    liste->tete = NULL;
}

void insertion(const struct couleur *c, struct liste_couleurs *liste) {
    struct maillon *nouveau = malloc(sizeof(struct maillon));
    if (!nouveau) {
        printf("Erreur : malloc a echoue dans insertion().\n");
        return;
    }

    nouveau->c = *c;
    nouveau->suivant = liste->tete;
    liste->tete = nouveau;
}

void parcours(const struct liste_couleurs *liste) {
    const struct maillon *courant = liste->tete;
    int i = 1;

    while (courant != NULL) {
        printf("Couleur %d : R=%u G=%u B=%u A=%u\n",
               i,
               courant->c.r,
               courant->c.g,
               courant->c.b,
               courant->c.a);
        courant = courant->suivant;
        i++;
    }
}