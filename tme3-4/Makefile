EX = main mainH
all : $(EX)

comparaisonH :comparaisonH.o biblioH.o
	gcc comparaisonH.o  biblioH.o  -o comparaisonH -Wall -g


comparaison : comparaison.o   biblioLC.o
	gcc comparaison.o  biblioLC.o -o comparaison -Wall -g

comparaisonH.o : comparaisonH.c biblioH.h
	gcc -c comparaisonH.c -Wall

comparaison.o: comparaison.c  biblioLC.h
	gcc -c comparaison.c -Wall

mainH : mainH.o biblioH.o entreeSortieH.o
	gcc mainH.o biblioH.o entreeSortieH.o -o mainH -Wall

mainH.o : mainH.c biblioH.h entreeSortieH.h
	gcc -c mainH.c -Wall

biblioH.o : biblioH.c biblioH.h
	gcc -c biblioH.c -Wall

entreeSortieH.o : entreeSortieH.c entreeSortieH.h
	gcc -c entreeSortieH.c



main: main.o biblioLC.o entreeSortieLC.o
	gcc  main.o biblioLC.o entreeSortieLC.o -o main -Wall

main.o : main.c biblioLC.h entreeSortieLC.h
	gcc -c main.c -Wall
	
biblioLC.o: biblioLC.c biblioLC.h
	gcc -c biblioLC.c -Wall

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h
	gcc -c entreeSortieLC.c


clean : 
	rm  -f *.o $(EX)
