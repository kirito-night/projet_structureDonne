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
    Livre * l = b->L;
    while(l){
        Livre * tmp = l->suiv;
        liberer_livre(l);
        l = tmp;
    }
    free(b);
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
    Livre* l = creer_livre(num, titre, auteur);
    l->suiv = b->L;
    b->L = l;
}

void afficherLivre(Livre* l){
    printf("Titre : %s, Auteur : %s, Numero : %d\n", l->titre, l->auteur, l->num);
}

void afficherBiblio(Biblio* b){
    Livre* l = b->l;
    while(l){
        afficherLivre(l);
        l = l->suiv;
    }
}

/*

int main(void){
    return 0;
}*/