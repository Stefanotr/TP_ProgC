#include <stdio.h>

int main() {

    int n = 5;   // hauteur de la pyramide
    int i, j;

    for (i = 1; i <= n; i++) {

        // --- 1. Affichage des espaces pour centrer ---
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // --- 2. Affichage des nombres croissants ---
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // --- 3. Affichage des nombres décroissants ---
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        // Fin de ligne
        printf("\n");
    }

    printf("Generation de la pyramide terminee.\n");

    return 0;
}