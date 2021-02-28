#include "entreeSortieH.h"
#include<stdio.h>
#include<string.h>
BiblioH* charger_n_entrees(char* nomfic, int n){
    BiblioH *b = creer_biblio(n);
    FILE *f = fopen(nomfic,"r");
    if(f ==NULL){
        fprintf(stderr," erreur d'ouverture de ficher");
    }

    char buffer[256];
    int num;
    char titre [256];
    char auteur [256];

    int i; 
    for( i = 0 ; i < n ; i++){
        fgets(buffer, 256,f);
        sscanf(buffer,"%d %s %s ", &num, titre, auteur);
        inserer(b,num, strdup(titre), strdup(auteur));

    }
    

    fclose(f);
    return b;
}

void enregistrer_biblio(BiblioH *b, char* nomfic){
    FILE *f = fopen(nomfic,"w");
    if(f==NULL){
        printf("enregistrement echouer: unable to open file");
    }
    int i;
    LivreH **tmp = b->T;
    for(i =0  ; i< b->m ; i++){
        while(tmp[i])
        fprintf(f,"%d %s %s\n", tmp[i]->num, tmp[i]->titre, tmp[i]->auteur);
        tmp[i] =tmp[i]->suivant; 
    }

    fclose(f);
    printf("enregistrement reussit");

}