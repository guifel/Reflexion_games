/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  constante.h    Rendu final										*
 * 																	*
 * Fichier contenant les constantes de haut niveau 					*
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */
 
#ifndef __CONSTANTE_H__
#define __CONSTANTE_H__
 
#include "tolerance.h"

// Constantes imposées pour le projet 

#define MIN_RADIUS 1.414213562
#define MAX_DISCS 1250
#define MAX_ENERGY 200
#define MAX_TOUR 20
#define MAX_TIME 10
#define MAX_PSEUDO 8

//Id's des joueurs

#define PLAYER_1 	0
#define PLAYER_2 	1

// Jeu en cours ou fini

#define ONGOING 0
#define OVER 1


// Couleur des disques

#define PLAYER1_R 0.4
#define PLAYER1_V 0
#define PLAYER1_B 0.4
#define PLAYER2_R 1
#define PLAYER2_V 0.6
#define PLAYER2_B 0

// Definition du domaine de jeu

#define X_MIN 						0
#define X_MAX 						100
#define Y_MIN 						0
#define Y_MAX						100

// Tailles des fenêtre et leur position

#define GLUT_SIZE 	500
#define GLUT_X 		650
#define GLUT_Y 		100
#define GLUI_W 		50
#define GLUI_H 		400

// ID GLUI

#define LOAD_EDITTEXT				11
#define LOAD_BUTTON					12
#define SAVE_EDITTEXT				21
#define SAVE_BUTTON					22
#define INFORMATION_PLAYER1_NAME	311
#define INFORMATION_PLAYER1_NBDISC	312
#define INFORMATION_PLAYER1_ENERGY	313
#define INFORMATION_PLAYER1_SCORE	314
#define INFORMATION_PLAYER1_SPINNER 315
#define INFORMATION_PLAYER2_NAME	321
#define INFORMATION_PLAYER2_NBDISC	322	
#define INFORMATION_PLAYER2_ENERGY	323
#define INFORMATION_PLAYER2_SCORE	324
#define INFORMATION_PLAYER2_SPINNER 325
#define CURRENT_TURN_PLAYER_TURN	41
#define CURRENT_TURN_REMAINING_TIME	42
#define CURRENT_TURN_SCORE_VARIATION 43
#define WINNER 						5
#define EXIT_PROGRAMME_BUTTON		6


#endif 
