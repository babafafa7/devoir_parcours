#include "liste.h"
#include "graph_mat-1.h"



#ifndef PARCOURS_PROFONDEUR_H
#define PARCOURS_PROFONDEUR_H

struct s_parcours_profondeur {
    liste* prefixe;     /* __liste d'ordre de visite des sommets */
    liste* suffixe;     /* __liste d'ordre des sommets totalement explorés */
    liste* pile;        /* __pile utile au fonctionnement du parcours en profondeur (version itérative) */
    int* pere;          /* __tableau des pères de chaque sommet dans l'arborescence du parcours */
};

typedef struct s_parcours_profondeur parcours_profondeur;

/* __Cette fonction construit, initialise un parcours_profondeur vide de capacité des listes taille_listes  et de sommet de départ sommet_départ 
    pré-conditions :        sommet_depart > -1
                            taille_listes > 0
    retourne un parcours_profondeur null si echec
*/
parcours_profondeur* parcours_profondeur_construire(int taille_listes, int sommet_depart);

/* __Cette fonction libère la mémoire allouée pour un parcours_profondeur passer en paramètre (et réinitialise à NULL le pointeur *p) */
void detruire_parcours_profondeur(parcours_profondeur* p);

/* __Réalise le parcours en profondeur (version itérative) à l'aide d'un graphe et d'un sommet_depart placés en paramètre.
    pré-conditions :    sommet_depart >-1
                        *g non null 
    retourne un parcours_profondeur null si echec
*/
parcours_profondeur* parcours_en_profondeur_iter(graph_mat* g, int sommet_depart);

/* __Réalise le parcours en profondeur (version récursive) à l'aide d'un graphe, d'un parcours_profondeur null et d'un sommet_depart placés en paramètre.
    pré-conditions :    *p soit null
                        sommet_depart >-1
                        *g non null 
    retourne un parcours_profondeur null si echec
*/
parcours_profondeur* parcours_en_profondeur_rec(graph_mat* g, parcours_profondeur* p, int sommet_depart);

/* Fonction d'entrée-sortie
 * Écrit le graphe orienté d'un parcours_profondeur au format dot dans le fichier de nom filename.
 * retourne une valeur négative en cas d'erreur (fichier non ouvrable en
 * écriture, ...) et 0 sinon. */
int parcours_write_dot(parcours_profondeur* p, const char *filename);

#endif