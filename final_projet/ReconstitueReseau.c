#include "Reseau.h"
#include "Chaine.h"
#include<stdio.h>
#include<stdlib.h>
#include"SVGwriter.h"
#include "Hachage.h"
#include"ArbreQuat.h"

#define TAILLE 50

void menu(){
    printf("entrez 1 pour la reconstitution de reseau par liste\n");
    printf("entrez 2 pour la reconstitution de reseau par table d'hachage\n");
    printf("entrez 3 pour la reconstitution de reseau par arbre quat\n");

}
/*
int main(int argc , char *argv[]){
    
    FILE *f = fopen("00014_burma.cha","r");
    
    //FILE *chaines = fopen("chainesEcrites.txt","w");
    if(f == NULL)
    {
        printf("Le fichier n'as pas pu être ouvert\n");
        exit(2);
    }

    Chaines* c = lectureChaines(f);


    Reseau* resABR  =reconstitueReseauArbre(c);
    afficheReseauSVG (resABR , "affchageReseauArbre");
    printf("le reseau est affiche\n");
    FILE *fw = fopen("ReseauEcrite", "w");
    
    ecrireReseau(resABR,fw);
    fclose(fw);
    fclose(f);

    return 0;
}
*/



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

        printf("reseau afficher, veuiller regarder le fichier html affchagereseauListe\n");
        break;
    case 2 : ;
        Reseau *resH = reconstitueReseauHachage(c, TAILLE);
        afficheReseauSVG(resH, "affichageReseauHachage");
       
        FILE *fw_hachage = fopen("ReseauEcriteHachage", "w");
        ecrireReseau(resH,fw_hachage);
        fclose(fw_hachage);
        printf("reseau afficher, veuiller regarder le fichier html affchagereseauHachage\n");
        break ;
    case 3 : ;
        Reseau* resABR  =reconstitueReseauArbre(c);
        afficheReseauSVG (resABR , "affchageReseauArbre");
        
        FILE *fw_arbre = fopen("ReseauEcriteArbre", "w");
        ecrireReseau(resABR,fw_arbre);
        fclose(fw_arbre);


        printf("reseau afficher, veuiller regarder le fichier html affchagereseauArbre\n");
        break; 
    
    default:
        printf("veuillez suivre l'indication du menu");
        break;

    }

    return 0;

}
