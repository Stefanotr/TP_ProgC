/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>

#include "serveur.h" // Assurez-vous que PORT est défini ici, ainsi que les prototypes si nécessaire.

int socketfd; // Déclaration globale de socketfd

// --- FONCTIONS DE CALCUL (EXERCICE 5.5 & 5.6) ---

/**
 * Effectue l'opération arithmétique simple demandée.
 * @param num1 Le premier opérande.
 * @param num2 Le second opérande.
 * @param op L'opérateur (+, -, *, /).
 * @return Le résultat du calcul.
 */
int effectuer_calcul(int num1, int num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0)
                return num1 / num2;
            else {
                fprintf(stderr, "Erreur de calcul: Division par zéro.\n");
                return 0; // Retourne 0 ou une valeur d'erreur spécifique
            }
        default:
            fprintf(stderr, "Erreur de calcul: Opérateur non supporté.\n");
            return 0;
    }
}

/**
 * Traite les messages de calcul envoyés par le client ("calcule : + 23 45").
 * Effectue le calcul et renvoie le résultat au client.
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param message : Le message reçu du client contenant l'opération.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_numeros_calcule(int client_socket_fd, const char *message) {
    char op;
    int num1, num2;
    int resultat;
    char reponse[1024];

    // Le format attendu est "calcule : <opérateur> <num1> <num2>"
    if (sscanf(message, "calcule : %c %d %d", &op, &num1, &num2) == 3) {
        resultat = effectuer_calcul(num1, num2, op);
        snprintf(reponse, sizeof(reponse), "calcule : %d", resultat);
        
        printf(" -> Calcul: %d %c %d = %d\n", num1, op, num2, resultat);
    } 
    // Gérer le cas de l'opération unaire ou l'opération complexe de l'Ex. 5.6
    else if (sscanf(message, "calcule : %c %d", &op, &num1) == 2) {
        
        // Simplification pour l'instant : si seulement 2 éléments sont scannés, c'est une erreur de format pour cette simple calculatrice
         snprintf(reponse, sizeof(reponse), "calcule : Erreur de format. Le message devrait être 'calcule : <op> <num1> <num2>'.");
    }
    else {
        // Échec du scan des 3 paramètres
        snprintf(reponse, sizeof(reponse), "calcule : Erreur de format. Le message n'est pas reconnu.");
    }

    // Renvoie la réponse (résultat ou erreur) au client
    return renvoie_message(client_socket_fd, reponse);
}

// --- FONCTION DE COMMUNICATION EXISTANTE ---

/**
 * Cette fonction envoie un message (*data) au client (client_socket_fd)
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message à envoyer.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int renvoie_message(int client_socket_fd, char *data) {
    int data_size = write(client_socket_fd, (void *)data, strlen(data));

    if (data_size < 0) {
        perror("Erreur d'écriture");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// --- FONCTION DE TRAITEMENT MODIFIÉE (EXERCICE 5.4 & 5.5/5.6) ---

/**
 * Cette fonction lit les données envoyées par le client,
 * et renvoie un message en réponse.
 * MODIFIÉ pour gérer l'envoi de saisie serveur (5.4) ou les requêtes de calcul (5.5/5.6).
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_envoie_message(int client_socket_fd, char *data) {
    printf("Message reçu: %s\n", data);

    // --- LOGIQUE DE CALCUL (EXERCICE 5.5 & 5.6) ---
    if (strncmp(data, "calcule :", 9) == 0) {
        return recois_numeros_calcule(client_socket_fd, data);
    } 
    
    // --- LOGIQUE DE RÉPONSE MANUELLE (EXERCICE 5.4) ---
    else if (strncmp(data, "message:", 8) == 0) {
        char reponse_serveur[1024];
        
        // Demander à l'utilisateur du serveur de saisir une réponse
        printf("Serveur: Entrez la réponse à envoyer au client (max 1023 char) : ");
        if (fgets(reponse_serveur, sizeof(reponse_serveur), stdin) == NULL) {
             strncpy(reponse_serveur, "Serveur: Erreur de saisie.", sizeof(reponse_serveur));
        }
        
        // Supprimer le saut de ligne de fgets
        size_t len = strlen(reponse_serveur);
        if (len > 0 && reponse_serveur[len - 1] == '\n') {
            reponse_serveur[len - 1] = '\0';
        }
        
        printf("Serveur: Envoi de la réponse: %s\n", reponse_serveur);
        return renvoie_message(client_socket_fd, reponse_serveur);
    }
    
    // Si ni calcul ni message simple n'est reconnu, envoyer un message d'erreur
    return renvoie_message(client_socket_fd, "Serveur: Requête non reconnue.");
}

// ... Les fonctions restantes (gerer_client, main) ne nécessitent pas de modifications ...

/**
 * Gestionnaire de signal pour Ctrl+C (SIGINT).
 * @param signal : Le signal capturé (doit être SIGINT pour Ctrl+C).
 */
