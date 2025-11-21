#include <stdio.h>
#include <string.h>

struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note1;
    float note2;
};

int main() {

    struct Etudiant ets[5];

    strcpy(ets[0].nom, "Dupont");
    strcpy(ets[0].prenom, "Marie");
    strcpy(ets[0].adresse, "20, Boulevard Niels Bohr, Lyon");
    ets[0].note1 = 16.5; ets[0].note2 = 12.1;

    strcpy(ets[1].nom, "Martin");
    strcpy(ets[1].prenom, "Pierre");
    strcpy(ets[1].adresse, "22, Boulevard Niels Bohr, Lyon");
    ets[1].note1 = 14.0; ets[1].note2 = 14.1;

    strcpy(ets[2].nom, "Durand");
    strcpy(ets[2].prenom, "Luc");
    strcpy(ets[2].adresse, "10 Rue C");
    ets[2].note1 = 12.5; ets[2].note2 = 11.3;

    strcpy(ets[3].nom, "Bernard");
    strcpy(ets[3].prenom, "Anna");
    strcpy(ets[3].adresse, "3 Avenue D");
    ets[3].note1 = 18.0; ets[3].note2 = 15.0;

    strcpy(ets[4].nom, "Petit");
    strcpy(ets[4].prenom, "Sophie");
    strcpy(ets[4].adresse, "5 Rue E");
    ets[4].note1 = 9.5; ets[4].note2 = 10.2;

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i+1);
        printf("Nom : %s\n", ets[i].nom);
        printf("Prenom : %s\n", ets[i].prenom);
        printf("Adresse : %s\n", ets[i].adresse);
        printf("Note 1 : %.2f\n", ets[i].note1);
        printf("Note 2 : %.2f\n\n", ets[i].note2);
    }

    return 0;
}