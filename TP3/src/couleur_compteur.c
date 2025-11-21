#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Couleur {
    unsigned char r, g, b, a;
};

struct CouleurCount {
    struct Couleur c;
    int nb;
};

int egale(struct Couleur a, struct Couleur b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

int main() {

    struct Couleur t[100];
    struct CouleurCount distinct[100];
    int nb_distinct = 0;

    srand(time(NULL));

    // remplir tableau
    for (int i = 0; i < 100; i++) {
        t[i].r = rand() % 256;
        t[i].g = rand() % 256;
        t[i].b = rand() % 256;
        t[i].a = 0xff;
    }

    // comptage
    for (int i = 0; i < 100; i++) {

        int existe = 0;

        for (int j = 0; j < nb_distinct; j++) {
            if (egale(t[i], distinct[j].c)) {
                distinct[j].nb++;
                existe = 1;
                break;
            }
        }

        if (!existe) {
            distinct[nb_distinct].c = t[i];
            distinct[nb_distinct].nb = 1;
            nb_distinct++;
        }
    }

    // affichage
    for (int i = 0; i < nb_distinct; i++) {
        printf("Couleur %02x %02x %02x %02x : %d occurrences\n",
            distinct[i].c.r,
            distinct[i].c.g,
            distinct[i].c.b,
            distinct[i].c.a,
            distinct[i].nb);
    }

    return 0;
}