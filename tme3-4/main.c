#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void menu(){
    printf("entrer 0 pour sortir du programme \n");

    printf("entrer 1 pour afficher la bibliotheque \n");
    printf("entrer 2 pour inserer un ouvrage a la tete de la bibliotheque  \n");
    printf("entrer 3 pour supprimer un ouvrage avec son nun son titre et son auteur\n");
    printf("entrer 4 pour rechercher un ouvrage dans la bibliotheque \n");



}
int main(int argc, char* argv[]){
    if(argc != ){
        printf(" veuilez entrer le nom du fichier a lire et le nb de ligne a lire\n");
        return 0;
    }
    char *nomfic = argv[1];
    int nbligne_alire = atoi(argv[2]);

    Biblio *b  = charger_n_entrees(nomfic,nbligne_alire);
    afficherBiblio(b);

}