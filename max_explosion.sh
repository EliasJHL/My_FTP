#!/bin/bash

# Définir l'hôte et le port cible
HOST="127.0.0.1"  # Remplacez "adresse_ip" par l'adresse IP ou le nom de domaine cible
PORT="4242"        # Remplacez "port" par le port cible

for i in {1..10000}
do
  echo "Connexion Telnet n°$i"
  telnet $HOST $PORT &
done
