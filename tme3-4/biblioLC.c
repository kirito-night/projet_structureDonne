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
    b->L =NULL;
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

Livre * recherche_ouvrage_num (Biblio *b, int num){
    Livre * l =b->L;
    while(l){
        if(l->num == num){
            return l;
        }
        l= l->suiv;
    }
    printf("livre non trouver");
    return NULL;
}

Livre * recherche_ouvrage_titre (Biblio *b, char* titre){
    Livre * l =b->L;
    while(l){
        if(strcmp(l->titre,titre)==0){
            return l;
        }
        l= l->suiv;
    }
    printf("livre non trouver");
    return NULL;
}

Biblio * recherche_ouvrage_auteur(Biblio *b, char* auteur){
    Biblio *res = creer_biblio();
    Livre *l = b->L;
    while(l){
        if(strcmp(l->auteur, auteur)== 0){
            inserer_en_tete(res,l->num, l->titre, l->auteur);
        }
        l =  l->suiv;
    }
    return res;
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