#include <stdio.h>

int main() {

    int a = 2;     // base
    int b = 3;     // exposant
    int resultat = 1;

    // Calcul de a^b
    for (int i = 1; i <= b; i++) {
        resultat = resultat * a;
    }

    printf("%d^%d = %d\n", a, b, resultat);

    return 0;
}