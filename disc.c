/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  disc.c    2ème rendu											*
 * 																	*
 * 	Module contenant destiné a gérer tout ce qui concerne les		*
 * 	disques, de type opaque. Ce module contient toutes les 			*
 * informations des disques, gardées dans une liste chainée			*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour :  17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tolerance.h"
#include "constante.h"
#include "v2d.h"
#include "graphic.h"
#include "disc.h"


// Structure pour la liste chainée

typedef struct disc DISC ;

struct disc 
{
	float cx, cy, value ;
	unsigned int player_id, disc_id, temp_destr ;
	DISC * next ;
};

// Pointeur de tête 

static DISC* first  = NULL;


// Fonction pour la création des disques dans la liste chainée

void disc_creation(float cx, float cy, float value, 
				   unsigned int player_id, unsigned int disc_id)
{
	DISC *new;
	if (!(new = (DISC*) malloc(sizeof(DISC))))
		printf("Erreur d'alocation") ; 
		
	new -> cx = cx ;
	new -> cy = cy ;
	new -> value = value ;
	new -> player_id = player_id ;
	new -> disc_id = disc_id ;
	new -> next = first ;
	new -> temp_destr = 0 ; 
	
	first = new ;	
}


// Fonction pour la destruction de tous les disques

void disc_destruction_all()
{
	DISC *scan = first, *previous = NULL ;
	
	while(scan)
	{
		previous = scan ;
		scan = scan -> next ;
		free(previous) ;
	}
	
	first = NULL ;
}


/* Fonction pour la destruction des disques à l'oeuvre du rayon et calcul
 * du score */

int disc_destruction(int current_player, int * player1_nbdisc_var, 
					 int * player2_nbdisc_var)
{
	
	DISC * scan = first, * previous = NULL ; 
	int energy_var = 0 ;
	
	while(scan) 
	{
		if (scan->temp_destr) //si le disque est tapé par le rayon
		{
			energy_var = energy_var + scan->value ;
			
			if(scan->player_id == PLAYER_1)
				* player1_nbdisc_var = *player1_nbdisc_var + 1 ;
			else
				* player2_nbdisc_var = *player2_nbdisc_var + 1 ;
			
			if(scan == first)
				first = first->next ;
			else
				previous -> next = scan -> next ;			
		
			free(scan) ;
		}
		else
		previous = scan ;
		
		scan = scan -> next ;
	}
	
	return energy_var ;
}


// Dessin de tous les disques 

void disc_drawing()
 {
	DISC * draw = first ;
	
	while(draw)
	{	
		
		if(draw->player_id == PLAYER_2)
		{
			if (draw->temp_destr == 1)
				graphic_set_color3f(PLAYER2_R, PLAYER2_V+0.2, PLAYER2_B+0.2) ;

			else
				graphic_set_color3f(PLAYER2_R, PLAYER2_V, PLAYER2_B) ;
		}
		
		
		if(draw->player_id == PLAYER_1)
		{
			if (draw->temp_destr == 1)
				graphic_set_color3f(PLAYER1_R+0.2, PLAYER1_V+0.2, PLAYER1_B+0.2) ;
				
			else
				graphic_set_color3f(PLAYER1_R, PLAYER1_V, PLAYER1_B) ;
		}
			
		graphic_draw_circle(draw->cx,draw->cy,draw->value*MIN_RADIUS) ;
		
		draw = draw -> next ;
	}
 }
 

/* Fonciton qui calcule la distance entre le centre du disque et le 
 * point de départ du vecteur rayon */

static float disc_distance (V2D point_d, V2D vect_u, DISC * check)
{
	float radius = check->value * MIN_RADIUS ;
	float norm_v, scalar_p ;
	V2D DC ; 
	
	DC.x = check->cx - point_d.x ; 
	DC.y = check->cy - point_d.y ;
	
	scalar_p = v2d_scalar_product(vect_u, DC) ;
	
	if (scalar_p > 0)
	{
		norm_v = v2d_norm_cross_product(vect_u, DC) ;
		
		if(norm_v <= radius + TOLERANCE) 
			return scalar_p - sqrtf(radius*radius - norm_v*norm_v) ;
	}
	
	 return (float)(-1) ;
}
 

/* Fonction qui renvoie les coordonnées du disque le plus proche 
 * intersecté.  De plus elle précalcule la variation de score et 
 * change l'état du disque à temporairement détruit */

