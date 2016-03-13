/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
 *  graphic.c    Rendu Final										*
 * 																	*
 * 	Module de bas niveau utilisant OpenGL destiné à faire les       *
 *  dessins de base, ligne, cercle, rectangle etc ... 				*
 *																	*
 * Auteurs : DUCCI Francesco Paolo FELLEY Guillaume					*
 * Scipers : 234732, 237672											*
 * 																	*
 * Dernière mise a jour : 17/05/14									*
 *	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*   */
 
#include <stdio.h>
#include <math.h>
#include <GL/glu.h>

//Fonction qui dessine un segment

void graphic_draw_segment (float x1,float y1,float x2,float y2)

{ 
    glBegin (GL_LINES);
    
    glVertex2f (x1, y1);
    glVertex2f (x2, y2);

    glEnd ();
}


//Fonction qui dessine un cercle

void graphic_draw_circle (float xc,float yc,float r)

{ 
	int i;
	const int SIDES = 50;

	glBegin (GL_POLYGON);
	
  
	for (i=0; i < SIDES; i++)
	{
		float alpha = i * 2. * M_PI / SIDES;
		float x = xc + r * cos (alpha),
		y = yc + r * sin (alpha);
		glVertex2f (x, y);
	}

	glEnd ();
}


//Fonction pour dessiner un rectangle

void graphic_draw_rectangle(float x1, float y1, float x2, float y2)
{
	glBegin (GL_POLYGON);
	
	glVertex2f (x1, y1);
	glVertex2f (x1, y2);
	glVertex2f (x2, y2);
	glVertex2f (x2, y1);
	
	glEnd();

}
	

//Fonction pour changer de couleur

void graphic_set_color3f(float r,float g,float b)
{
  glColor3f(r, g, b);
}


//Fonction pour changer l'épaisseur d'un trait

void graphic_set_line_width(float width)
{
  glLineWidth(width);
}
