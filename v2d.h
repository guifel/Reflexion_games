/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 * v2d.h    Rendu final												*
 * 																	*
 * Fichier en-tête de v2d.c											*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */

#ifndef __V2D_H__
#define __V2D_H__

typedef struct v2d V2D ;

//Definition de la structure qui contient les données des vecteurs
struct v2d
{
	float x, y ;
} ;

//Fonction qui calcule la norme d'un vecteur
float v2d_norm(V2D vect_v) ;

//fonction qui calcule le produit scalaire entre 2 vecteurs
float v2d_scalar_product (V2D vect_v1, V2D vect_v2) ;

//Fonction qui calcule la norme d'un produit en croix entre 2 vecteurs
float v2d_norm_cross_product (V2D vect_v1, V2D vect_v2) ;

//Fonction qui normalise un vecteur
V2D v2d_vector_normalize(V2D vect_v) ;

#endif
