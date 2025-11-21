#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int t[100];

    srand(time(NULL));

    // Remplir tableau
    for (int i = 0; i < 100; i++) {
        t[i] = (rand() % 201) - 100; // valeurs [-100 ; 100]
    }

    // Affichage tableau non trié
    printf("Tableau non trié :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");

    // TRI A BULLES
    for (int i = 0; i < 100 - 1; i++) {
        for (int j = 0; j < 100 - 1 - i; j++) {
            if (t[j] > t[j+1]) {
                int temp = t[j];
                t[j] = t[j+1];
                t[j+1] = temp;
            }
        }
    }

    // Affichage trié
    printf("Tableau trié :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");

    return 0;
}