/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

/*
 * @brief Fonction pour envoyer et recevoir des messages de type "message: ".
 * @param socketfd : L'identifiant de la socket.
 */
int envoie_recois_message(int socketfd);

/*
 * @brief Nouvelle fonction pour envoyer une requête de calcul au serveur au format "calcule : op num1 num2". (Ex. 5.5)
 * @param socketfd : L'identifiant de la socket.
 * @param op : L'opérateur (+, -, *, /).
 * @param num1 : Le premier nombre.
 * @param num2 : Le second nombre.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_operateur_numeros(int socketfd, char op, int num1, int num2);

#endif