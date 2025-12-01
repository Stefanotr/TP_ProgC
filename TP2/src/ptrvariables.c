#include <stdio.h>

int main() {
    // Déclaration des variables de différents types
    char c = 0x12;
    short s = 0x1234;
    int i = 0x12345678;
    long l = 0x1122334455;
    long long ll = 0x1122334455667788;
    float f = 3.5f;
    double d = 8.25;
    long double ld = 1.2345;

    // Déclaration et initialisation des pointeurs
    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long *pl = &l;
    long long *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    printf("--- Avant manipulation (Utilisation de TOUS les pointeurs) ---\n");
    
    // Utilisation des pointeurs pour afficher les adresses et valeurs originales (corrige l'erreur 'unused variable')
    printf("c  : adresse=%p | valeur (hex)=%hhx (via *pc)\n", (void*)pc, *pc);
    printf("s  : adresse=%p | valeur (hex)=%hx (via *ps)\n", (void*)ps, *ps);
    printf("i  : adresse=%p | valeur (hex)=%x (via *pi)\n", (void*)pi, *pi);
    printf("l  : adresse=%p | valeur (hex)=%lx (via *pl)\n", (void*)pl, *pl);
    printf("ll : adresse=%p | valeur (hex)=%llx (via *pll)\n", (void*)pll, *pll);
    printf("f  : adresse=%p | valeur (float)=%f (via *pf)\n", (void*)pf, *pf);
    printf("d  : adresse=%p | valeur (double)=%lf (via *pd)\n", (void*)pd, *pd);
    printf("ld : adresse=%p | valeur (L.double)=%Lf (via *pld)\n", (void*)pld, *pld);
    
    printf("\n");

    // Manipulation des variables i et f via leurs pointeurs
    printf("Manipulation de 'i' (*pi -= 1) et de 'f' (*pf *= 2)...\n");
    *pi -= 1;
    *pf *= 2;

    printf("\n--- Après manipulation ---\n");
    
    // Affichage des résultats après manipulation
    printf("i  : adresse=%p | nouvelle valeur (hex)=%x\n", (void*)pi, *pi);
    printf("f  : adresse=%p | nouvelle valeur (float)=%f\n", (void*)pf, *pf);

    return 0;
}