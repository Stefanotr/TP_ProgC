#include <stdio.h>

int factorielle(int num) {
    if (num == 0) {
        printf("fact(0): 1\n");
        return 1;
    } else {
        int valeur = num * factorielle(num - 1);
        printf("fact(%d): %d\n", num, valeur);
        return valeur;
    }
}

int main(void) {
    int tests[] = {0, 1, 3, 5, 7};
    int taille = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < taille; i++) {
        int n = tests[i];
        int res = factorielle(n);
        printf("Factorielle de %d = %d\n\n", n, res);
    }

    return 0;
}