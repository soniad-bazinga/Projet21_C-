CPP=g++ --std=c++11
CFLAGS= -Wall

all : main

main : main.o Partie.o Piece.o Meuble.o Personnage.o Joueur.o Objet.o Amazone.o Guerrier.o Sorciere.o Moine.o
	$(CPP) $(CFLAGS) -o $@ $^

main.o : main.cpp Partie.hpp Piece.hpp Meuble.hpp Personnage.hpp Joueur.hpp Amazone.hpp Guerrier.hpp Sorciere.hpp Moine.hpp
	$(CPP) $(CFLAGS) -c $<

partie.o : Partie.cpp Partie.hpp Piece.hpp Meuble.hpp Personnage.hpp Joueur.hpp Objet.hpp Amazone.hpp Guerrier.hpp Sorciere.hpp Moine.hpp
	$(CPP) $(CFLAGS) -c $<

piece.o : Piece.cpp Piece.hpp Personnage.hpp Joueur.hpp Meuble.hpp Amazone.hpp Guerrier.hpp Sorciere.hpp Moine.hpp
	$(CPP) $(CFLAGS) -c $<

meuble.o : Meuble.cpp Meuble.hpp
	$(CPP) $(CFLAGS) -c $<

personnage.o : Personnage.cpp Personnage.hpp Meuble.hpp
	$(CPP) $(CFLAGS) -c $<

joueur.o : Joueur.cpp Joueur.hpp Meuble.hpp Amazone.hpp Guerrier.hpp Sorciere.hpp Moine.hpp
	$(CPP) $(CFLAGS) -c $<

objet.o : Objet.hpp Objet.cpp Meuble.hpp
	$(CPP) $(CFLAGS) -c $<

amazone.o : Amazone.cpp Amazone.hpp 
	$(CPP) $(CFLAGS) -c $<

guerrier.o : Guerrier.cpp Guerrier.hpp 
	$(CPP) $(CFLAGS) -c $<

sorciere.o : Sorciere.cpp Sorciere.hpp 
	$(CPP) $(CFLAGS) -c $<

moine.o : Moine.cpp Moine.hpp 
	$(CPP) $(CFLAGS) -c $<


clean :
	rm *.o

test: all
	./main