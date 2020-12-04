#include "liste.h"
#include "graph_mat-1.h"

#ifndef PARCOURS_LARGEUR_H
#define PARCOURS_LARGEUR_H

struct s_parcours_largeur {
    int d;              //sommet départ du parcours
    liste* prefixe;     //liste d'ordre de visite des sommets
    liste* suffixe;     //liste d'ordre de sommets totalement exploré
    liste* pere;        //liste des pères de chaque sommet dans l'arborescence du parcours 
};

typedef struct s_parcours_largeur parcours_largeur;

parcours_largeur* parcours_largeur_construire(int taille_listes, int sommet_depart);
void detruire_parcours_profondeur(parcours_largeur*);
parcours_largeur* parcours_en_largeur_iter(graph_mat*, int sommet_depart);
parcours_largeur* parcours_en_largeur_rec(graph_mat*, int sommet_depart);

#endif