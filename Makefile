exec : main.o matrice.o flux.o
	g++ -o exec main.o matrice.o flux.o

main.o : main.cpp matrice.h
	g++ -c main.cpp

matrice.o : matrice.cpp matrice.h
	g++ -c matrice.cpp

flux.o : flux.cpp flux.h
	g++ -c flux.cpp

clean : rm *.o exec  
