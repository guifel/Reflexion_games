/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  main.cpp    Rendu Final										*
 * 																	*
 * 	Module principal initialisant et gérant l'interface utilisateur *
 * 	GLUI ET GLUT. Ce module depend d'OpenGL	(GLUT et GLUI).			*
 * Ce modulle passe par le module "jeu" pour interagier avec les	*
 * modules "disc" et "ray"											*
 *																	*
 * Auteurs : DUCCI Francesco Paolo FELLEY Guillaume					*
 * Scipers : 234732, 237672											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

extern "C"
{
	#include "v2d.h"
	#include "constante.h"
	#include "graphic.h"
	#include "jeu.h"
	
} ;

namespace 
{
	// Variables pour GLUT
	
	GLfloat aspect_ratio = (GLfloat)1;
	
  	int main_window;
  	
  	// Variables et pointeur pour GLUI
  	
  	char default_text[200] = "";
  	
  	GLUI *glui;
  	GLUI_Panel *load_panel, *save_panel, *information_panel, 
			   *player1_panel, *player2_panel, *current_turn_panel;
			   
  	GLUI_Button *exit_pgrogramme;
  	
  	GLUI_EditText *load_edittext,*save_edittext, *information_player1_name,
				  *information_player1_nbdisc, *information_player1_energy, 
				  *information_player1_score, *information_player2_name,
				  *information_player2_nbdisc, *information_player2_energy, 
				  *information_player2_score,*current_turn_player_turn,
				  *current_turn_remaining_time,
				  *current_turn_score_valuation, *winner;
				  
	GLUI_Spinner *information_player1_spin,*information_player2_spin;
	
	
	//Variables des dimension de l'espace de jeu		  
	static GLfloat x_min, x_max, y_min, y_max;
	
	//Varible du timer
	static float remaning_time = 10;
	
	//Variable du joueur actuel
	static int current_player = PLAYER_1;
	
	//Variable servant a identifier le bon boutton de la souri 
	static int good_button = 0;
	
	//Largeur, hauteur de la fenêtre
	static int width, height;
	
	//Point (d) de départ du rayon et son vecteur directeur normalisé (u)			  
	static V2D point_d, vect_u;
 
	//Variable pour la fin de la partie
	static unsigned int game_state ;
 
}


//Fonction qui verifie si un joueur à gagné

void check_conditions ()
{
	//Si le joueur A ne peu pas détruire de disques du joueur B
	if (!(jeu_disc_can_destroy
		(current_player, jeu_get_player_energy(current_player))))
	{
		//Si le joueur  B ne peu pas détruire de disques du joueur A
		if (!(jeu_disc_can_destroy
			(!current_player, jeu_get_player_energy(!current_player))))
		{
			//Si le score de A est mineur du score de B
			if (jeu_get_player_score(current_player) < 
				jeu_get_player_score(!(current_player)))
				//B gagne
			{
				winner->set_text(jeu_get_player_name(!(current_player)));
				game_state = OVER ;
			}
			//Si le score de A est égale au score de B	
			if (jeu_get_player_score(current_player) == 
				jeu_get_player_score(!(current_player)))
					//Le match est nul
				{
					winner -> set_text("Ex Aequo") ;
					game_state = OVER ;
				}
			//Si le score de A est majeur du score de B
			if (jeu_get_player_score(current_player) > 
				jeu_get_player_score(!(current_player)))
				//A gagne
			{
				winner->set_text(jeu_get_player_name((current_player)));
				game_state = OVER ;
			}
		}
		//Sinon (A peut pas jouer, B oui)
		else
		{
			//Si le score de A est mineur du score de B
			if (jeu_get_player_score(current_player) < 
				jeu_get_player_score(!(current_player)))
				//B gagne
			{
				winner->set_text(jeu_get_player_name(!(current_player)));
				game_state = OVER ;
			}
		}
	}
}


//Fonction de dessin et de chargement des champs GLUT

