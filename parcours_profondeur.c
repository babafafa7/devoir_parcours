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

        /* __Allocations du tableau des peres */
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

    liste_ajouter_debut(p->pile, p->d);                 /* __On place le sommet de depart dans la pile */
    liste_ajouter_fin(p->parcours, p->d );              /* __et on le marque comme visité (on le place dans la liste parcours) */
    while(!liste_est_vide(p->pile)){                    /* __Tant que la pile n'est pas vide */
        int* elt = liste_get_debut(p->pile);            /* __On prend element au sommet de la pile */
        int brk = 1;
        unsigned int j;
        for(j = 0; j < gm_n(g); j++){                   /* __On cherche s'il a des fils non visités */
            if(((gm_mult_edge(g,(*elt),j)) >= 1) && (liste_contient_element(p->parcours,j) != 1)){ 
                brk = 0;
                liste_ajouter_debut(p->pile, j);        /* __Si oui on place le fils en tete de pile */ 
                liste_ajouter_fin(p->parcours, j);      /* __et on le marque comme visité (on le place dans la liste parcours) */
                p->pere[j] = (*elt);                    /* __puis on marque le pere de fils */
                break;
            }
        }
        if(brk){                                        /* __Sinon */
            liste_supprimer_debut(p->pile,elt);         /* __On dépile la pile */
            liste_ajouter_fin(p->suffixe, (*elt));      /* __On le marque comme totalement visité (place dans la liste suffixe)*/
        } 
    }
}

void parcours_en_profondeur_rec(parcours_profondeur* p, graph_mat* g){
    int brk, *elt;
    unsigned int j;
    if(p->d != -1){                                 /* __Si le sommet de départ est le sommet -1 on ne fait rien */
        liste_ajouter_fin(p->parcours, p->d);       /* __Sinon on le marque comme visité (on le place dans la liste parcours */
        elt = &(p->d);
        brk = 1;
        for(j = 0; j < gm_n(g); j++){               /* __On cherche s'il a des fils non visités */
            if(((gm_mult_edge(g,*elt,j)) >= 1) && (liste_contient_element(p->parcours,j) != 1)){
                brk = 0;                            
                p->pere[j] = p->d;                  /* __Si oui on marque le pere du fils */
                p->d = j;                           /* __puis on marque le fils comme sommet de depart */
                parcours_en_profondeur_rec(p, g);   /* __On appelle la fonction recursivement avec le nouveau sommet de départ */
                break;
            }
        }
        if(brk){
            liste_ajouter_fin(p->suffixe, *elt);    /* __Sinon on le marque comme totalement visité (place dans la liste suffixe) */
            p->d = p->pere[*elt];                   /* __On marque son pere comme nouveau sommet de depart */
            parcours_en_profondeur_rec(p, g);       /* __Puis on appelle la fonction recursivement avec le nouveau sommet de départ */
        }   
    }
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
	for(v=0; v<liste_get_n(p->parcours);v++){
        fprintf(f, "\t%d;\n", v);
    }
		

	fprintf(f, "\n");
    
	for(v =1; v< liste_get_n(p->parcours); v++){
        fprintf(f, "\t%d -> %d;\n", p->pere[v], v);
    }
        
	fprintf(f, "}\n");
	fclose(f);	
	return 0;
}

void suffixe(parcours_profondeur* p, int* tab){
    int i,j;
    for(i=0; i< p->suffixe->n;i++){
        for(j=0; j< p->suffixe->n;j++){
            if((int)i == p->suffixe->tab[j]){
                tab[i]=j+1;
                break;
            }
        }
    }
}
