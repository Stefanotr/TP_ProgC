/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // Ajouté pour les fonctions réseau

#include "serveur.h"
#include "cJSON.h" // Inclusion de la librairie JSON

int socketfd; // Déclaration globale

/**
 * @brief Exécute la commande Firefox pour afficher le graphique SVG.
 */
int visualize_plot()
{
    const char *browser = "firefox";
    char command[256];
    
    // Utilisation de l'option -new-tab ou & pour ne pas bloquer le serveur
    snprintf(command, sizeof(command), "%s %s &", browser, svg_file_path); 

    int result = system(command);

    if (result == 0)
    {
        printf("SVG file opened in %s.\n", browser);
    }
    else
    {
        printf("Failed to open the SVG file (code %d). Assurez-vous que Firefox est installé.\n", result);
    }

    return 0;
}

double degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

/**
 * @brief Génère le graphique SVG en utilisant les couleurs du tableau JSON. (Ex. 6.3)
 */
int plot_json(cJSON *couleurs_array)
{
    int num_colors_total = cJSON_GetArraySize(couleurs_array);
    if (num_colors_total < 2) {
        printf("Erreur: Pas assez de données de couleur dans le JSON.\n");
        return 1;
    }
    
    // Le premier élément du tableau (indice 0) est le nombre de couleurs (Ex. 6.2)
    cJSON *n_item = cJSON_GetArrayItem(couleurs_array, 0);
    int num_colors;

    if (cJSON_IsNumber(n_item)) {
        num_colors = n_item->valueint;
    } else {
        // Si le premier élément n'est pas un nombre, on considère le reste du tableau
        num_colors = num_colors_total - 1; 
    }
    
    if (num_colors <= 0) {
        printf("Erreur: Nombre de couleurs à tracer invalide.\n");
        return 1;
    }


    FILE *svg_file = fopen(svg_file_path, "w");
    if (svg_file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");
    fprintf(svg_file, "  <text x=\"200\" y=\"20\" font-size=\"16\" text-anchor=\"middle\">Top %d Couleurs de l'Image</text>\n", num_colors);


    double center_x = 200.0;
    double center_y = 200.0;
    double radius = 150.0;
    double start_angle = -90.0; // Commence en haut (-90 degrés)

    // Tracé de la roue de couleur (camembert)
    for (int i = 1; i <= num_colors; i++) // Commence à 1 pour ignorer l'indice [0] (qui est le compte N)
    {
        cJSON *token_item = cJSON_GetArrayItem(couleurs_array, i);
        if (!cJSON_IsString(token_item)) continue;

        char *token = token_item->valuestring; // La couleur au format #RRGGBB
        
        // Tous les segments ont la même taille
        double angle_segment = 360.0 / num_colors; 
        double end_angle = start_angle + angle_segment;

        double start_angle_rad = degreesToRadians(start_angle);
        double end_angle_rad = degreesToRadians(end_angle);

        double x1 = center_x + radius * cos(start_angle_rad);
        double y1 = center_y + radius * sin(start_angle_rad);
        double x2 = center_x + radius * cos(end_angle_rad);
        double y2 = center_y + radius * sin(end_angle_rad);

        // Dessiner l'arc et le relier au centre
        fprintf(svg_file, "  <path d=\"M%.2f,%.2f L%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f Z\" fill=\"%s\" />\n",
                center_x, center_y, x1, y1, radius, radius, x2, y2, token);

        start_angle = end_angle;
    }

    fprintf(svg_file, "</svg>\n");

    fclose(svg_file);

    visualize_plot();
    return 0;
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{
    int data_size = write(client_socket_fd, (void *)data, strlen(data));

    if (data_size < 0)
    {
        perror("erreur ecriture");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

/**
 * @brief Reçoit le message JSON, l'analyse et appelle la fonction appropriée. (Ex. 6.3)
 */
int recois_envoie_message(int client_socket_fd, char data[1024])
{
    printf("\nMessage JSON reçu: %s\n", data);
    
    cJSON *root = cJSON_Parse(data);
    if (root == NULL) {
        printf("Erreur: Impossible d'analyser le JSON.\n");
        return renvoie_message(client_socket_fd, "{\"reponse\":\"Erreur JSON\"}");
    }

    cJSON *code = cJSON_GetObjectItem(root, "code");
    cJSON *valeurs = cJSON_GetObjectItem(root, "valeurs");

    if (cJSON_IsString(code) && cJSON_IsArray(valeurs))
    {
        if (strcmp(code->valuestring, "couleurs") == 0)
        {
            // Requête d'analyse de couleurs (Ex. 6.1, 6.2, 6.3)
            plot_json(valeurs);
            
            // Renvoyer une confirmation JSON
            renvoie_message(client_socket_fd, "{\"reponse\":\"OK\",\"details\":\"SVG généré et Firefox lancé\"}");
        }
        else if (strcmp(code->valuestring, "message") == 0)
        {
            // Exemple de traitement d'un message simple JSON
            char reponse_msg[1024];
            snprintf(reponse_msg, sizeof(reponse_msg), "{\"reponse\":\"OK\",\"details\":\"Message %s reçu par le serveur\"}", cJSON_GetStringValue(cJSON_GetArrayItem(valeurs, 0)));
            renvoie_message(client_socket_fd, reponse_msg);
        }
        else {
             renvoie_message(client_socket_fd, "{\"reponse\":\"Erreur\",\"details\":\"Code d'opération non reconnu\"}");
        }
    }
    else {
        renvoie_message(client_socket_fd, "{\"reponse\":\"Erreur\",\"details\":\"Format JSON manquant (code/valeurs)\"}");
    }
    
    cJSON_Delete(root);
    return (EXIT_SUCCESS);
}

// Fonction de gestion du signal Ctrl+C
void gestionnaire_ctrl_c(int signal)
{
    (void)signal; // FIX: Indique au compilateur que ce paramètre est intentionnellement ignoré.
    
    printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
    // fermer le socket
    close(socketfd);
    exit(0); // Quitter proprement le programme.
}

int main()
{
    int bind_status;
    struct sockaddr_in server_addr;

    /*
     * Creation d'une socket
     */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Unable to open a socket");
        return -1;
    }

    int option = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // détails du serveur (adresse et port)
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Relier l'adresse à la socket
    bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status < 0)
    {
        perror("bind");
        return (EXIT_FAILURE);
    }

    // Enregistrez la fonction de gestion du signal Ctrl+C
    signal(SIGINT, gestionnaire_ctrl_c);

    printf("Serveur en attente de connexions sur le port %d...\n", PORT);

    // Boucle infinie
    while (1)
    {
        // Écouter les messages envoyés par le client
        listen(socketfd, 10);

        // Lire et répondre au client
        struct sockaddr_in client_addr;
        char data[1024];

        unsigned int client_addr_len = sizeof(client_addr);

        // nouvelle connection de client
        int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket_fd < 0)
        {
            perror("accept");
            // Optionnel: Ajouter le fork() pour gérer plusieurs clients simultanément si le code initial en avait.
            continue; 
        }

        // la réinitialisation de l'ensemble des données
        memset(data, 0, sizeof(data));

        // lecture de données envoyées par un client
        int data_size = read(client_socket_fd, (void *)data, sizeof(data) - 1);
        data[data_size] = '\0'; // Assurer la terminaison de la chaîne

        if (data_size > 0)
        {
            recois_envoie_message(client_socket_fd, data);
        }
        else if (data_size == 0)
        {
            printf("Client déconnecté.\n");
        }
        else
        {
             perror("erreur lecture");
        }
        
        // Fermer la socket client après le traitement
        close(client_socket_fd);
    }

    return 0;
}