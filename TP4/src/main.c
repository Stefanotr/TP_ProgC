#include <stdio.h>
#include "operator.h"
#include "fichier.h"
#include "liste.h"

void exercice_4_1(void);
void exercice_4_2(void);
void exercice_4_7(void);

int main(void) {
    int choix;

    printf("=== TP4 - Menu principal ===\n");
    printf("1. Exercice 4.1 - Calcul avec operateurs\n");
    printf("2. Exercice 4.2 - Gestion de fichiers\n");
    printf("3. Exercice 4.7 - Liste de couleurs\n");
    printf("Votre choix : ");
    if (scanf("%d", &choix) != 1) {
        printf("Entree invalide.\n");
        return 1;
    }

    // vider le buffer d'entree
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    switch (choix) {
        case 1:
            exercice_4_1();
            break;
        case 2:
            exercice_4_2();
            break;
        case 3:
            exercice_4_7();
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }

    return 0;
}

/* ================= Exercice 4.1 ================= */

void exercice_4_1(void) {
    int num1, num2;
    char op;

    printf("Entrez num1 : ");
    scanf("%d", &num1);

    printf("Entrez num2 : ");
    scanf("%d", &num2);

    printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
    // vider retour ligne précédent
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    op = getchar();

    int res = appliquer_operateur(num1, num2, op);

    if ((op == '/' || op == '%') && num2 == 0) {
        printf("Erreur : division ou modulo par zero.\n");
    } else {
        printf("Resultat : %d\n", res);
    }
}

/* ================= Exercice 4.2 ================= */

void exercice_4_2(void) {
    int choix;
    char nom[256];
    char message[512];

    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Ecrire dans un fichier\n");
    printf("Votre choix : ");
    if (scanf("%d", &choix) != 1) {
        printf("Entree invalide.\n");
        return;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    if (choix == 1) {
        printf("Entrez le nom du fichier a lire : ");
        if (fgets(nom, sizeof(nom), stdin) == NULL) return;
        // enlever \n
        for (int i = 0; nom[i]; i++) {
            if (nom[i] == '\n') { nom[i] = '\0'; break; }
        }
        lire_fichier(nom);
    } else if (choix == 2) {
        printf("Entrez le nom du fichier dans lequel vous souhaitez ecrire : ");
        if (fgets(nom, sizeof(nom), stdin) == NULL) return;
        for (int i = 0; nom[i]; i++) {
            if (nom[i] == '\n') { nom[i] = '\0'; break; }
        }

        printf("Entrez le message a ecrire : ");
        if (fgets(message, sizeof(message), stdin) == NULL) return;
        for (int i = 0; message[i]; i++) {
            if (message[i] == '\n') { message[i] = '\0'; break; }
        }

        ecrire_dans_fichier(nom, message);
    } else {
        printf("Choix invalide.\n");
    }
}

/* ================= Exercice 4.7 ================= */

void exercice_4_7(void) {
    struct liste_couleurs ma_liste;
    init_liste(&ma_liste);

    struct couleur couleurs[10] = {
        {0xFF, 0x00, 0x00, 0xFF},
        {0x00, 0xFF, 0x00, 0xFF},
        {0x00, 0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x00, 0xFF},
        {0xFF, 0x00, 0xFF, 0xFF},
        {0x00, 0xFF, 0xFF, 0xFF},
        {0x80, 0x80, 0x80, 0xFF},
        {0xC0, 0xC0, 0xC0, 0xFF},
        {0x12, 0x34, 0x56, 0xFF},
        {0xAB, 0xCD, 0xEF, 0xFF}
    };

    for (int i = 0; i < 10; i++) {
        insertion(&couleurs[i], &ma_liste);
    }

    printf("Liste des couleurs :\n");
    parcours(&ma_liste);
}