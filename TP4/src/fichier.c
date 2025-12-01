#include "fichier.h"
#include <stdio.h>

void lire_fichier(const char *nom_de_fichier) {
    FILE *f = fopen(nom_de_fichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier '%s' en lecture.\n", nom_de_fichier);
        return;
    }

    char buffer[512];
    printf("Contenu du fichier %s :\n", nom_de_fichier);
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(f);
}

void ecrire_dans_fichier(const char *nom_de_fichier, const char *message) {
    /* On ouvre en mode ajout pour pouvoir réutiliser dans etudiant_bd.c */
    FILE *f = fopen(nom_de_fichier, "a");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier '%s' en ecriture.\n", nom_de_fichier);
        return;
    }

    fprintf(f, "%s\n", message);

    fclose(f);
    printf("Le message a ete ecrit dans le fichier %s.\n", nom_de_fichier);
}