void gestionnaire_ctrl_c(int signal)
{
  (void)signal; // FIX: Indique au compilateur que ce paramètre est intentionnellement ignoré.

  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");

  // Fermer le socket si ouvert
  if (socketfd != -1)
  {
    close(socketfd);
  }

  exit(0); // Quitter proprement le programme.
}

/**
 * Gère la communication avec un client spécifique.
 *
 * @param client_socket_fd Le descripteur de socket du client à gérer.
 */
void gerer_client(int client_socket_fd)
{
  char data[1024];

  // La boucle infinie est nécessaire pour l'Exercice 5.6
  while (1) 
  {
    // Réinitialisation des données
    memset(data, 0, sizeof(data));

    // Lecture des données envoyées par le client
    int data_size = read(client_socket_fd, data, sizeof(data));

    if (data_size <= 0)
    {
      // Erreur de réception ou déconnexion du client
      if (data_size == 0)
      {
        // Le client a fermé la connexion proprement
        printf("Client déconnecté.\n");
      }
      else
      {
        perror("Erreur de réception");
      }

      // Fermer le socket du client et sortir de la boucle de communication
      close(client_socket_fd);
      break; // Sortir de la boucle de communication avec ce client
    }
    
    // Le serveur lit et répond dans cette boucle infinie (Ex. 5.6)
    recois_envoie_message(client_socket_fd, data);
  }
}

/**
 * Configuration du serveur socket et attente de connexions.
 */
int main()
{

  int bind_status;                // Statut de la liaison
  struct sockaddr_in server_addr; // Structure pour l'adresse du serveur
  int option = 1;                 // Option pour setsockopt

  // Création d'une socket
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  // Vérification si la création de la socket a réussi
  if (socketfd < 0)
  {
    perror("Impossible d'ouvrir une socket");
    return -1;
  }

  // Configuration de l'option SO_REUSEADDR pour permettre la réutilisation de l'adresse du serveur
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // Initialisation de la structure server_addr
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);       // Port d'écoute du serveur
  server_addr.sin_addr.s_addr = INADDR_ANY; // Accepter les connexions de n'importe quelle adresse

  // Liaison de l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Vérification si la liaison a réussi
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Enregistrement de la fonction de gestion du signal Ctrl+C
  signal(SIGINT, gestionnaire_ctrl_c);

  // Mise en attente de la socket pour accepter les connexions entrantes jusqu'à une limite de 10 connexions en attente
  listen(socketfd, 10);

  printf("Serveur en attente de connexions...\n");
  

  struct sockaddr_in client_addr;                     // Structure pour l'adresse du client
  unsigned int client_addr_len = sizeof(client_addr); // Longueur de la structure client_addr
  int client_socket_fd;                               // Descripteur de socket du client

  // Boucle infinie
  while (1)
  {
    // Nouvelle connexion cliente
    client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket_fd < 0)
    {
      perror("accept");
      continue; // Continuer à attendre d'autres connexions en cas d'erreur
    }

    // Créer un processus enfant pour gérer la communication avec le client
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
      // Code du processus enfant
      close(socketfd); // Fermer la socket du serveur dans le processus enfant
      gerer_client(client_socket_fd);
      exit(0); // Quitter le processus enfant
    }
    else if (child_pid < 0)
    {
      perror("fork");
      close(client_socket_fd); // Fermer le socket du client en cas d'erreur
    }
    else
    {
      // Code du processus parent
      close(client_socket_fd); // Fermer le socket du client dans le processus parent
    }
  }

  // Le programme ne devrait jamais atteindre cette ligne dans la boucle infinie
  return 0;
}