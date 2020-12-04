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
    }
     return parcours;
}

void detruire_parcours_profondeur(parcours_profondeur* p){
    if(p != NULL){
       /* __ libération de la mémoire allouée pour les listes de la structure */
       if(p->prefixe != NULL){
           liste_detruire(p->prefixe);
           liste_detruire(p->suffixe);
           liste_detruire(p->pere);
       }
    }
    /* __ libération de la mémoire allouée pour la structure elle-même */
	free(p);
}

parcours_profondeur* parcours_en_profondeur_iter(graph_mat*, int sommet_depart){
    
}

parcours_profondeur* parcours_en_profondeur_iter(graph_mat*, int sommet_depart){
    
}

void afficher_listes(parcours_profondeur*){

}