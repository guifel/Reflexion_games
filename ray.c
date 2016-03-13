/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 * ray.c		2eme rendu											*
 * 																	*
 * Module qui gère la réflection du rayon sur les disques et toutes *
 * les autres operations liées à sa propagation.	 				*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 13/03/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */

#include <stdlib.h>
#include "graphic.h"
#include "tolerance.h"
#include "constante.h"
#include "v2d.h"
#include "disc.h"
#include "ray.h"

//structure du type RAY

typedef struct ray RAY ;	
struct ray
{
	V2D pt1, pt2;
	RAY *next;
};

//Tête de liste

RAY *first = 0;


//Fonction qui calcule le vecteur réflechi lors du rebond sur un disque

static V2D ray_reflected (V2D vect_u, V2D point_i, V2D point_c)
{
	V2D vect_n = {point_i.x - point_c.x, point_i.y - point_c.y} ; //vecteur normal
	V2D vect_w ; //vecteur réflechi
	
	vect_n = v2d_vector_normalize(vect_n) ;
	
	vect_w.x = vect_u.x - 2*v2d_scalar_product(vect_u, vect_n)*vect_n.x ;
	vect_w.y = vect_u.y - 2*v2d_scalar_product(vect_u, vect_n)*vect_n.y ;
	
	return vect_w ;
}


/*Fonction principale du module. Tant le l'énergie totale et l'énergie 
 * reservée au tour courrant est suffisante, elle calcule le rayon lors 
 * de chaque rebond. Elle renvoie la variation de score. */

int ray_propagate(V2D point_d, V2D vect_u, int player, int total_energy, int ene_tour) 
{ 
	
	int spent_energy = 0, score_var = 0 ;
	float distance = MAX_MODELE ;
	V2D point_c, point_i ;
	disc_state_reset() ;
	
	ray_delete();
	
	while (spent_energy < ene_tour && spent_energy < total_energy)
	{
		
		point_c = disc_intersected(point_d, vect_u, player,
		&distance, &spent_energy, &score_var, total_energy, ene_tour) ;

		if (distance == MAX_MODELE)
		{
			ray_create(point_d,point_c);
			return score_var ;
		}
		
		//calcul du point d'intersection sur la circonference du disque
		
		point_i.x = point_d.x + vect_u.x * distance ;
		point_i.y = point_d.y + vect_u.y * distance ;
		
		//calcul du nouveau vecteur directeur
		
		vect_u = ray_reflected(vect_u, point_i, point_c) ;
		
		ray_create(point_d,point_i);
		
		point_d.x = point_i.x ;
		point_d.y = point_i.y ;
	}
	
	return score_var ;		
}


//Fonction qui dessine tous les segments du rayon

void ray_trace()
{
	RAY *draw = first ;
	
	graphic_set_color3f(0.2,0,1) ;
	graphic_set_line_width(3) ;
	
	while(draw)
	{
		graphic_draw_segment(draw->pt1.x, draw->pt1.y, 
							 draw->pt2.x ,draw->pt2.y) ;
							 
		draw = draw->next ;
	}
}


//Fonction qui détruit le rayon

void ray_delete()
{
	RAY *scan = first, *previous = NULL ;
	
	while(scan)
	{
		previous = scan ;
		scan = scan -> next ;
		free(previous) ;
	}
	
	first = NULL ;
}


//Fonction qui ajoute à la liste une nouvelle structure de type RAY

void ray_create(V2D pt1, V2D pt2)
{
	RAY *new;
	
	if (!(new = (RAY*) malloc(sizeof(RAY))))
		printf("Erreur d'alocation");
		
	new -> pt1 = pt1;
	new -> pt2 = pt2;
	new -> next = first ;
	first = new;
}


//Fonction qui verifie qu'au moin un rayon existe

void* ray_exist()
{
	return first;
}


	
	
	
	
	
	