void  redraw_all ()
{	
	glClear (GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity ();
	
	glOrtho(x_min,x_max,y_min,y_max,-1,1);
	
	// Dessin les disques

	jeu_drawing();
	
	jeu_ray_trace();
	
	//Dessin des bords
	
	if(current_player == PLAYER_1)
		graphic_set_color3f(PLAYER1_R,PLAYER1_V,PLAYER1_B);
	if(current_player == PLAYER_2)
		graphic_set_color3f(PLAYER2_R,PLAYER2_V,PLAYER2_B);
		
	graphic_set_line_width(10);
	
	graphic_draw_segment(X_MIN,Y_MIN,X_MAX,Y_MIN);
	graphic_draw_segment(X_MIN,Y_MIN,X_MIN,Y_MAX);
	graphic_draw_segment(X_MAX,Y_MAX,X_MAX,Y_MIN);
	graphic_draw_segment(X_MAX,Y_MAX,X_MIN,Y_MAX);
	
	//Rectangles blancs servant a limiter le champ de jeu
	
	graphic_set_color3f(1,1,1);
	
	graphic_draw_rectangle(0,100,100,200);
	graphic_draw_rectangle(0,0,100,-200);
	graphic_draw_rectangle(-200,-200,0,300);
	graphic_draw_rectangle(100,200,300,-200);
	
	glutSwapBuffers();
}

// Fonction de mise à jour des champ GLUI

void glui_maj()
{
	information_player1_name->set_text(jeu_get_player_name(PLAYER_1));
	information_player1_score->set_float_val
		(jeu_get_player_score(PLAYER_1));
	information_player1_energy->set_float_val
		(jeu_get_player_energy(PLAYER_1));
	information_player1_nbdisc->set_float_val
		(jeu_get_player_nbdisc(PLAYER_1));
	information_player2_name->set_text(jeu_get_player_name(PLAYER_2));
	information_player2_score->set_float_val
		(jeu_get_player_score(PLAYER_2));
	information_player2_energy->set_float_val
		(jeu_get_player_energy(PLAYER_2));
	information_player2_nbdisc->set_float_val
		(jeu_get_player_nbdisc(PLAYER_2));
		
	information_player1_spin -> set_int_limits(MAX_TOUR,
		jeu_get_player_energy(PLAYER_1),GLUI_LIMIT_CLAMP);
	information_player2_spin -> set_int_limits(MAX_TOUR,
		jeu_get_player_energy(PLAYER_2),GLUI_LIMIT_CLAMP);

}


// Fonction qui valide le tire du joueur

void main_ray_validation()
{
	jeu_ray_delete();
	
	current_turn_remaining_time->set_float_val(remaning_time);
	
	jeu_ray_validation((int)current_turn_score_valuation->get_float_val());
	
	current_player = ! current_player ;
		
	current_turn_player_turn -> set_text(jeu_get_player_name
										(current_player));
										
	current_turn_score_valuation -> set_int_val(0);
										
	check_conditions () ;
								
	remaning_time = 10;
	
}


// CallBack d'affichage

void display_cb()
{
	//Affichage des élément GLUT
	redraw_all();
	
	//Affichage des élèment GLUI
	glui_maj();
	
}


//Callback de reshape

void  reshape_cb ( int  w,  int  h)
{
	glViewport(0,0, w, h);
	
	width = w;
	height= h;
	
	aspect_ratio = (GLfloat) w / (GLfloat) h;
	
	if (aspect_ratio <= 1.)
	{
		x_min = X_MIN;
		x_max = X_MAX;
		y_min = Y_MIN/aspect_ratio ;
		y_max = Y_MAX/aspect_ratio ;
	}
	else
	{
		x_min = X_MIN*aspect_ratio;
		x_max = X_MAX*aspect_ratio;
		y_min = Y_MIN ;
		y_max = Y_MAX;
	}
}


//Fonction timer

void timer_CB(int value)
{
	if(remaning_time < MAX_TIME)
	{
		remaning_time = remaning_time - 0.1;
		
		glutTimerFunc(100, &timer_CB, MAX_TIME);
		
		current_turn_remaining_time->set_float_val(
			((float)((int)(remaning_time*10)))/10);
	}
	if(remaning_time <= 0)
	{ 
		remaning_time = MAX_TIME;
		
		main_ray_validation();
		
		good_button = 0;
	}
}


//Fonction callback de la souris (déplacement)

void set_point_motion_cb(int x, int y )
{
	if(good_button && game_state == ONGOING)
	{
		if (jeu_disc_can_destroy(current_player, jeu_get_player_energy(current_player)))
		{
			vect_u.x = point_d.x -(((float)x/width)*(x_max-x_min) + x_min);
			vect_u.y = point_d.y -(((float)(height-y)/height)*(y_max-y_min) +
								y_min);
								
			if((vect_u.x || vect_u.y) && remaning_time >= 10)
			{
				remaning_time = 9.99;
				glutTimerFunc(100, &timer_CB, 0);
			}
		
			vect_u = v2d_vector_normalize(vect_u);
	
			current_turn_score_valuation->set_float_val(jeu_ray_propagate
				(point_d,vect_u,information_player1_spin -> get_int_val(),
				information_player2_spin -> get_int_val()));
		}
		else
		{
		check_conditions () ;	
				
		current_player = ! current_player ;
		
		current_turn_player_turn -> set_text(jeu_get_player_name
										(current_player));
		}
	}
}


//Fonction callback de la souris (bouttons)

void set_point_cb(int button, int button_state, int x, int y )
{
	GLfloat x2,y2,dx,dy;
	
	point_d.x = ((float)x/width)*(x_max-x_min) + x_min;
	point_d.y = ((float)(height-y)/height)*(y_max-y_min) + y_min;
	
	if (button_state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && 
		jeu_cursor_on_disc(point_d) && point_d.x <= 100 && 
		point_d.x >= 0 && point_d.y <= 100 && point_d.y >= 0)
	{
		good_button = 1;
		glutMotionFunc(set_point_motion_cb);	
		
	}
	else good_button = 0;
	
	if (button_state == GLUT_UP && button == GLUT_LEFT_BUTTON && 
		jeu_ray_exist()) 
	{
		remaning_time = 10;
		main_ray_validation();
	}
	
	if(button_state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		
		dx = x_max - x_min;
		dy = y_max - y_min;
		
		x2 = x_min + x*dx/width;
		y2= y_max - y*dy/height;
		
		x_min = x2 - dx/6;
		x_max = x2 + dx/6;
		y_min = y2 - dy/6;
		y_max = y2 + dy/6;
	}
	
	if (button_state == GLUT_UP && button == GLUT_MIDDLE_BUTTON) 
		reshape_cb(width,height);
}


//Fonction callback

void control_cb(int id)
{
	
	switch(id)
	{
		case LOAD_BUTTON :
				
			if(jeu_reading(load_edittext->get_text()))
				
				printf("Load : %s\n",load_edittext->get_text());
				reshape_cb(width,height);
				game_state = ONGOING ;
				remaning_time = 10;
				current_player = PLAYER_1;
				current_turn_player_turn -> set_text(jeu_get_player_name
										(current_player));
				current_turn_score_valuation -> set_int_val(0);
				
				winner->set_text("None");
				glutMouseFunc( set_point_cb );
				
			
			break;
			
		case SAVE_EDITTEXT :
	
			break;
			
		case SAVE_BUTTON :
			printf("Save : %s\n",save_edittext->get_text());
			jeu_saving(save_edittext->get_text());
			break;
			
		case EXIT_PROGRAMME_BUTTON:
			
			printf("\nBye !\n");
			exit(EXIT_SUCCESS);
	}
	
}


// Initialisation de GLUI

void init_glui_main()
{
	
	//Fenêtre GLUI
	
	glui = GLUI_Master.create_glui((char*) "Reflexion", 0, GLUI_H, GLUI_W); 
	
	//Rafraichissement de la fenêtre GLUT automatique
	
	glui->set_main_gfx_window(main_window); 
	
	//Chargement de widget GLUI
		
	load_panel = glui->add_panel("Load");
	glui->add_button_to_panel
		(load_panel,"Load Game",LOAD_BUTTON,control_cb);
	load_edittext = glui->add_edittext_to_panel(load_panel,
		(char*)"Filename",GLUI_EDITTEXT_TEXT,default_text,LOAD_EDITTEXT,
		control_cb);
    
    save_panel = glui->add_panel("Save");
	glui->add_button_to_panel
		(save_panel,"Save Game",SAVE_BUTTON,control_cb);
	save_edittext = glui->add_edittext_to_panel(save_panel,
		(char*)"Filename",GLUI_EDITTEXT_TEXT,default_text,SAVE_EDITTEXT,
		control_cb);
		
	load_edittext->set_text("test.txt");
	save_edittext->set_text("out.txt");
}


//Fonction de chargement des élèments GLUI 1

void init_glui_1()
{
	
	information_panel = glui->add_panel("Information");
	
	player1_panel = glui->add_panel_to_panel(information_panel,"Player 1");
	information_player1_name = glui->add_edittext_to_panel(player1_panel,
		(char*)"Name", GLUI_EDITTEXT_TEXT, default_text,
		INFORMATION_PLAYER1_NAME,control_cb);
	information_player1_nbdisc = glui->add_edittext_to_panel(player1_panel,
		(char*)"Nb disc", GLUI_EDITTEXT_INT, default_text,
		INFORMATION_PLAYER1_NBDISC,control_cb);
	information_player1_energy = glui->add_edittext_to_panel(player1_panel,
		(char*)"Energy", GLUI_EDITTEXT_INT, default_text,
		INFORMATION_PLAYER1_ENERGY,control_cb);
	information_player1_score = glui->add_edittext_to_panel(player1_panel,
		(char*)"Score", GLUI_EDITTEXT_INT, default_text,
		INFORMATION_PLAYER1_SCORE,control_cb);
	information_player1_spin = glui->add_spinner_to_panel(player1_panel,
		(char*)"Max tour",GLUI_SPINNER_INT,default_text,
		INFORMATION_PLAYER1_SPINNER,control_cb);
	player2_panel = glui->add_panel_to_panel(information_panel,"Player 2");
	information_player2_name = glui->add_edittext_to_panel(player2_panel,
		(char*)"Name", GLUI_EDITTEXT_TEXT, default_text,
		INFORMATION_PLAYER2_NAME,control_cb);
	information_player2_nbdisc = glui->add_edittext_to_panel(player2_panel,
		(char*)"Nb disc", GLUI_EDITTEXT_INT, default_text,
		INFORMATION_PLAYER2_NBDISC,control_cb);
	information_player2_energy = glui->add_edittext_to_panel(player2_panel,
		(char*)"Energy", GLUI_EDITTEXT_INT, default_text,
		INFORMATION_PLAYER2_ENERGY,control_cb);
	information_player2_score = glui->add_edittext_to_panel(player2_panel,
		(char*)"Score", GLUI_EDITTEXT_INT, default_text,
		INFORMATION_PLAYER2_SCORE,control_cb);
	information_player2_spin = glui->add_spinner_to_panel(player2_panel,
		(char*)"Max tour",GLUI_SPINNER_INT,default_text,
		INFORMATION_PLAYER2_SPINNER,control_cb);
		
}


//Fonction de chargement des élèment GLUI 2

void init_glui_2()
{

	
	current_turn_panel = glui->add_panel_to_panel(information_panel,
		"Current Turn");
	current_turn_player_turn = glui->add_edittext_to_panel
		(current_turn_panel,(char*)"Player Turn", GLUI_EDITTEXT_TEXT, 
		default_text,CURRENT_TURN_PLAYER_TURN,control_cb);
	current_turn_remaining_time = glui->add_edittext_to_panel
		(current_turn_panel,(char*)"Remaining Time", GLUI_EDITTEXT_FLOAT, 
		default_text,CURRENT_TURN_REMAINING_TIME,control_cb);
		current_turn_remaining_time->set_float_val(10.0);
	current_turn_score_valuation = glui->add_edittext_to_panel
		(current_turn_panel,(char*)"Score Variation", GLUI_EDITTEXT_INT, 
		default_text,CURRENT_TURN_SCORE_VARIATION,control_cb);
		current_turn_score_valuation->set_float_val(0);
		current_turn_player_turn->set_text("Player1");
	
	winner = glui->add_edittext((char*)"Winner", GLUI_EDITTEXT_TEXT, 
		default_text, WINNER,control_cb);
	exit_pgrogramme = glui->add_button
		("Exit",EXIT_PROGRAMME_BUTTON,control_cb);
		
	winner->set_text("None");
}


// Initialisation de GLUT

void init_glut()
{
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    
    glutInitWindowPosition(GLUT_X, GLUT_Y);
    
    glutInitWindowSize(GLUT_SIZE,GLUT_SIZE);
    
    main_window = glutCreateWindow("Reflexion Game");
    
    glClearColor (1.,1.,1.,0.);
    
	glutDisplayFunc(display_cb);
	
	glutReshapeFunc(reshape_cb);
}


// Main

int main(int argc, char * argv[])
{	
	// GLUT
	
	glutInit(&argc, argv);
	
	init_glut();
	
	// GLUI
	
	init_glui_main();
	init_glui_1();
	init_glui_2();
	
	// Chargement du jeu si un fichier est spécifié
	
	if(argc == 2)
	{
		jeu_reading(argv[1]);
		current_turn_player_turn -> set_text(jeu_get_player_name
										(current_player));
										
		glutMouseFunc( set_point_cb );
	}
	
	// Boucle principale GLUT

    glutMainLoop(); 
    
  return EXIT_SUCCESS;
}
