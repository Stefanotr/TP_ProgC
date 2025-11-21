#include <stdio.h>

#define N 10

int compare(const char *a, const char *b) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }

    return a[i] == b[i]; // doit finir au même moment
}

int main() {

    char phrases[N][200] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };

    char recherche[200] = "La programmation en C est amusante.";
    int trouve = 0;

    for (int i = 0; i < N; i++) {
        if (compare(phrases[i], recherche)) {
            trouve = 1;
            break;
        }
    }

    if (trouve)
        printf("Phrase trouvee\n");
    else
        printf("Phrase non trouvee\n");

    return 0;
}