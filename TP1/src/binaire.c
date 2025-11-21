#include <stdio.h>

int main() {

    int nombres[] = {0, 4096, 65536, 65535, 1024};
    int taille = sizeof(nombres) / sizeof(nombres[0]);

    for (int n = 0; n < taille; n++) {

        int valeur = nombres[n];

        printf("Nombre : %d\n", valeur);
        printf("Binaire : ");

        // affichage bit par bit (de gauche à droite)
        for (int i = 31; i >= 0; i--) {

            // on teste le bit i avec un masque (1 << i)
            int bit = (valeur >> i) & 1;
            printf("%d", bit);

            // pour plus de lisibilité, on met un espace tous les 4 bits
            if (i % 4 == 0) {
                printf(" ");
            }
        }

        printf("\n\n");
    }

    return 0;
}