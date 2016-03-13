/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  disc.h   2eme rendu												*
 * 																	*
 * 	Fichier header du module disc									*
 *																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 234732, 237672											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */


#ifndef __disc_H__
#define __disc_H__

#include "v2d.h"
#include "stdio.h"

// Fonction pour la création des disques dans la liste chainée
void disc_creation(float cx, float cy, float value, 
				   unsigned int player_id, unsigned int disc_id) ;

/* Fonction pour la destruction des disques à l'oeuvre du rayon et calcul
 * du score */
int disc_destruction(int current_player, int * player1_nbdisc_var, int * player2_nbdisc_var) ;

// Fonction pour la destruction de tous les disques
void disc_destruction_all() ;

/* Fonction qui renvoie les coordonnées du disque le plus proche 
 * intersecté.  De plus elle précalcule la variation de score et 
 * change l'état du disque à temporairement détruit */
V2D disc_intersected(V2D point_d, V2D vect_u, int player, float * distance, 
	int * spent_energy, int *score_var , int ene_tour, int total_energy ) ;

//Fonction qui remet l'état de tous les disques à sa valeur initiale
void disc_state_reset() ;

// Dessin de tous les disques 
void disc_drawing() ;

// Detection de l'erreur ou des disques seraient en dehors des limites du jeu
int disc_out_of_boundaries(int n_player) ;

// Dectecte l'erreur ou des disques se touchent
int disc_are_in_contact (int players_n_discs[2][2]) ;

// Imprime les disques dans un fichier
void disc_print(int player_id, FILE * fichier) ;

/*Fonction qui verifie que le point de départ du rayon ne soit pas
 * à l'interieur d'un disque */
int disc_cursor_on_disc(V2D point_d);

/*Fonction qui verifie qu'un joueur puisse détruire les disques de
 * son adversaire */
int disc_can_destroy(int player, int ene) ;

#endif
