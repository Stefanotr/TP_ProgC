#include <stdio.h>

int main() {

    int compteur = 5;  // valeur modifiable (< 10)

    printf("=== Triangle avec FOR ===\n");

    // --- Version avec for ---
    for (int i = 1; i <= compteur; i++) {
        for (int j = 1; j <= i; j++) {

            if (i >= 3 && j >= 2 && j < i) {
                printf("# ");
            } else {
                printf("* ");
            }

        }
        printf("\n");
    }


    printf("\n=== Triangle avec WHILE ===\n");

    // --- Version avec while ---
    int i = 1;
    while (i <= compteur) {

        int j = 1;
        while (j <= i) {

            if (i >= 3 && j >= 2 && j < i) {
                printf("# ");
            } else {
                printf("* ");
            }

            j++;
        }

        printf("\n");
        i++;
    }

    return 0;
}
