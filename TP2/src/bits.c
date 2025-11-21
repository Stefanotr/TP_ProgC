#include <stdio.h>

int main() {

    int d = 0x10001000;  // valeur modifiable
    int bit4, bit20, resultat;

    // 4e bit de gauche = bit 28
    bit4 = (d >> 28) & 1;

    // 20e bit de gauche = bit 12
    bit20 = (d >> 12) & 1;

    // Vérification : les deux doivent être = 1
    if (bit4 == 1 && bit20 == 1) {
        resultat = 1;
    } else {
        resultat = 0;
    }

    printf("%d\n", resultat);

    return 0;
}