#include "parcours_profondeur.h"


parcours_profondeur* parcours_profondeur_construire(int taille_listes, int sommet_depart){
    parcours_profondeur* parcours;

    /* __ vérification des paramètres */
	if((taille_listes <= 0) || (sommet_depart <= 0)){
		return NULL;
    }

    /* __ allocation mémoire pour le parcours */
    parcours = (parcours_profondeur*) malloc(sizeof(parcours_profondeur));

    if(parcours != NULL){
        /* __sommet de départ */
        parcours->d = sommet_depart;

        /* __Allocations des listes*/
        parcours->prefixe = liste_construire(taille_listes);
        parcours->suffixe = liste_construire(taille_listes);
        parcours->pere = liste_construire(taille_listes);
        parcours->N = liste_construire(taille_listes);
    }
    return parcours;
}

void detruire_parcours_profondeur(parcours_profondeur* p){
    if(p != NULL){
        /* __ libération de la mémoire allouée pour les listes de la structure */
        liste_detruire(&(p->prefixe));
        liste_detruire(&(p->suffixe));
        liste_detruire(&(p->pere));
        liste_detruire(&(p->N));
    }
    /* __ libération de la mémoire allouée pour la structure elle-même */
	free(p);
}

parcours_profondeur* parcours_en_profondeur_iter(graph_mat* g, int sommet_depart){
    parcours_profondeur* p = parcours_profondeur_construire(gm_n(g), sommet_depart);

    while(!liste_est_pleine(p->prefixe)){
        liste_ajouter_debut(p->suffixe, sommet_depart);
        liste_ajouter_fin(p->prefixe, sommet_depart);
        while(!liste_est_vide(p->suffixe)){
            int* elt = liste_get_debut(p->prefixe);
            int inclus = 0;
            unsigned int j;
            for(j = 0; j < gm_n(g); j++){
                if((g->adj[(*elt)*gm_n(g) + j] == 1) && (liste_contient_element(p->prefixe,j) != 1)){
                    inclus = 1;
                }
            }
            if(inclus){
                liste_supprimer_debut(p->suffixe,j);
                liste_ajouter_fin(p->N, j);
            }
            else{
                for(j = 0; j < gm_n(g); j++){
                    if((g->adj[(*elt)*gm_n(g) + j] == 1) && (liste_contient_element(p->prefixe,j) != 1)){
                        liste_ajouter_debut(p->suffixe, j);
                        liste_ajouter_fin(p->prefixe, j);
                    }
                    
                }
            }  
        }
    }
    return p;
}

parcours_profondeur* parcours_en_profondeur_rec(graph_mat* g , int sommet_depart){
    return NULL;
}