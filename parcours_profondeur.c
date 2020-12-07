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
        /* __Allocations des listes*/
        parcours->prefixe = liste_construire(taille_listes);
        parcours->pile = liste_construire(taille_listes);
        parcours->suffixe = liste_construire(taille_listes);

        /* __Allocations du tableau des peres */
        parcours->pere = malloc(sizeof(int)*taille_listes);

        /* __initialisation du pere du sommet de départ */
        parcours->pere[sommet_depart] = -1;
    }
    return parcours;
}

void detruire_parcours_profondeur(parcours_profondeur* p){
    if(p != NULL){
        /* __ libération de la mémoire allouée pour les listes de la structure */
        liste_detruire(&(p->prefixe));
        liste_detruire(&(p->pile));
        liste_detruire(&(p->suffixe));
        free(p->pere);
        
    }
    /* __ libération de la mémoire allouée pour la structure elle-même */
	free(p);
}

parcours_profondeur* parcours_en_profondeur_iter(graph_mat * g , int sommet_depart){
    parcours_profondeur* p = parcours_profondeur_construire(gm_n(g), sommet_depart);
    liste_ajouter_debut(p->pile, sommet_depart);        /* __On place le sommet de depart dans la pile */
    liste_ajouter_fin(p->prefixe, sommet_depart);       /* __et on le marque comme visité (on le place dans la liste prefixe) */
    while(!liste_est_vide(p->pile)){                    /* __Tant que la pile n'est pas vide */
        int* elt = liste_get_debut(p->pile);            /* __On prend element au sommet de la pile */
        int brk = 1;
        unsigned int j;
        for(j = 0; j < gm_n(g); j++){                   /* __On cherche s'il a des fils non visités */
            if(((gm_mult_edge(g,(*elt),j)) >= 1) && (liste_contient_element(p->prefixe,j) != 1)){ 
                brk = 0;
                liste_ajouter_debut(p->pile, j);        /* __Si oui on place le fils en tete de pile */ 
                liste_ajouter_fin(p->prefixe, j);       /* __et on le marque comme visité (on le place dans la liste prefixe) */
                p->pere[j] = (*elt);                    /* __puis on marque le pere de fils */
                break;
            }
        }
        if(brk){                                        /* __Sinon */
            liste_supprimer_debut(p->pile,elt);         /* __On dépile la pile */
            liste_ajouter_fin(p->suffixe, (*elt));      /* __On le marque comme totalement visité (place dans la liste suffixe)*/
        } 
    }
    return p;
}

parcours_profondeur* parcours_en_profondeur_rec(graph_mat* g, parcours_profondeur* p, int sommet_depart){
    int brk, *elt;
    unsigned int j;
    if(p == NULL){
        p = parcours_profondeur_construire(gm_n(g), sommet_depart);
    }
    if(sommet_depart != -1){                                        /* __Si le sommet de départ est le sommet -1 on ne fait rien */
        liste_ajouter_fin(p->prefixe, sommet_depart);               /* __Sinon on le marque comme visité (on le place dans la liste prefixe */
        elt = &(sommet_depart);
        brk = 1;
        for(j = 0; j < gm_n(g); j++){                               /* __On cherche s'il a des fils non visités */
            if(((gm_mult_edge(g,*elt,j)) >= 1) && (liste_contient_element(p->prefixe,j) != 1)){
                brk = 0;                            
                p->pere[j] = sommet_depart;                         /* __Si oui on marque le pere du fils */
                sommet_depart = j;                                  /* __puis on marque le fils comme sommet de depart */
                p = parcours_en_profondeur_rec(g, p, sommet_depart);/* __On appelle la fonction recursivement avec le nouveau sommet de départ */
                break;
            }
        }
        if(brk){
            liste_ajouter_fin(p->suffixe, *elt);                    /* __Sinon on le marque comme totalement visité (place dans la liste suffixe) */
            sommet_depart = p->pere[*elt];                          /* __On marque son pere comme nouveau sommet de depart */
            p = parcours_en_profondeur_rec(g, p, sommet_depart);    /* __Puis on appelle la fonction recursivement avec le nouveau sommet de départ */
        }   
    }
    return p;
}

int parcours_write_dot(parcours_profondeur* p, const char *filename){
	FILE *f;
	int v;

	f = fopen(filename, "w");
	if (f == NULL) {
		perror("fopen in parcours_write_dot");
		return -1;
	}

	fprintf(f, "digraph {\n");
	for(v=0; v<liste_get_n(p->prefixe);v++){
        fprintf(f, "\t%d;\n", v);
    }
		

	fprintf(f, "\n");
    
	for(v =1; v< liste_get_n(p->prefixe); v++){
        fprintf(f, "\t%d -> %d;\n", p->pere[v], v);
    }
        
	fprintf(f, "}\n");
	fclose(f);	
	return 0;
}
