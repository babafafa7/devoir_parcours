#include "liste.h"
#include "graph_mat-1.h"



#ifndef PARCOURS_PROFONDEUR_H
#define PARCOURS_PROFONDEUR_H

struct s_parcours_profondeur {
    int d;              /* __sommet départ du parcours */
    liste* parcours;    /* __liste d'ordre de visite des sommets */
    liste* suffixe;     /* __liste d'ordre de sommets totalement exploré */
    liste* pile;
    int* pere;          /* __tableau des pères de chaque sommet dans l'arborescence du parcours */
};

typedef struct s_parcours_profondeur parcours_profondeur;

parcours_profondeur* parcours_profondeur_construire(int taille_listes, int sommet_depart);
void detruire_parcours_profondeur(parcours_profondeur*);
void parcours_en_profondeur_iter(parcours_profondeur*, graph_mat*);
parcours_profondeur* parcours_en_profondeur_rec(graph_mat*, int sommet_depart);

#endif