/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  graphic.h    Rendu Final										*
 * 																	*
 * 	Module de bas niveau utilisant OpenGL destiné à faire les       *
 *  dessins de base, ligne, cercle, rectangle etc ... 				*
 *																	*
 * Auteurs : DUCCI Francesco Paolo FELLEY Guillaume					*
 * Scipers : 234732, 237672											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */
 
#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

//Fonction qui dessine un segment
void graphic_draw_segment (float x1,float y1,float x2,float y2);

//Fonction qui dessine un cercle
void graphic_draw_circle (float xc,float yc,float r);

//Fonction pour changer de couleur
void graphic_set_color3f(float r,float g,float b) ;

//Fonction pour changer l'épaisseur d'un trait
void graphic_set_line_width(float width);

//Fonction pour dessiner un rectangle
void graphic_draw_rectangle(float x1, float y1, float x2, float y2);

#endif
