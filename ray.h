/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 * ray.h    2er rendu												*
 * 																	*
 * Fichier en-tête de ray.c											*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */

#include "v2d.h"

#ifndef __RAYON_H__
#define __RAYON_H__

/*Fonction principale du module. Tant que l'énergie totale et l'énergie 
 * reservée au tour courrant sont suffisante,s elle calcule le rayon lors 
 * de chaque rebond. Elle renvoie la variation de score. */
int ray_propagate(V2D point_d, V2D vect_u, int player,
				  int total_energy, int ene_tour) ;
				  

//Fonction qui dessine tous les segments du rayon
void ray_trace();

//Fonction qui détruit le rayon
void ray_delete();

//Fonction qui ajoute à la liste une nouvelle structure de type RAY
void ray_create(V2D pt1,V2D pt2);

//Fonction qui verifie qu'un rayon existe
void* ray_exist();

#endif
