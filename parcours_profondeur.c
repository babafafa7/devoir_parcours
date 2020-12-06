#include "parcours_profondeur.h"
#include "graph_mat-1.h"
#include "liste.h"
#include <stdlib.h>
#include <stdio.h>


parcours_profondeur* parcours_profondeur_construire(int taille_listes, int sommet_depart){
    parcours_profondeur* parcours;
    
    /* __ vérification des paramètres */
	if((taille_listes <= 0) || (sommet_depart < 0)){
		return NULL;
    }

    /* __ allocation mémoire pour le parcours */
    parcours = (parcours_profondeur*) malloc(sizeof(parcours_profondeur));

    if(parcours != NULL){
        /* __sommet de départ */
        parcours->d = sommet_depart;

        /* __Allocations des listes*/
        parcours->parcours = liste_construire(taille_listes);
        parcours->pile = liste_construire(taille_listes);
        parcours->suffixe = liste_construire(taille_listes);
        parcours->pere = malloc(sizeof(int)*taille_listes);

        /* __initialisation du pere du sommet de départ */
        parcours->pere[0] =-1;
    }
    return parcours;
}

void detruire_parcours_profondeur(parcours_profondeur* p){
    if(p != NULL){
        /* __ libération de la mémoire allouée pour les listes de la structure */
        liste_detruire(&(p->parcours));
        liste_detruire(&(p->pile));
        liste_detruire(&(p->suffixe));
        free(p->pere);
        
    }
    /* __ libération de la mémoire allouée pour la structure elle-même */
	free(p);
}

void parcours_en_profondeur_iter(parcours_profondeur* p, graph_mat * g){

    while(!liste_est_pleine(p->parcours)){
        liste_ajouter_debut(p->pile, p->d);
        liste_ajouter_fin(p->parcours, p->d );
        while(!liste_est_vide(p->pile)){
            int* elt = liste_get_debut(p->pile);
            int brk = 1;
            unsigned int j;
            for(j = 0; j < gm_n(g); j++){
                if(((gm_mult_edge(g,(*elt),j)) >= 1) && (liste_contient_element(p->parcours,j) != 1)){
                    brk = 0;
                    liste_ajouter_debut(p->pile, j);
                    liste_ajouter_fin(p->parcours, j);
                    p->pere[j] = (*elt);
                    break;
                }
            }
            if(brk){
                liste_supprimer_debut(p->pile,elt);
                liste_ajouter_fin(p->suffixe, (*elt));
            } 
        }
    }
}

void parcours_en_profondeur_rec(parcours_profondeur* p, graph_mat* g){
    int brk, *elt;
    unsigned int j;
    if(p->d != -1){
        liste_ajouter_fin(p->parcours, p->d);
        elt = &(p->d);
        brk = 1;
        for(j = 0; j < gm_n(g); j++){
            if(((gm_mult_edge(g,*elt,j)) >= 1) && (liste_contient_element(p->parcours,j) != 1)){
                brk = 0;
                p->pere[j] = p->d;
                p->d = j;
                parcours_en_profondeur_rec(p, g);
                break;
            }
        }
        if(brk){
            liste_ajouter_fin(p->suffixe, *elt);
            p->d = p->pere[*elt];
            parcours_en_profondeur_rec(p, g);
        }
    }
}

int parcours_write_dot(parcours_profondeur* p, const char *filename)
{
	/* début solution */
	FILE *f;
	int v;

	f = fopen(filename, "w");
	if (f == NULL) {
		perror("fopen in parcours_write_dot");
		return -1;
	}

	fprintf(f, "digraph {\n");
	for(v=0; v<liste_get_n(p->parcours);v++){
        fprintf(f, "\t%d;\n", v);
    }
		

	fprintf(f, "\n");
    
	for(v =1; v< liste_get_n(p->parcours); v++){
        fprintf(f, "\t%d -> %d;\n", p->pere[v], v);
    }
        
	fprintf(f, "}\n");
	fclose(f);
	/* fin solution */
	return 0;
}
