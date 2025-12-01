#include "repertoire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

// Définitions pour la file (Queue) de répertoires à parcourir
#define MAX_QUEUE 100
#define MAX_PATH 1024

// Simuler une file simple avec un tableau de chaînes
char queue[MAX_QUEUE][MAX_PATH];
int front = 0; // Tête de la file (élément à traiter)
int rear = 0;  // Queue de la file (où insérer le prochain élément)

// Ajoute un répertoire à la file
void enqueue(const char *path) {
    if (rear < MAX_QUEUE) {
        strncpy(queue[rear], path, MAX_PATH - 1);
        queue[rear][MAX_PATH - 1] = '\0'; // Assurer la terminaison
        rear++;
    } else {
        fprintf(stderr, "Erreur : Capacité maximale de la file atteinte.\n");
    }
}

// Retire un répertoire de la file
char* dequeue() {
    if (front < rear) {
        return queue[front++];
    }
    return NULL; // File vide
}

// Implémentation de la fonction de parcours itératif
void lire_dossier_iteratif(const char *nom_repertoire) {
    DIR *dir;
    struct dirent *entry;
    char current_path[MAX_PATH];
    
    // Initialisation de la file avec le répertoire de départ
    front = 0;
    rear = 0;
    enqueue(nom_repertoire);

    printf("Début du parcours itératif du répertoire : %s\n", nom_repertoire);

    // Boucle itérative principale
    while (front < rear) {
        // 1. Défiler le prochain répertoire à traiter
        char *dir_to_process = dequeue();
        
        if (dir_to_process == NULL) continue;

        printf("\nParcours du répertoire : %s\n", dir_to_process);

        // 2. Ouvrir le répertoire en cours
        dir = opendir(dir_to_process);
        if (dir == NULL) {
            perror("Erreur opendir");
            continue;
        }

        // 3. Lire les entrées du répertoire
        while ((entry = readdir(dir)) != NULL) {
            // Ignorer les répertoires "." (courant) et ".." (parent)
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Construire le chemin complet de l'entrée
            snprintf(current_path, MAX_PATH, "%s/%s", dir_to_process, entry->d_name);

            // 4. Afficher l'entrée
            printf("  -> %s", current_path);

            // 5. Si c'est un répertoire, l'ajouter à la file (pour traitement futur)
            if (entry->d_type == DT_DIR) {
                printf(" (Répertoire)\n");
                enqueue(current_path); // Enfiler pour le parcourir plus tard
            } else if (entry->d_type == DT_REG) {
                printf(" (Fichier)\n");
            } else {
                printf(" (Autre)\n");
            }
        }
        
        // 6. Fermer le répertoire
        closedir(dir);
    }
}