/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#include "cJSON.h" // Nécessaire pour les prototypes JSON

#define PORT 8089

const char *svg_file_path = "pie_chart.svg";

/*
 * @brief Envoie un message (*data) au client (client_socket_fd).
 */
int renvoie_message(int client_socket_fd, char *data);

/*
 * @brief Reçoit le message JSON, l'analyse et appelle la fonction appropriée. (Ex. 6.3)
 */
int recois_envoie_message(int client_socket_fd, char data[1024]);

/*
 * @brief Génère le graphique SVG en utilisant les couleurs du tableau JSON et lance Firefox. (Ex. 6.1, 6.2, 6.3)
 */
int plot_json(cJSON *couleurs_array);

#endif