# Definitions de macros

CC     = gcc
CFLAGS = -g
CFILES = main.cpp v2d.c disc.c graphic.c jeu.c ray.c
OFILES = $(CFILES:.c=.o) error.o
LIBS = -lglut -lGL -lGLU -lm -lglui -L/usr/X11R6/lib -lX11 -lXext -lstdc++

# Definition de la premiere regle

jeu.x: $(OFILES)
	$(CC) $(OFILES) $(LIBS) -o jeu.x -g

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f jeu.o main.o ray.o graphic.o disc.o v2d.o *.x *.c~ *.h~

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
main.o: main.cpp v2d.h constante.h tolerance.h graphic.h jeu.h
v2d.o: v2d.c v2d.h
disc.o: disc.c tolerance.h constante.h v2d.h graphic.h disc.h
graphic.o: graphic.c
jeu.o: jeu.c error.h constante.h tolerance.h disc.h v2d.h ray.h jeu.h
ray.o: ray.c graphic.h tolerance.h constante.h v2d.h disc.h ray.h
