#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int t[100];
    int x;
    int present = 0;

    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        t[i] = rand() % 200;
    }

    printf("Tableau :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");

    printf("Entrez l'entier a chercher : ");
    scanf("%d", &x);

    for (int i = 0; i < 100; i++) {
        if (t[i] == x) {
            present = 1;
            break;
        }
    }

    if (present)
        printf("entier present\n");
    else
        printf("entier absent\n");

    return 0;
}