#include "parcours_profondeur.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    parcours_profondeur *profondeur_iter, *profondeur_rec = NULL;
    unsigned int i;

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

    /* __parcours en profondeur_iter (version iterative)*/
    profondeur_iter = parcours_en_profondeur_iter(g, 0);
    
    /*__affichage des sommets de leur rang de visite, rang de visite complete et de leur père */
    printf("*** donnees obtenues pour le parcours (version iterative):\n");
    printf("sommet\tprefixe\tsuffixe\tpere\n");
    for(i = 0; i< gm_n(g); i++){
        printf("%d \t %d \t %d \t %d\n",i,profondeur_iter->prefixe->tab[i] + 1,profondeur_iter->suffixe->pos[i] +1,profondeur_iter->pere[i]);
    }

    /* __crée le fichier parcours_profondeur_iter.dot contenant le graphe orienté du parcours en profondeur_iter */
    parcours_write_dot(profondeur_iter,"parcours_profondeur_iter.dot");

    /* __parcours en profondeur (version récursive)*/
    profondeur_rec = parcours_en_profondeur_rec(g, profondeur_rec, 0);

    /*__affichage des sommets de leur rang de visite, rang de visite complete et de leur père */
    printf("\n*** donnees obtenues pour le parcours (version récursive):\n");
    printf("sommet\tprefixe\tsuffixe\tpere\n");
    for(i = 0; i< gm_n(g); i++){
        printf("%d \t %d \t %d \t %d\n",i,profondeur_rec->prefixe->tab[i] + 1,profondeur_rec->suffixe->pos[i] +1,profondeur_rec->pere[i]);
    }

    /* __crée le fichier parcours_profondeur_rec.dot contenant le graphe orienté du parcours en profondeur_rec */
    parcours_write_dot(profondeur_rec,"parcours_profondeur_rec.dot");

    /* __libération de la mémoire */
    gm_free(g);
    detruire_parcours_profondeur(profondeur_iter);
    detruire_parcours_profondeur(profondeur_rec);

    return 0;
}