V2D disc_intersected(V2D point_d, V2D vect_u, int player, float * distance, 
	int * spent_energy, int * score_var, int ene_tour, int total_energy )
{
	DISC * check = first ;
	DISC * closer = first ;
	V2D point_c = {0, 0} ;
	float temp_dist ;

	*distance = MAX_MODELE ;

	//recherche du disque le plus proche touché par le rayon
	
	while(check)  
	{
		if (check->temp_destr == 0)
		{
			temp_dist = disc_distance (point_d, vect_u, check) ;
			
			if (temp_dist != -1 && temp_dist < * distance)
			{
				closer = check ;
				* distance  = temp_dist ;
			}
		}
		check = check -> next;
	}
	
	if (*distance == MAX_MODELE)
	{
		point_c.x = point_d.x + vect_u.x * MAX_MODELE * 2;
		point_c.y = point_d.y + vect_u.y * MAX_MODELE * 2;
		
	}
	else
	{
		point_c.x = closer->cx ;
		point_c.y = closer->cy ;
		
		* spent_energy += closer->value ;
		
		if (* spent_energy <= ene_tour && * spent_energy <= total_energy)
		{
			if (closer->player_id != player)
				* score_var += closer->value  ;
			else 
				* score_var -= closer->value  ;
			
			closer->temp_destr = 1 ;
		}
	}
	
	return  point_c;
}


//Fonction qui remet l'état de tous les disques a sa valeur initiale

void disc_state_reset()
{
	DISC * scan = first ;
	
	while(scan)
	{
		scan->temp_destr = 0 ;
		scan = scan -> next ;
	}
}


/* Detectection de l'erreur ou des disques s'intersectent
 * (utilisé que dans "disc_are_in_contact") */

static int disc_intersect (DISC disc_1, DISC disc_2)
{
	
	float distance, radius_sum ;
	
	distance = sqrt(pow((disc_1.cx - disc_2.cx), 2) 
			   + pow((disc_1.cy - disc_2.cy), 2)) ;
	
	radius_sum = (disc_1.value + disc_2.value) * MIN_RADIUS ;
	
	if (radius_sum + TOLERANCE >= distance) return 1 ;
	else return 0 ;
	
}


// Detection de l'erreur ou des disques seraient en dehors des limites du jeu

int disc_out_of_boundaries(int n_player)
{	
	DISC* scan = first ;	
	
	while(scan)
	{
		if (scan->player_id == n_player)
		{
			
			if ( (scan->cx + scan->value * MIN_RADIUS > MAX_MODELE)
			  || (scan->cy - scan->value * MIN_RADIUS < 0)
			  || (scan->cx + scan->value * MIN_RADIUS > MAX_MODELE)
			  || (scan->cy - scan->value * MIN_RADIUS < 0) )
				return scan->disc_id ;
		}
		scan = scan -> next ;
	}
	
	return -1 ;
}


// Dectection de l'erreur ou des disques se touchent

int disc_are_in_contact (int players_n_discs[2][2])
{
	DISC* scan = first ; 
	DISC* other = NULL ;
	
	while (scan)
	{
		other = scan->next ;
		
		while (other)
		{
			
			if (disc_intersect(* scan, * other))
			{
				players_n_discs [0][0] = scan->player_id ;
				players_n_discs [0][1] = scan->disc_id ;
				players_n_discs [1][0] = other->player_id ;
				players_n_discs [1][1] = other->disc_id ;
				
				return 1 ;
			}
			else 
				other = other->next ;
		}
		
		scan = scan->next ;
	}
	
	return 0 ;
}

// Imprime les disques dans un fichier
		
void disc_print(int player_id, FILE * fichier)
{
	
	DISC *printing = first ;
	
	while (printing)
	{
		if (printing->player_id == player_id)
			fprintf (fichier, "%.4f %.4f %.4f\n", printing->cx, 
					 printing->cy, printing->value);
					 
		printing = printing->next ;
	}
	
	fprintf (fichier, "\n\n") ;
}


/*Fonction qui verifie que le point de départ du rayon ne soit pas 
 * à l'interieur d'un disque*/

int disc_cursor_on_disc(V2D point_d)
{
	DISC * scan = first; 
	V2D dist ;
	
	while(scan)
	{
		
		dist.x = scan->cx - point_d.x ;
		dist.y = scan->cy - point_d.y ;
		
		if(v2d_norm(dist) <= scan->value * MIN_RADIUS)
		{
		
			return 0 ;
		}
		
		scan = scan -> next ;
	}
	return 1 ;
}


/*Fonction qui verifie qu'un joueur puisse détruire les disques de
 * son adversaire */

int disc_can_destroy(int player, int ene)
{
	DISC *scan = first ;
	
	while(scan)
	{	
		if (scan->player_id != player && scan->value <= (float)ene + 0.5)
			return 1 ;
		
		scan = scan->next ;	
	}
	
	return 0 ;
}
