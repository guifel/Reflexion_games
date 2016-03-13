/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  jeu.c  		 Rendu final										*
 * 																	*
 * Ce fichier contient des fonctions appelées par main.ccp.			*
 * But du programme : scanner un fichier txt pour charger les		*
 * données (joueurs et disques) et verifier s'il y a des erreurs. 	*
 * Effectuer la sauvegarde de l'état courant du jeu dans un fichier *
 * txt. Fournir les donnérs des joueurs pour l'affichage.			*			
 * 																	*
 * Auteurs : DUCCI Francesco Paolo, FELLEY Guillaume				*
 * Scipers : 237672, 234732											*
 * 																	*
 * Dernière mise a jour : 15/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "error.h"
#include "constante.h"
#include "disc.h"
#include "ray.h"
#include "jeu.h"

#define ERROR_Y		1	 
#define ERROR_N		0	

typedef struct Player PLAYER ;

//Definition de la structure des joueurs	
struct Player
{
	char name[10] ;			//nom du joueur
	int score ;				//score di joueur
	int energy ;			//energie du joueur
	int nbdisc ;			//nombre des disques du joueur
};

//Fonction qui décode un ligne scannée par la fonction reading
static void decoding_line (char * tab, PLAYER players[2]) ;

//Fonction qui verifie les erreurs
static void verification_file (PLAYER players[2]) ;

//Fonction qui verifie si lo nombre de disques scannée est correct
static void disc_nb_check (int scanned_nb, int current_player) ;

//Tableau qui contient les 2 joueurs
static PLAYER tab_players[2] ;	

//Varialbe globale pour la détection des erreurs	
static int error = ERROR_N;

//Id player en train de jouer 
static int current_player = PLAYER_1;

//Etats pour l'automate de lecture
enum Reading_state {S_PLAYER_1, S_DISC_1, S_PLAYER_2, S_DISC_2} ;

/*Fonction chargée de lire les données qui concernent les joueurs et les
 * disques dans un fichier texte et de verifier les erreurs*/
int jeu_reading (const char * nom_fichier)
{
	char line[80] ;				
	FILE * fichier = NULL ; 
	error = ERROR_N ;

	if((fichier = fopen (nom_fichier, "r")) != NULL) //ouverture du fichier
	{
		disc_destruction_all();
		
		while(fgets(line,80,fichier)) 
		{
			if((line[0]=='#')||(line[0]=='\n')||(line[0]=='\r'))
				continue ;  
			decoding_line(line, tab_players) ;	  
		}

    /*dernier appel de la fonction qui verifie seulement que le nombre
     *de disques du 2eme joueur soit correcte*/
		decoding_line ("     ", tab_players) ; 
		
		verification_file (tab_players) ;
		
		current_player = PLAYER_1 ;
		
		if (error)
			return 0 ;
		else 
			return 1;
	}
	else 
	{
		printf("Erreur d'ouverture du fichier\n");
		return 0;
	}
}


static void decoding_line (char * line, PLAYER tab_players[2])
{
	static int state = S_PLAYER_1, i = 0 ;
	float cx, cy, value ;
	
	switch (state)  //Automate de lecture
	{	
		case S_PLAYER_1 :
	
		sscanf (line, "%s %d %d %d",tab_players[PLAYER_1].name,
			&tab_players[PLAYER_1].score, &tab_players[PLAYER_1].energy, 
			&tab_players[PLAYER_1].nbdisc) ;
		state = S_DISC_1 ; 
		break ;
		
		case S_DISC_1 :
	
		if (sscanf (line, "%f %f %f", &cx, &cy, &value) != 3 )
		{
			disc_nb_check(i, PLAYER_1) ;
			state = S_PLAYER_2 ;
			i = 0 ;
		}
		else
		{
			disc_creation (cx, cy, value, PLAYER_1, i) ;
			i++ ;
			break ; 
		}
	
		case S_PLAYER_2 :
	
		sscanf (line, "%s %d %d %d",tab_players[PLAYER_2].name,
			&tab_players[PLAYER_2].score, &tab_players[PLAYER_2].energy, 
			&tab_players[PLAYER_2].nbdisc) ;			   				   
		state = S_DISC_2 ; 
		break ;
			   
		case S_DISC_2 :
	
		if (sscanf (line, "%f %f %f", &cx, &cy, &value) != 3 )
		{	
			disc_nb_check(i, PLAYER_2) ;
			i = 0 ;
			state = S_PLAYER_1 ;
			break ;
		}
		else
		{
			disc_creation (cx, cy, value, PLAYER_2, i) ;
			i++ ;
			break ; 
		}
		
	default :
		;
	}
}


//Fonction qui verifie que le fichier chargé est correct

