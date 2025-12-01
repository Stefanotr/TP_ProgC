# Fichiers objets requis par le client (inclut cJSON.o)
COBJS ?= client.o bmp.o couleur.o cJSON.o
# Fichiers objets requis par le serveur (inclut cJSON.o)
SOBJS ?= serveur.o cJSON.o 

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

# Cible par défaut: compile tout
all: $(SERVER) $(CLIENT)

# Règle pour le SERVEUR : Lit serveur.o et cJSON.o et crée l'exécutable
# La ligne '-lm' est conservée pour la fonction mathématique (cos, sin) dans serveur.c
$(SERVER): $(SOBJS)
	gcc -o $(SERVER) $(SOBJS) -lm

# Règle pour le CLIENT : Lit client.o, bmp.o, couleur.o et cJSON.o et crée l'exécutable
$(CLIENT): $(COBJS)
	gcc -o $(CLIENT) $(COBJS)

# Règle générique de compilation : crée les fichiers .o à partir des fichiers .c
.c.o: 
	gcc -Wall -Werror -ggdb3 -c $*.c

# --- NOUVELLES RÈGLES AJOUTÉES ---

# Règle pour nettoyer les fichiers générés (exécutables et objets)
clean:
	rm -f *.o $(SERVER) $(CLIENT)

