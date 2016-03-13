/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  jeu.h    rendu final											*
 * 																	*
 * 	Fichier en-tête de jeu.c										*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 13/03/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */
 
#ifndef __JEU_H__
#define __JEU_H__
 
 #include "v2d.h"
 
/*Fonction chargée de lire les données qui concernent les joueurs et les
 * disques dans un fichier texte et de verifier les erreurs*/
int jeu_reading (const char * nom_fichier) ;

/*Fonction chargée de sauvegarder l'état du jeu en imprimant les 
 * données dans un fichier txt */
void jeu_saving (const char * nom_fichier) ;

// Fonction de dessin des disques
void jeu_drawing();


/*Fonctions chargées de récuperer les informations des joueurs pour les
 * afficher*/
 
char* jeu_get_player_name (int player);

int jeu_get_player_energy (int player);

int jeu_get_player_score (int player);

int jeu_get_player_nbdisc (int player);

//Fonction qui détecte si le le point_d est sur un disque ou non 
int jeu_cursor_on_disc(V2D point_d);

//Fonctions qui valide le tour du joueur 
void jeu_ray_validation(int scor_var);

//Fonction qui calcul la propagation du rayon
int jeu_ray_propagate(V2D point_d, V2D vect_u, int ene1, int ene2);

//Fonctions servants d'intermédiaires entre le module ray et main

//Fonction qui dessine les rayons
void jeu_ray_trace() ;

//Fonction qui détruit les rayons
void jeu_ray_delete() ;

//Fonction qui renvoi null si aucun disque existe
void* jeu_ray_exist() ;

//Fonction servant d'intermédiaire entre disc et main

//Fonction qui controle si un joueur peut detruire un disque de l'autre
int jeu_disc_can_destroy(int player, int ene) ;


#endif 
