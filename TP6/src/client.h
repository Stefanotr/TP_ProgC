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
#define MAX_COLORS 30 // Limite définie par l'exercice 6.2

/*
 * @brief Envoie une requête de message simple au format JSON.
 * @param socketfd : L'identifiant de la socket.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_message_simple(int socketfd, const char *msg);

/*
 * @brief Analyse une image BMP, construit une requête JSON avec les N couleurs
 * et l'envoie au serveur. (Ex. 6.2 & 6.3)
 * @param socketfd : L'identifiant de la socket.
 * @param pathname : Chemin vers l'image BMP.
 * @param nbr_couleurs : Nombre de couleurs à analyser (max MAX_COLORS).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_couleurs_json(int socketfd, char *pathname, int nbr_couleurs);

#endif