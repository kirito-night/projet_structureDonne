#include "Reseau.h"
#include "Chaine.h"
#include<stdio.h>
#include<stdlib.h>
#include"SVGwriter.h"
//#include "Hachage.h"

#define TAILLE 50
void menu(){
    printf("entrez 1 pour la reconstitution de reseau par liste\n");
    printf("entrez 2 pour la reconstitution de reseau par table d'hachage\n");
    printf("entrez 3 pour la reconstitution de reseau par arbre quat\n");

}
/*
int main(int argc , char *argv[]){
    if(argc != 3 ){
        printf("veuillez entrer le nom du fichier .cha et le un entier");
    }
    char *nomfic = argv[1];
    FILE *f = fopen(nomfic,"r");

    if(f==NULL)
    {
        printf("Le fichier n'as pas pu être ouvert\n");
        exit(1);
    }

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
}*/


int main(int argc , char *argv[]){
    menu();
    if(argc != 3 ){
        printf("veuillez entrer le nom du fichier .cha et le un entier");
    }

    char *nomfic = argv[1];
    int rep = atoi(argv[2]);
    FILE *f = fopen(nomfic,"r");
    if(f==NULL)
    {
        printf("Le fichier n'as pas pu être ouvert\n");
        exit(1);
    }

    Chaines *c = lectureChaines(f);

    switch (rep)
    {
    case 1: ;
        Reseau *res = reconstitueReseauListe(c);
        afficheReseauSVG(res,"affichagereseauListe");
        FILE *fw = fopen("ReseauEcriteliste", "w");
        ecrireReseau(res,fw);
        fclose(fw);
        break;
    case 2 : ;
        Reseau *resH = reconstitueReseauHachage(c, TAILLE);
        afficheReseauSVG(resH, "affichageReseauHachage");
        break ; 
    
    default:
        printf("veuillez suivre l'indication du menu");
        break;
    }

}
