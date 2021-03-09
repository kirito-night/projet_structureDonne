#include "Chaine.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

Chaines* lectureChaines(FILE *f){

    Chaines *res = (Chaines *)malloc(sizeof(Chaines));
    char buffer[256];
    char tmp[50]; //on s'en fou de lui 
    int Nbchain;
    int Gamma;
    fgets(buffer, 256,f);
    sscanf(buffer,"%s %d" , tmp,&Nbchain);

    fgets(buffer, 256,f);
    sscanf(buffer,"%s %d" , tmp,&Gamma);
    res->nbChaines =Nbchain;
    res->gamma=Gamma;
    CellChaine *liste_cha = NULL;
    while(fgets(buffer, 256,f)!= NULL){
        //sbuffer[255] = '\0';
        CellChaine *cha = (CellChaine *)malloc(sizeof(CellChaine));
        int num;
        int nbPoints;
        sscanf(buffer,"%d %d ",&num,&nbPoints);
        cha->numero = num;
        int i;
        CellPoint *liste_point = NULL;
        for(i = 0 ; i < nbPoints; i++){
            CellPoint *point = (CellPoint*)malloc(sizeof(CellPoint));
            float x, y;
            sscanf(buffer,"%f %f ",&x,&y);
            point->x=x;
            point->y = y;
            point->suiv = liste_point;
            liste_point=point;
            
        }
        cha->points = liste_point;
        cha->suiv = liste_cha;
        liste_cha = cha;


    }
    res->chaines = liste_cha;
    return res;
}

void ecrireChaine(Chaines *C, FILE *f){
    fprintf(f,"NbChain : %d \n Gamma : %d\n",C->nbChaines,C->gamma);
    int i ;
    CellChaine *liste_chaine = C->chaines;
    for(i = 0 ; i <C->nbChaines ; i++){
        
        int nb_points = 0; 
        CellPoint *liste_point = liste_chaine->points;
        while(liste_point){
            nb_points +=1;
            liste_point=  liste_point->suiv;
        }

        fprintf(f,"%d %d ",liste_chaine->numero, nb_points);
        liste_point = liste_chaine->points;
        while(liste_point){
            fprintf(f, "%f %f ",liste_point->x,liste_point->y);

        }
        fprintf(f,"\n");

    }
}








double longueurChaine(CellChaine *c)
{


    if(c==NULL)
    {
        return 0;
    }
    double res = 0;
    CellPoint* temp_point = c->points;
    CellPoint* temp_point_suiv = temp_point->suiv;

    while(temp_point_suiv!=NULL)
    {
        res += sqrt(pow(temp_point_suiv->y - temp_point->y,2)+pow(temp_point_suiv->x - temp_point->x, 2));
        temp_point = temp_point_suiv;
        temp_point_suiv = temp_point_suiv->suiv;
    }

    return res;
}


double longueurTotale(Chaines* C)  
{
    if(C==NULL)
    {
        return 0;
    }
    double res = 0;
    CellChaine* temp = C->chaines;
    
    while(temp!=NULL){
        res+=longueurChaine(temp);
        temp = temp->suiv;
    }

    return res;
}

int comptePointsTotal(Chaines* C)
{

    if(C==NULL){
        return 0;
    }
    
    int nb_points = 0;

    CellChaine* temp = C->chaines;

    while(temp!=NULL){
        CellPoint* point = temp->points;
        while(point!=NULL){
            nb_points+=1;
            point = point->suiv;
        }
        temp = temp->suiv;
    }
    return nb_points;
}
