#include "Graphe.h"
#include <stdlib.h>
Sommet* InitieSommet(int num , double x, double y){
    Sommet* res =  (Sommet *)malloc(sizeof(Sommet));
    res->num = num;
    res->x = x;
    res->y = y;
    res->L_voisin = NULL;
    return res;
}

Graphe *creerGrapheTest(Reseau *r){
    Graphe *resG = (Graphe *)malloc(sizeof(Graphe));
    resG->gamma = r->gamma;
    resG->nbsom = r->nbNoeuds;
    resG->nbcommod = 0;
    resG->T_som = (Sommet**) malloc(sizeof(Sommet*)*resG->nbsom);
    memset(resG->T_som, 0,sizeof(Sommet*)*resG->nbsom );
    resG->T_commod =NULL;
    
    CellNoeud *l_noeud = r->noeuds;
    while(l_noeud){
        if(resG->T_som[(l_noeud->nd->num) -1] ==NULL){ // on verifie si le sommet est deja initier ou pas
            Sommet *new_sommet = InitieSommet(l_noeud->nd->num, l_noeud->nd->x,l_noeud->nd->y);
            
            

            CellNoeud *liste_voisin = l_noeud->nd->voisins;
            while(liste_voisin){  //probleme car alloue 2 fois une meme arete 
                
                //on alloue l'arete 
                Arete *new_arete = (Arete *)malloc(sizeof(Arete));
                new_arete->u = new_sommet->num;
                new_arete->v = liste_voisin->nd->num;
                
                //on alloue la cellule pour l'arete et on insere en tete dans la liste voisin des l
                Cellule_arete *new_cell  = (Cellule_arete*)malloc(sizeof(Cellule_arete));
                new_cell->a = new_arete;
                new_cell ->suiv = new_sommet->L_voisin;
                new_sommet->L_voisin = new_cell;

                //on alloue la cellule pour voisin qui contient la meme arete
                Cellule_arete *cell_voisin  = (Cellule_arete*)malloc(sizeof(Cellule_arete));
                cell_voisin->a = new_arete;

                // on verifie si le sommet est deja initialiser ou pas
                if((resG->T_som)[liste_voisin->nd->num -1] == NULL){ // si la sommet n'est pas initialise , on initialise 
                    Sommet* sommet_voisin = InitieSommet(liste_voisin->nd->num,liste_voisin->nd->x, liste_voisin->nd->y);
                    cell_voisin->suiv =  sommet_voisin->L_voisin;
                    sommet_voisin->L_voisin = cell_voisin;

                    (resG->T_som)[liste_voisin->nd->num -1] = sommet_voisin;

                }else{ // si deja initialiser on insere dans sa liste de voisin 
                   cell_voisin->suiv = (resG->T_som)[liste_voisin->nd->num -1]->L_voisin;
                   (resG->T_som)[liste_voisin->nd->num -1] = cell_voisin;
                }

                



                liste_voisin= liste_voisin->suiv;
                
            }

            (resG->T_som)[(new_sommet->num) -1]  = new_sommet;


            l_noeud = l_noeud->suiv;
        }else{ // si le sommet est deja initier on s'en occupe donc que des voisin 

        }
        
    }
    


    return resG;
}


Graphe *creerGraphe(Reseau *r){
    Graphe *resG = (Graphe *)malloc(sizeof(Graphe));
    resG->gamma = r->gamma;
    resG->nbsom = r->nbNoeuds;
    resG->nbcommod = 0;
    resG->T_som = (Sommet**) malloc(sizeof(Sommet*)*resG->nbsom);
    memset(resG->T_som, 0,sizeof(Sommet*)*resG->nbsom );
    resG->T_commod =(Commod *)malloc(sizeof(Commod) * resG->nbcommod);
    
    CellNoeud *l_noeud = r->noeuds;
    while(l_noeud){
       
        Sommet *new_sommet = InitieSommet(l_noeud->nd->num, l_noeud->nd->x,l_noeud->nd->y);
        CellNoeud *liste_voisin = l_noeud->nd->voisins;
        while(liste_voisin){ // une condition necessaire probablement 
            Arete *new_arete = (Arete *)malloc(sizeof(Arete));
            new_arete->u = new_sommet->num;
            new_arete->v = liste_voisin->nd->num;
            Cellule_arete *new_cell  = (Cellule_arete*)malloc(sizeof(Cellule_arete));
            new_cell->a = new_arete;
            new_cell ->suiv = new_sommet->L_voisin;
            new_sommet->L_voisin = new_cell;

            liste_voisin= liste_voisin->suiv;
        }

        (resG->T_som)[(new_sommet->num) -1]  = new_sommet;

        l_noeud= l_noeud->suiv;
    }

    CellCommodite *l_commo = r->commodites;
    
    while(l_commo ){ //on s'en occupe de la commodite
        Commod* new_commo = (Commod*) malloc(sizeof(Commod));
        new_commo->e1 = l_commo->extrA;
        new_commo->e2 = l_commo->extrB;
        (resG->T_commod)[resG->nbcommod] = *new_commo;

        l_commo = l_commo->suiv;
        resG->nbcommod +=1;


    }



    
    return resG;
}
