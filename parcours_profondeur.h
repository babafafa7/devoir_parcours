#include "liste.h"
#include "graph_mat-1.h"
#include <stdlib.h>


#ifndef PARCOURS_PROFONDEUR_H
#define PARCOURS_PROFONDEUR_H

struct s_parcours_profondeur {
    int d;              /* __sommet départ du parcours */
    liste** prefixe;    /* __liste d'ordre de visite des sommets */
    liste** suffixe;    /* __liste d'ordre de sommets totalement exploré */
    liste** pere;       /* __liste des pères de chaque sommet dans l'arborescence du parcours */ 
};

typedef struct s_parcours_profondeur parcours_profondeur;

parcours_profondeur* parcours_profondeur_construire(int taille_listes, int sommet_depart);
void detruire_parcours_profondeur(parcours_profondeur*);
parcours_profondeur* parcours_en_profondeur_iter(graph_mat*, int sommet_depart);
parcours_profondeur* parcours_en_profondeur_rec(graph_mat*, int sommet_depart);
void afficher_listes(parcours_profondeur*);

#endif