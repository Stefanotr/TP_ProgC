#include <stdio.h>
#include "fichier.h"

struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note1;
    float note2;
};

int main(void) {
    struct Etudiant ets[5];
    char ligne[512];
    const char *fichier = "etudiant.txt";

    for (int i = 0; i < 5; i++) {
        printf("Entrez les details de l'etudiant.e %d :\n", i + 1);

        printf("Nom : ");
        scanf("%49s", ets[i].nom);

        printf("Prenom : ");
        scanf("%49s", ets[i].prenom);

        printf("Adresse (un seul mot ou sans espace pour simplifier) : ");
        scanf("%99s", ets[i].adresse);

        printf("Note 1 : ");
        scanf("%f", &ets[i].note1);

        printf("Note 2 : ");
        scanf("%f", &ets[i].note2);
    }

    for (int i = 0; i < 5; i++) {
        snprintf(ligne, sizeof(ligne),
                 "Nom:%s Prenom:%s Adresse:%s Note1:%.2f Note2:%.2f",
                 ets[i].nom,
                 ets[i].prenom,
                 ets[i].adresse,
                 ets[i].note1,
                 ets[i].note2);

        ecrire_dans_fichier(fichier, ligne);
    }

    printf("Les details des etudiants ont ete enregistres dans le fichier %s.\n",
           fichier);

    return 0;
}