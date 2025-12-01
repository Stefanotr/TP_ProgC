/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

/*
 * @brief Envoie un message (*data) au client (client_socket_fd).
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message à envoyer.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int renvoie_message(int client_socket_fd, char *data);

/*
 * @brief Lit les données envoyées par le client, et renvoie un message en réponse.
 * (MODIFIÉ pour gérer la réponse manuelle et les requêtes de calcul).
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_envoie_message(int client_socket_fd, char *data);

/*
 * @brief Effectue l'opération arithmétique simple demandée. (Ex. 5.5)
 * @param num1 Le premier opérande.
 * @param num2 Le second opérande.
 * @param op L'opérateur (+, -, *, /).
 * @return Le résultat du calcul.
 */
int effectuer_calcul(int num1, int num2, char op);

/*
 * @brief Traite les messages de calcul envoyés par le client. (Ex. 5.5 & 5.6)
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param message : Le message reçu du client contenant l'opération.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_numeros_calcule(int client_socket_fd, const char *message);

#endif // __SERVER_H__