#include <stdio.h>

int main() {

    char noms[5][50] = {"Dupont", "Martin", "Durand", "Bernard", "Petit"};
    char prenoms[5][50] = {"Marie", "Paul", "Luc", "Anna", "Sophie"};
    char adresses[5][100] = {
        "10 rue A",
        "20 rue B",
        "30 rue C",
        "40 rue D",
        "50 rue E"
    };

    float note_prog[5] = {16.5, 14.0, 12.5, 18.0, 9.5};
    float note_sys[5]  = {12.1, 14.1, 11.3, 15.0, 10.2};

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i+1);
        printf("Nom : %s\n", noms[i]);
        printf("Prenom : %s\n", prenoms[i]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Note prog : %.2f\n", note_prog[i]);
        printf("Note sys : %.2f\n\n", note_sys[i]);
    }

    return 0;
}
