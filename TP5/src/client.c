/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "client.h"

// --- FONCTION AJOUTÉE POUR L'EXERCICE 5.5/5.6 ---

/**
 * @brief Fonction pour envoyer une requête de calcul au serveur et recevoir le résultat.
 *
 * @param socketfd Le descripteur de la socket.
 * @param op L'opérateur (+, -, *, /).
 * @param num1 Le premier nombre.
 * @param num2 Le second nombre.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_operateur_numeros(int socketfd, char op, int num1, int num2) {
    char data_envoi[1024];
    char data_reception[1024];

    // Construit le message au format "calcule : <op> <num1> <num2>"
    // L'exercice 5.6 suggère aussi l'usage de variables comme 'somme' pour num1/num2, mais nous gardons ici l'approche simple 'num num'
    snprintf(data_envoi, sizeof(data_envoi), "calcule : %c %d %d", op, num1, num2);

    // Envoie le message au serveur
    int write_status = write(socketfd, data_envoi, strlen(data_envoi));
    if (write_status < 0) {
        perror("Erreur d'écriture de la requête de calcul");
        return -1;
    }
    printf("Requête envoyée: %s\n", data_envoi);

    // Réinitialisation du buffer de réception
    memset(data_reception, 0, sizeof(data_reception));

    // Lit les données de la socket (le résultat du calcul)
    int read_status = read(socketfd, data_reception, sizeof(data_reception));
    if (read_status < 0) {
        perror("Erreur de lecture du résultat");
        return -1;
    }
    if (read_status == 0) {
        printf("Serveur déconnecté.\n");
        return -1;
    }

    // Affiche le résultat reçu du serveur
    printf("Résultat reçu: %s\n", data_reception);

    return 0; // Succès
}

// --- FONCTION EXISTANTE (MIS À JOUR) ---

/**
 * Fonction pour envoyer et recevoir un message simple depuis un client connecté à la socket.
 * (Exercice 5.4)
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd) {
    char data_envoi[1024];
    char data_reception[1024];
    char message_utilisateur[1000]; // Buffer pour la saisie utilisateur

    // Demande à l'utilisateur d'entrer un message
    printf("\nVotre message simple (max 1000 caractères): ");
    if (fgets(message_utilisateur, sizeof(message_utilisateur), stdin) == NULL) {
        fprintf(stderr, "Erreur de saisie.\n");
        return -1;
    }

    // Supprimer le saut de ligne de fgets
    size_t len = strlen(message_utilisateur);
    if (len > 0 && message_utilisateur[len - 1] == '\n') {
        message_utilisateur[len - 1] = '\0';
    }

    // Construit le message avec une étiquette "message: "
    snprintf(data_envoi, sizeof(data_envoi), "message: %s", message_utilisateur);

    // Envoie le message au serveur
    int write_status = write(socketfd, data_envoi, strlen(data_envoi));
    if (write_status < 0) {
        perror("Erreur d'écriture du message simple");
        return -1;
    }

    // Réinitialisation du buffer de réception
    memset(data_reception, 0, sizeof(data_reception));

    // Lit les données de la socket (la réponse du serveur)
    int read_status = read(socketfd, data_reception, sizeof(data_reception));
    if (read_status <= 0) {
        if (read_status == 0) printf("Serveur déconnecté.\n");
        else perror("Erreur de lecture de la réponse");
        return -1;
    }

    // Affiche le message reçu du serveur
    printf("Réponse du Serveur: %s\n", data_reception);

    return 0; // Succès
}

// --- FONCTION MAIN MODIFIÉE POUR LE CHOIX D'EXERCICE ---

int main()
{
  int socketfd;
  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  // Pour se connecter à la même machine
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  
  // demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    close(socketfd);
    exit(EXIT_FAILURE);
  }

  printf("Connexion au serveur réussie. Port %d.\n", PORT);
  
  // Boucle pour l'envoi répété de requêtes (Ex. 5.6)
  while (1)
  {
    int choix;
    char op;
    int n1, n2;
    char ligne_saisie[256];

    printf("\n--- Menu Client ---\n");
    printf("1. Envoyer un message simple (Ex. 5.4)\n");
    printf("2. Envoyer une requête de calcul (Ex. 5.5/5.6)\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");

    if (fgets(ligne_saisie, sizeof(ligne_saisie), stdin) == NULL) {
        continue;
    }
    
    // Tenter de lire le choix à partir de la ligne saisie
    if (sscanf(ligne_saisie, "%d", &choix) != 1) {
        printf("Choix invalide.\n");
        continue;
    }

    switch (choix) {
        case 1:
            // Appel de la fonction pour message simple (Ex. 5.4)
            envoie_recois_message(socketfd);
            break;

        case 2:
            // Appel de la fonction pour calcul (Ex. 5.5)
            printf("Entrez l'opération au format: <op> <num1> <num2> (Ex: + 23 45) : ");
            
            // On utilise fgets et sscanf pour gérer les espaces et la saisie
            if (fgets(ligne_saisie, sizeof(ligne_saisie), stdin) == NULL) {
                break;
            }
            
            if (sscanf(ligne_saisie, " %c %d %d", &op, &n1, &n2) == 3) {
                envoie_operateur_numeros(socketfd, op, n1, n2);
            } else {
                printf("Format de calcul incorrect. Utilisez 'op num1 num2'.\n");
            }
            break;

        case 0:
            printf("Fermeture de la connexion...\n");
            close(socketfd);
            exit(EXIT_SUCCESS);

        default:
            printf("Option non reconnue.\n");
            break;
    }
  }

  // Cette ligne ne devrait pas être atteinte
  return 0;
}