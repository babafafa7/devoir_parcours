#include "parcours_profondeur.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    parcours_profondeur * profondeur;
    unsigned int i,j;
    int* tab;
    /* __ graphe orienté pour le parcours en profondeur */
    graph_mat* g1 = gm_init(8);
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

    /* __parcours en profondeur (version iterative)*/
    profondeur = parcours_profondeur_construire(gm_n(g), 0);
    parcours_en_profondeur_iter(profondeur, g);

    /* __permet de préciser le rang de visite complete de chaque noeud */
    tab = malloc(sizeof(int)*gm_n(g));
    for(i=0; i<gm_n(g);i++){
        for(j=0; j<gm_n(g);j++){
            if((int)i == profondeur->suffixe->tab[j]){
                tab[i]=j+1;
            }
        }
    }

    /*__affichage des sommets de leur rang de visite, rang de visite complete et de leur père */
    printf("*** donnees obtenues pour le parcours (version iterative):\n");
    printf("sommet\tprefixe\tsuffixe\tpere\n");
    for(i = 0; i< gm_n(g); i++){
        printf("%d \t %d \t %d \t %d\n",i,profondeur->parcours->tab[i] + 1,tab[i],profondeur->pere[i]);
    }

    /* __génération du graphe orienté par le le parcours en profondeur (version iterative) */
    for (i=1; i<gm_n(g1);i++){
        gm_add_edge(g1,profondeur->pere[i],i);
    }
   
    gm_write_dot(g1,"parcours_profondeur.dot");
    /* __libération de la mémoire */
    free(tab);
    gm_free(g);
    gm_free(g1);
    detruire_parcours_profondeur(profondeur);

    return 0;
}