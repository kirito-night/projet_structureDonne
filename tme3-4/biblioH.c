#include "biblioH.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include<stdio.h>
int fonctionClef(char* auteur){
    int sum = 0;
    int i = 0;
    while(auteur[i]!= '\0'){
        sum += auteur[i];
        i++;
    }

    return sum;
}

LivreH * creer_livre( int num , char * titre, char * auteur){
    LivreH *res = (LivreH *)malloc(sizeof(LivreH));
    res->clef = fonctionClef(auteur);
    res->num = num;
    res->titre = strdup(titre);
    res->auteur = strdup(auteur);
    res->suivant = NULL;
    return res;
}

void liberer_livre(LivreH *l){
    free(l->auteur);
    free(l->titre);
    free(l);
}

BiblioH * creer_biblio(int m){
    BiblioH* res = (BiblioH *)malloc(sizeof(BiblioH));
    res->m = m;
    res->nE = 0;
    res->T = (LivreH**)malloc(sizeof(LivreH*)*m);
    //memset(res->T, 0 , sizeof(LivreH*)*m);
    int i = 0;
    for(i = 0 ; i < res->nE; i++){
        (res->T)[i] = (LivreH*)malloc(sizeof(LivreH));
    }
    return res;

}

void liberer_biblio(BiblioH * b){
    int i = 0 ; 
    for(i = 0 ; i < b->nE; i++){
        liberer_livre((b->T)[i]);

    }
    free(b->T);
}

int fonctionHachage(int cle, int m){
    int A =(sqrt(5)-1)/2;
    return (int)(m*(cle* A - (int)(cle*A)));
}

void inserer(BiblioH * b, int num, char* titre , char* auteur){
    int i = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH *ins = creer_livre(num,titre,auteur);
    ins->suivant = (b->T)[i];
    (b->T)[i] = ins;
}

LivreH * recherche_ouvrage_num (BiblioH *b, int num){
    int i; 
    for(i =0 ; i< b->m ; i++){
        LivreH *tmp = b->T[i];
        while (tmp){
            if(tmp->num == num){
                printf("livre  trouver\n");
                return tmp;
            }
        }
    }
    printf("livre non trouver\n");
    return NULL;
}


LivreH * recherche_ouvrage_titre(BiblioH *b, char * titre){
    int i; 
    for(i =0 ; i< b->m ; i++){
        LivreH *tmp = b->T[i];
        while (tmp){
            if(strcmp(tmp->auteur, titre)== 0){
                printf("livre  trouver\n");
                return tmp;
            }
        }
    }
    printf("livre non trouver\n");
    return NULL;
}

BiblioH * recherche_ouvrage_auteur(BiblioH *b, char * auteur){
    int i = fonctionClef(auteur);
    BiblioH *res = b->T[i];
    return res ;
}


void afficher_livre(LivreH *l){
     printf("Titre : %s, Auteur : %s, Numero : %d\n", l->titre, l->auteur, l->num);
}

void afficher_biblio(BiblioH *b){
    int i ; 
    for(i = 0 ; i < b->nE; i++){
        LivreH *tmp = b->T[i];
        while (tmp){
            afficher_livre(tmp);
            tmp = tmp->suivant;
        }
    }
}