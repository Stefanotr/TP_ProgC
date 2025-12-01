#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char nom_fichier[256];

    if (argc >= 2) {
        snprintf(nom_fichier, sizeof(nom_fichier), "%s", argv[1]);
    } else {
        printf("Entrez le nom du fichier : ");
        if (fgets(nom_fichier, sizeof(nom_fichier), stdin) == NULL) {
            return 1;
        }
        for (int i = 0; nom_fichier[i]; i++) {
            if (nom_fichier[i] == '\n') { nom_fichier[i] = '\0'; break; }
        }
    }

    char phrase[256];
    printf("Entrez la phrase que vous souhaitez rechercher : ");
    if (fgets(phrase, sizeof(phrase), stdin) == NULL) {
        return 1;
    }
    for (int i = 0; phrase[i]; i++) {
        if (phrase[i] == '\n') { phrase[i] = '\0'; break; }
    }

    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", nom_fichier);
        return 1;
    }

    char ligne[512];
    int num_ligne = 0;
    int total_trouves = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        num_ligne++;
        int count = 0;

        int len_ligne = (int)strlen(ligne);
        int len_phrase = (int)strlen(phrase);

        for (int i = 0; i <= len_ligne - len_phrase; i++) {
            int j = 0;
            while (j < len_phrase && ligne[i + j] == phrase[j]) {
                j++;
            }
            if (j == len_phrase) {
                count++;
            }
        }

        if (count > 0) {
            printf("Ligne %d, %d fois\n", num_ligne, count);
            total_trouves += count;
        }
    }

    if (total_trouves == 0) {
        printf("La phrase n'a pas ete trouvee dans le fichier.\n");
    }

    fclose(f);
    return 0;
}