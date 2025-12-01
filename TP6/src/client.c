/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Ajouté pour inet_addr

#include "client.h"
#include "bmp.h"
#include "cJSON.h" // Inclusion de la librairie JSON

/**
 * @brief Envoie une requête JSON au serveur et attend une réponse.
 */
static int send_and_receive_json(int socketfd, char *json_data_to_send) {
    char data_reception[1024];

    if (json_data_to_send == NULL) return -1;
    
    printf("Requête JSON envoyée: %s\n", json_data_to_send);

    // Envoie le message JSON au serveur
    int write_status = write(socketfd, json_data_to_send, strlen(json_data_to_send));
    if (write_status < 0) {
        perror("erreur ecriture");
        return -1;
    }

    // Réinitialisation du buffer de réception
    memset(data_reception, 0, sizeof(data_reception));

    // Lit les données de la socket (la réponse du serveur)
    int read_status = read(socketfd, data_reception, sizeof(data_reception) - 1);
    if (read_status <= 0) {
        if (read_status == 0) printf("Serveur déconnecté.\n");
        else perror("erreur lecture");
        return -1;
    }
    data_reception[read_status] = '\0';

    printf("Réponse JSON reçue: %s\n", data_reception);
    return 0;
}

/**
 * @brief Construit la requête JSON pour un message simple.
 */
int envoie_message_simple(int socketfd, const char *msg) {
    cJSON *root = cJSON_CreateObject();
    cJSON *valeurs = cJSON_CreateArray();

    cJSON_AddStringToObject(root, "code", "message");
    cJSON_AddItemToArray(valeurs, cJSON_CreateString(msg));
    cJSON_AddItemToObject(root, "valeurs", valeurs);
    
    char *json_string = cJSON_PrintUnformatted(root);
    int status = send_and_receive_json(socketfd, json_string);
    
    cJSON_Delete(root);
    free(json_string);
    return status;
}


/**
 * @brief Analyse une image BMP et construit la chaîne JSON de couleurs. (Ex. 6.3)
 */
static char* analyse_to_json(char *pathname, int nbr_couleurs) {
    couleur_compteur *cc = analyse_bmp_image(pathname);
    if (cc == NULL) return strdup("{\"code\":\"erreur\",\"valeurs\":[\"image_invalide\"]}");
    
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "code", "couleurs");

    cJSON *valeurs = cJSON_CreateArray();
    cJSON_AddItemToObject(root, "valeurs", valeurs);

    int count_to_send = (cc->size < nbr_couleurs) ? cc->size : nbr_couleurs;
    
    // Ajoute le nombre de couleurs effectif comme premier élément (utile pour la vérification)
    cJSON_AddItemToArray(valeurs, cJSON_CreateNumber(count_to_send)); 

    // Parcourir les couleurs triées (les plus fréquentes sont à la fin après trier_couleur_compteur)
    for (int count = 1; count <= count_to_send; count++) {
        char hex_color[10]; // Format: #RRGGBB\0
        int idx = cc->size - count; // Les plus fréquentes sont à la fin

        if (cc->compte_bit == BITS32) {
            sprintf(hex_color, "#%02x%02x%02x", 
                    cc->cc.cc32[idx].c.rouge, 
                    cc->cc.cc32[idx].c.vert, 
                    cc->cc.cc32[idx].c.bleu);
        } else { // BITS24
            sprintf(hex_color, "#%02x%02x%02x", 
                    cc->cc.cc24[idx].c.rouge, 
                    cc->cc.cc24[idx].c.vert, 
                    cc->cc.cc24[idx].c.bleu);
        }
        cJSON_AddItemToArray(valeurs, cJSON_CreateString(hex_color));
    }
    
    char *json_string = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    
    // NOTE: La libération de la mémoire cc (analyse_bmp_image) doit être ajoutée ici si non faite.
    return json_string;
}

/**
 * @brief Fonction principale pour l'envoi des couleurs au serveur. (Ex. 6.2 & 6.3)
 */
int envoie_couleurs_json(int socketfd, char *pathname, int nbr_couleurs)
{
    char *json_data = analyse_to_json(pathname, nbr_couleurs);
    
    int status = send_and_receive_json(socketfd, json_data);
    
    // Libérer la mémoire allouée par cJSON_PrintUnformatted
    free(json_data); 
    return status;
}

int main(int argc, char **argv)
{
    int socketfd;
    struct sockaddr_in server_addr;

    if (argc < 3)
    {
        printf("usage: ./client <nombre_de_couleurs> <chemin_bmp_image>\n");
        printf("Exemple: ./client 10 images/myimage.bmp\n");
        return (EXIT_FAILURE);
    }
    
    // Lecture de N (nombre de couleurs)
    int nbr_couleurs = atoi(argv[1]);
    if (nbr_couleurs <= 0 || nbr_couleurs > MAX_COLORS)
    {
        printf("Erreur: Le nombre de couleurs doit être entre 1 et %d.\n", MAX_COLORS);
        return (EXIT_FAILURE);
    }

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
    // Utiliser l'adresse locale pour la connexion client-serveur sur la même machine
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    // demande de connection au serveur
    int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_status < 0)
    {
        perror("connection serveur");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    
    // Envoyer les couleurs extraites (Ex. 6.1, 6.2, 6.3)
    envoie_couleurs_json(socketfd, argv[2], nbr_couleurs);
    
    // Si l'utilisateur voulait un test de message simple (Exemple de TP5/6.3)
    // envoie_message_simple(socketfd, "Bonjour depuis le client.");

    close(socketfd);
    return 0;
}