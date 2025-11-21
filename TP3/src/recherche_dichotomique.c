#include <stdio.h>

int main() {

    int t[100];

    // remplir tableau trié
    for (int i = 0; i < 100; i++) {
        t[i] = i * 2; // exemple simple
    }

    printf("Tableau trié :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");

    int x;
    printf("Entrez l'entier a chercher : ");
    scanf("%d", &x);

    int debut = 0, fin = 99, milieu;
    int trouvé = 0;

    while (debut <= fin) {
        milieu = (debut + fin) / 2;

        if (t[milieu] == x) {
            trouvé = 1;
            break;
        }
        else if (t[milieu] < x) {
            debut = milieu + 1;
        }
        else {
            fin = milieu - 1;
        }
    }

    if (trouvé)
        printf("entier present\n");
    else
        printf("entier absent\n");

    return 0;
}