static void verification_file (PLAYER tab_players[2])
{
	int i = 0, j = 0 ;  //compteurs
	int players_n_discs [2][2] ;
	
	for(i = 0 ; i < 2 ; i++)
	{	
		//Verification que les pseudos ne dépassent pas 8 caractères
		if (strlen (tab_players[i].name) > MAX_PSEUDO) 
		{
			error_pseudo_is_too_long(i+1);
			error = ERROR_Y ;
		}
		//Verification que l'energie ne soit pas négative
		if (tab_players[i].energy < 0) 
		{
			error_energy_is_negative (i+1);
			error = ERROR_Y ;
		}
		//Verification que l'énergie ne soit pas supérieure au maximum
		if (tab_players[i].energy > MAX_ENERGY) 
		{
			error_energy_is_too_big(i+1);
			error = ERROR_Y ;
		}
		//Verification que les disques soient contenus dans le monde
		j = disc_out_of_boundaries(i) ;
		if (j != -1)
		{
			error_disk_is_out_of_boundaries(i+1, j)	;
			error = ERROR_Y ;
		}
	}
	// Vérification que les disques ne s'intersectent pas
	if ( disc_are_in_contact(players_n_discs) )
	{
		error_disks_are_in_contact (players_n_discs [0][0]+1,
			players_n_discs [0][1], players_n_discs [1][0]+1,
			players_n_discs [1][1]) ;
		error = ERROR_Y ;
	}
	
	if (!(error))
	error_success() ;
	
	return ;
}


/*Fonction chargée de sauvegarder l'état du jeu en imprimant les 
 * données dans un fichier txt */
 
void jeu_saving (const char * nom_fichier)
{
	FILE * fichier = NULL ; 
	int i = 0 ;
	
	if((fichier = fopen (nom_fichier, "w")) != NULL) //ouverture du fichier
	{
		for (i = 0 ; i < 2 ; i++)
		{
			fprintf (fichier, "%s %d %d %d\n", tab_players[i].name,
				tab_players[i].score, tab_players[i].energy, 
				tab_players[i].nbdisc) ;
											 											 
			disc_print(i, fichier) ;
		}
		fclose (fichier) ;
	}
	else 
		printf("Error, can't save the game") ;	
}

static void disc_nb_check (int scanned_nb, int player)
{
	if(scanned_nb <  tab_players[player].nbdisc)
	{
		error_missing_disk(player+1) ;
		error = ERROR_Y;
	}
	if(scanned_nb > tab_players[player].nbdisc)
	{
		error_too_many_disks(player+1) ;
		error = ERROR_Y ;
	}
}


// Fonction de dessin des disques

void jeu_drawing()
{
	if (!(error))
		disc_drawing();
}


/*Fonctions chargées de récuperer les informations des joueurs pour les
 * afficher*/
 
char* jeu_get_player_name (int player)
{
	return tab_players[player].name;
}

int jeu_get_player_energy (int player)
{
	return tab_players[player].energy;
}

int jeu_get_player_score (int player)
{
	return tab_players[player].score;
}

int jeu_get_player_nbdisc (int player)
{
	return tab_players[player].nbdisc;
}


//Fonction qui détecte si le le point_d est sur un disque ou non 

int jeu_cursor_on_disc(V2D point_d)
{
	return disc_cursor_on_disc(point_d);
}


//Fonctions qui valide le tour du joueur 

void jeu_ray_validation(int scor_var)
{
		
	int player1_nbdisc_var = 0, player2_nbdisc_var = 0;
	
	//Mise à jour du score et de l'énergie dans tab_player
	
	tab_players[current_player].score =
		tab_players[current_player].score + scor_var;
	
	tab_players[current_player].energy = 
		tab_players[current_player].energy -
		disc_destruction(current_player,&player1_nbdisc_var,
		&player2_nbdisc_var);
	
	tab_players[PLAYER_1].nbdisc =
		tab_players[PLAYER_1].nbdisc - player1_nbdisc_var;
	tab_players[PLAYER_2].nbdisc = 
		tab_players[PLAYER_2].nbdisc - player2_nbdisc_var;
	
	//Passage au joueur suivant 
	
	current_player = !current_player ;
}


//Fonction qui calcul la propagation du rayon

int jeu_ray_propagate (V2D point_d, V2D vect_u, int ene1, int ene2)
{
	int score_var ;
	
	int ene_tour ;
	
	if (current_player == PLAYER_1) ene_tour = ene1 ;
	else ene_tour = ene2 ;
	
	score_var = ray_propagate (point_d, vect_u, current_player,
							  tab_players[current_player].energy,
							  ene_tour) ;
	
	return score_var ;
}


//Fonctions servants d'intermédiaires entre le module ray et main

//Fonction qui dessine les rayons
void jeu_ray_trace ()
{
	ray_trace() ;
}

//Fonction qui détruit les rayons
void jeu_ray_delete()
{
	ray_delete() ;
}

//Fonction qui renvoi null si aucun disque existe
void* jeu_ray_exist()
{
	return ray_exist();
}


//Fonction servant d'intermédiaire entre disc et main

//Fonction qui controle si un joueur peut detruire un disque de l'autre
int jeu_disc_can_destroy(int player, int ene)
{
	return disc_can_destroy(player, ene) ;
}
