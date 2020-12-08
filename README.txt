Bastien FALCHERO 11804029 Groupe 2	
Jayson SAINTE-ROSE 11714079 Groupe 1

Dans le but de ce devoir nous avons réalisé un programme capable d'appliquer de deux manières différentes ;
itérative et récursive, l'agorithme du parcours en profondeurs.
Pour cela nous avons utilisé les bibliothèques; graph_mat-1.h, liste.h.
A la suite de l'éxécution de ce programme des fichiers ".dot" seront créés contenant les graphes orientés représente le parcours.
Il y aura un graphe orienté par méthode.

Contenu de l'archive :
-Makefile
-graph_mat.c
-graph_mat.h
-liste.c
-liste.h
-main.c
-parcours_profondeur.c
-parcours_profondeur.h

Afin de compiler il est nécéssaire d'entrer la commande "make" dans le terminal.
Une fois compiler il suffite d'enter la commande "./parcours_profondeurs" pour lancer l'éxécution.
Enfin afin de visualiser les graphes orientés les commandes correspondants à chaque méthodes sont les suivantes :
-dot -Tx11 parcours_profondeurs_iter.dot -- pour la version itérative
-dot -Tx11 parcours_profondeurs_rec.dot -- pour la version récursive