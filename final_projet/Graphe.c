#include "Graphe.h"
#include <stdlib.h>
#include "Struct_File.h"


Sommet* InitieSommet(int num , double x, double y){
    Sommet* res =  (Sommet *)malloc(sizeof(Sommet));
    res->num = num;
    res->x = x;
    res->y = y;
    res->L_voisin = NULL;
    return res;
}
/*
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
}*/


Graphe *creerGraphe(Reseau *r){
    Graphe *resG = (Graphe *)malloc(sizeof(Graphe));
    resG->gamma = r->gamma;
    resG->nbsom = r->nbNoeuds;
    resG->nbcommod = nbCommodites(r);
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
    
    int cpt_commod = 0;
    while(l_commo ){ //on s'en occupe de la commodite
        
        /*Commod* new_commo = (Commod*) malloc(sizeof(Commod));
        new_commo->e1 = l_commo->extrA;
        new_commo->e2 = l_commo->extrB;
        (resG->T_commod)[resG->nbcommod] = *new_commo;*/

        (resG->T_commod)[cpt_commod].e1 = l_commo->extrA;
        (resG->T_commod)[cpt_commod].e2 = l_commo->extrB;

        l_commo = l_commo->suiv;
        cpt_commod +=1;


    }



    
    return resG;
}

int plus_petit_nbChaine (Graphe* g, int u , int v){
    if (u == v){
        return 0 ; // le chemin nulle 
    }
    
    // pour la taille du tabeau a voir si ajouter +1 , ou bien de faire -1 sur les indice
    int visit[g->nbsom]; // on cree un tableau pour verifier si un noeud est deja visite ou non 

    memset(visit, 0 , sizeof(int) * g->nbsom);

    int distance[g->nbsom];
    for(int i = 0 ; i < g->nbsom ; i++){
        distance[i] = 0;
    }

    S_file *F  = (S_file*) malloc(sizeof(S_file));
    Init_file(F);
    visit[u-1] = 1;
    distance[u-1] = 0; // verification pour etre sur
    enfile(F,u);


    while(!(estFileVide(F))){
        int sommet_present = defile(F); 
        if(sommet_present = v){
            assert(distance[sommet_present -1] == distance[v-1]);
            return distance[v-1];
        }

        Cellule_arete * cour = g->T_som[sommet_present -1]->L_voisin;
        while (cour != NULL)
        {
            int sommet_voisin = cour->a->v;
            if(visit[sommet_voisin -1] == 0){
                visit[sommet_voisin -1] =  1 ;
                enfile(F,sommet_voisin);
                distance[sommet_voisin -1] = distance[sommet_present -1] +1;

            }
            cour = cour->suiv;
        }
        

        
    }
    
    return -1 ; // pas de chemin pour aller de u a v 

}


