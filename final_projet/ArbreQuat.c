#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"
#include "Chaine.h"

void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax)
{
    CellChaine* CellTemp = C->chaines;
    CellPoint* p = CellTemp->points;
    *xmin = p->x, *xmax = p->x, *ymax = p->y, *ymin = p->y; //Problème ici

    while(CellTemp->suiv!=NULL)
    {
        p = CellTemp->points;
        while(p->suiv!=NULL)
        {
            if(*xmin > p->x){
                *xmin = p->x;
            }
            if(*xmax<p->x){
                *xmax = p->x;
            }
            if(*ymin>p->y){
                *ymin=p->y;
            }
            if(*ymax<p->y){
                *ymax=p->y;
            }
            p = p->suiv;
        }
        CellTemp = CellTemp->suiv;
    }
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX,double coteY)
    {
        ArbreQuat* new = (ArbreQuat*) malloc(sizeof(ArbreQuat));

        new->xc = xc;
        new->yc = yc;
        new->coteX = coteX;
        new->coteY = coteY;
        new->noeud = NULL;
        new->so = NULL;
        new->se = NULL;
        new->ne = NULL;
        new->no = NULL;

        return new;
    }




Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*
parent, double x, double y);