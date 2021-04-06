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
void insererNoeudArbre(Noeud *n, ArbreQuat** a, ArbreQuat* parent){
    
    if(*a == NULL){
        double new_coteX = (parent->coteX) / 2;
        double new_coteY = (parent->coteY) / 2;
        double new_x , new_y;
        double xc = parent->xc;
        double yc = parent->yc;
        /*
        if(n->x < parent->xc && n->y < parent->yc){ //le cas sud ouest

            new_x = xc - xc/2;
            ArbreQuat* son =  creerArbreQuat(xc - xc/2, yc - yc/2, new_coteX, new_coteY);
            son->noeud = n;
            parent->so = son;
        }
        if(n->x > parent->xc && n->y > parent->yc){//nord est 
            ArbreQuat* son =  creerArbreQuat(xc + xc/2, yc + yc/2, new_coteX, new_coteY);
            son->noeud = n;
            parent->ne = son;
        }
        if(n->x < parent->xc && n->y > parent->yc){//nord ouest 
            ArbreQuat* son =  creerArbreQuat(xc - xc/2, yc + yc/2, new_coteX, new_coteY);
            son->noeud = n;
            parent->no = son;
        }
        else{ //sud est
            ArbreQuat* son =  creerArbreQuat(xc + xc/2, yc - yc/2, new_coteX, new_coteY);
            son->noeud = n;
            parent->se = son;
        }
        */

       if(n->x < parent->xc){
           new_x = xc - xc/2 ;
       }else{
           new_x  = xc+ xc/2 ;
       }
       
       if(n->y < parent->yc){
           new_y = yc - yc/2;
       }else{
           new_y = yc +yc/2;
       }

       ArbreQuat* son =  creerArbreQuat(new_x, new_y, new_coteX, new_coteY);
       son->noeud = n;
       *a = son;
    }

    if((*a)->noeud != NULL){
        Noeud * tmp  = (*a)->noeud ; 

        if(tmp->x < (*a)->xc){
            if(tmp->y < (*a)->yc){
                insererNoeudArbre(tmp, &(*a)->so,*a );
            }
            else{
                insererNoeudArbre(tmp, &(*a)->no,*a );
            }
        }else{
            if(tmp->y < (*a)->yc){
                insererNoeudArbre(tmp, &(*a)->se,*a );
            }
            else{
                insererNoeudArbre(tmp, &(*a)->ne, *a);
            }
        }

        if(n->x < (*a)->xc){
            if(n->y < (*a)->yc){
                insererNoeudArbre(n, &(*a)->so,*a );
            }
            else{
                insererNoeudArbre(n, &(*a)->no,*a );
            }
        }else{
            if(n->y < (*a)->yc){
                insererNoeudArbre(n, &(*a)->se,*a );
            }
            else{
                insererNoeudArbre(n, &(*a)->ne, *a);
            }
        }
        (*a)->noeud = NULL;
    }

    if((*a) -> noeud == NULL && *a != NULL){
        if(n->x < parent->xc && n->y < parent->yc){
            insererNoeudArbre(n, &(*a)->so,*a);
        }

        if(n->x > parent->xc && n->y > parent->yc){
             insererNoeudArbre(n, &(*a)->ne,*a);
        }
        if(n->x < parent->xc && n->y > parent->yc){
            insererNoeudArbre(n, &(*a)->no,*a);
        }
        if(n->x > parent->xc && n->y < parent->yc){
            insererNoeudArbre(n, &(*a)->se,*a);
        }

    }

}





Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){


    if((*a) == NULL){
        Noeud *new  = (Noeud *) malloc (sizeof(Noeud));
        new->x = x;
        new->y = y;
        new->num = R->nbNoeuds + 1;
        new->voisins = NULL;

        CellNoeud *new_cell = (CellNoeud *) malloc(sizeof(CellNoeud));
        new_cell ->nd = new; 
        new_cell ->suiv = R->noeuds ;
        R->noeuds  =new_cell;
        R->nbNoeuds +=1 ;

        insererNoeudArbre(new, a,parent);
        return new; 
    }

    if((*a)-> noeud != NULL){
        Noeud *tmp_noeud = (*a)-> noeud; 
        if(tmp_noeud -> x == x && tmp_noeud ->y == y){ //le cas ou le noeud est dans l'arbre
            return tmp_noeud;
        }
        
        if(x < (*a) ->xc){ //le cas ou le noeud n'est pas dans l'arbre
            if(y < (*a) ->yc){
                rechercheCreeNoeudArbre(R, &(*a)->so, *a, x, y );
            }else{
                rechercheCreeNoeudArbre(R, &(*a)->no, *a, x, y );
            }
        }else{
            if(y < (*a) ->yc){
                 rechercheCreeNoeudArbre(R, &(*a)->se, *a, x, y );
            }
            else{
                rechercheCreeNoeudArbre(R, &(*a)->ne, *a, x, y );
            }
        }
    }

    if((*a)->noeud == NULL && *a != NULL){
         if(x < (*a) ->xc){ //le cas ou le noeud n'est pas dans l'arbre
            if(y < (*a) ->yc){
                rechercheCreeNoeudArbre(R, &(*a)->so, *a, x, y );
            }else{
                rechercheCreeNoeudArbre(R, &(*a)->no, *a, x, y );
            }
        }else{
            if(y < (*a) ->yc){
                 rechercheCreeNoeudArbre(R, &(*a)->se, *a, x, y );
            }
            else{
                rechercheCreeNoeudArbre(R, &(*a)->ne, *a, x, y );
            }
        }
    }

}
