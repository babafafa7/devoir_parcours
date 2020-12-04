#include <stdio.h>
#include <stdlib.h>
#include "parcours_profondeur.h"


int main(){
    /* __création du graph de test */
    graph_mat* g = gm_init(8);
    gm_add_edge(g, 0, 1);
    gm_add_edge(g, 0, 2);
    gm_add_edge(g, 1, 3);
    gm_add_edge(g, 1, 4);
    gm_add_edge(g, 2, 3);
    gm_add_edge(g, 3, 4);
    gm_add_edge(g, 4, 5);
    gm_add_edge(g, 4, 6);
    gm_add_edge(g, 5, 6);
    gm_add_edge(g, 6, 7);

    /* __affichage matrice d'adjacence du graph test */
    printf("**** graphe de test:\n");
    gm_disp(g);

    /* __libération de la mémoire du graphe de test*/
    gm_free(g);

    return 0;
}