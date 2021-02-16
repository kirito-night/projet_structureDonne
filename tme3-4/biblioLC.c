#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num, char* titre, char* auteur){
    Livre* l = (Livre*) malloc(sizeof(Livre));  
    l->titre = (char*) malloc(sizeof(char)*200);
    l->auteur = (char*) malloc(sizeof(char)*200);

    l->num = num;
    strcpy(l->titre,titre);
    strcpy(l->auteur,auteur);

    return l;
}

void liberer_livre(Livre* l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){
    Biblio* b = (Biblio*) malloc(sizeof(Biblio));
    return b;
}

void liberer_biblio(Biblio* b){
    free(b);
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
    Livre* l = creer_livre(num, titre, auteur);
    b->L = l;
}

int main(void){
    return 0;
}