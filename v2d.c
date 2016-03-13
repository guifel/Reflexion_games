/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 * v2d.c		Rendu final											*
 * 																	*
 * Module de bas niveau qui gère les operations sur les vecteurs 	*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */
 
 
#include <math.h>
#include "v2d.h"


//Fonction qui calcule la norme d'un vecteur

float v2d_norm(V2D vect_v) 
{
	float norm ;
	
	norm = sqrtf(vect_v.x * vect_v.x + vect_v.y * vect_v.y) ;
	
	return norm ;
}


//fonction qui calcule le produit scalaire entre 2 vecteurs

float v2d_scalar_product (V2D vect_v1, V2D vect_v2)
{
	float scalar_product ;
	
	scalar_product = vect_v1.x * vect_v2.x + vect_v1.y * vect_v2.y ;
	
	return scalar_product ;
}


//Fonction qui calcule la norme d'un produit en croix entre 2 vecteurs

float v2d_norm_cross_product (V2D vect_v1, V2D vect_v2)
{
	float cross_product ;
	
	cross_product =  fabs(vect_v1.x * vect_v2.y - vect_v1.y * vect_v2.x);
	
	return cross_product ;
}


//Fonction qui normalise un vecteur

V2D v2d_vector_normalize(V2D vect_v)
{
	float norm = v2d_norm (vect_v) ;
	
	vect_v.x /= norm ;
	vect_v.y /= norm ;
	
	return vect_v ;
}
