#include <stdio.h>

int main() {

    printf("La taille de int est : %lu octets\n", sizeof(int));
    printf("La taille de int* est : %lu octets\n", sizeof(int*));
    printf("La taille de int** est : %lu octets\n", sizeof(int**));

    printf("La taille de char* est : %lu octets\n", sizeof(char*));
    printf("La taille de char** est : %lu octets\n", sizeof(char**));
    printf("La taille de char*** est : %lu octets\n", sizeof(char***));

    printf("La taille de float* est : %lu octets\n", sizeof(float*));
    printf("La taille de float** est : %lu octets\n", sizeof(float**));
    printf("La taille de float*** est : %lu octets\n", sizeof(float***));

    return 0;
}