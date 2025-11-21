#include <stdio.h>

int main() {

    char s1[100] = "Hello";
    char s2[100] = " World!";
    char copie[100];
    char concat[200];

    // ---- Longueur de s1 ----
    int len = 0;
    while (s1[len] != '\0') {
        len++;
    }
    printf("Longueur de s1 = %d\n", len);

    // ---- Copie de s1 dans copie ----
    int i = 0;
    while (s1[i] != '\0') {
        copie[i] = s1[i];
        i++;
    }
    copie[i] = '\0';

    printf("Copie : %s\n", copie);

    // ---- Concaténation s1 + s2 ----
    i = 0;
    int j = 0;

    while (s1[i] != '\0') {
        concat[i] = s1[i];
        i++;
    }

    while (s2[j] != '\0') {
        concat[i] = s2[j];
        i++;
        j++;
    }

    concat[i] = '\0';

    printf("Concat : %s\n", concat);

    return 0;
}