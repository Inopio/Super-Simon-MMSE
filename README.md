# Super-Simon-MMSE
Projet Super Simon réseau MMSE

# Architecture
Nous avons décidé d'utiliser plusieurs fichiers:
    - un ficher client.py qui permet de gérer le client (les joueurs)
    - un fichier server.py qui permet de centraliser le jeu entre les joueurs
    - un fichier simon.ino dans le répertoire simon qui implémente les actions utilisées par l'arduino

# Principe
Le jeu se joue avec 4 joueurs.

Lorsqu'on lance le jeu une fenêtre apparaît.Avant qu'une partie commence le joueur doit cliquer sur le bouton rejoindre la partie. Une fois qu'il a été ajouté sur le serveur, le joueur obtient alors son numéro ainsi que sa couleur qui sera liée à une action qu'il devra effectuer:
    - Joueur 1: mettre un obstacle devant le capteur ultrason
    - Joueur 2: fermer un interrupteur
    - Joueur 3: actionner un bouton poussoir
    - Joueur 4: cacher le capteur photosensible pour qu'il ne soit pas éclairé

Dans un premier temps un servomoteur choisi une séquence aléatoire à jouer en pointant sur la couleur du joueur qui doit effectuer l'action.
Les joueurs doivent répéter la séquence qui a été créée par le servomoteur avec les actions qui leur ont été attribuées.
Chacune des actions doit être effectuée dans un délai de 10 secondes sinon le coup est considéré comme mauvais.

Un écran LCD affiche un message pour commencer le jeu. Durant la partie le score est affiché sur cet écran et à la fin de la partie un message nous indique si on a gagné ou perdu.
