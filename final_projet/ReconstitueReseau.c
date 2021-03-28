#include "Reseau.h"
#include "Chaine.h"
#include<stdio.h>
#include<stdlib.h>
#include"SVGwriter.h"

int main(int argc , char *argv[]){
    /*if(argc != 3 ){
        printf("veuillez entrer le nom du fichier .cha et le un entier");
    }
    char *nomfic = argv[1];
    FILE *f = fopen(nomfic,"r");

    if(f==NULL)
    {
        printf("Le fichier n'as pas pu être ouvert\n");
        exit(1);
    }*/

    FILE *f = fopen("00014_burma.cha","r");
    
    FILE *chaines = fopen("chainesEcrites.txt","w");
    if(chaines == NULL)
    {
        printf("Le fichier n'as pas pu être ouvert\n");
        exit(2);
    }

    Chaines* c = lectureChaines(f);


    Reseau *res = reconstitueReseauListe(c);
    afficheReseauSVG(res,"affichageReseau");
    FILE *fw = fopen("ReseauEcrite", "w");
    
    ecrireReseau(res,fw);
    fclose(fw);


    return 0;
}