#include "Reseau.h"
#include "Chaine.h"
#include <stdlib.h>
#include "SVGwriter.h"
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y)
{
    CellNoeud* temp_noeud = R->noeuds;

    while(temp_noeud!=NULL)
    {
        if((temp_noeud->nd->x == x) && (temp_noeud->nd->y == y))
        {
            printf("point dedans\n");
            return temp_noeud->nd;
        }        
        temp_noeud = temp_noeud->suiv;
    }
    Noeud* nouveau = (Noeud*) malloc(sizeof(Noeud));
    nouveau->num = R->nbNoeuds + 1;
    nouveau->x = x;
    nouveau->y = y;
    nouveau->voisins = NULL;
    CellNoeud* new_cell = (CellNoeud*) malloc(sizeof(CellNoeud));
    new_cell->nd =nouveau;
    new_cell->suiv = R->noeuds;
    R->noeuds = new_cell;
    R->nbNoeuds += 1;
    printf("point n'est pas dedans \n")
    return nouveau;


}

CellNoeud * insererNoeud(CellNoeud * liste_nd, CellNoeud *insere){
    CellNoeud * tmp = liste_nd;
    while(tmp){
        if(tmp->nd->x == insere->nd->x && tmp->nd->y == insere->nd->y){
            printf("deja dans la liste\n");
            return liste_nd;
        }
        tmp = tmp->suiv;
        
    }
    insere->suiv=  liste_nd;
    liste_nd = insere;
    printf("element est insere\n");
    return liste_nd; 
}
/*
Reseau* reconstitueReseauListe(Chaines *C){
    //double LtotC = longueurTotale(C);
    //int nbPointTot = comptePointsTotal(C);

    Reseau * res = (Reseau*) malloc(sizeof(Reseau));
    res->gamma = C->gamma;
    res->nbNoeuds = 0 ;
    res->noeuds = NULL;
    res->commodites = NULL;
    CellChaine *tmp_chaine = C->chaines;
    
    CellCommodite *liste_commo = NULL;
    for(int i = 0 ;  i < C->nbChaines ; i++){
        CellPoint *tmp_ptn = tmp_chaine->points;
        CellPoint *dernierPoint = NULL;
        while(tmp_ptn){
            Noeud* nouveau = rechercheCreeNoeudListe(res,tmp_ptn->x,tmp_ptn->y);
            nouveau->voisins = NULL; // pas sur pour la liste des voisin d'un nd
            
            if(tmp_ptn->suiv == NULL){
                dernierPoint = tmp_ptn;
            }
            

            tmp_ptn = tmp_ptn ->suiv;

        }
        CellCommodite *commo = (CellCommodite*)malloc(sizeof(CellCommodite));
        commo->extrA = rechercheCreeNoeudListe(res,tmp_chaine->points->x, tmp_chaine->points->y);
        commo->extrB = rechercheCreeNoeudListe(res,dernierPoint->x,dernierPoint->y);
        commo->suiv =liste_commo;
        liste_commo= commo;


        tmp_chaine =tmp_chaine->suiv;
    } 
    res->commodites =liste_commo;
    

    return res;
}*/


Reseau* reconstitueReseauListe(Chaines *C){
    //double LtotC = longueurTotale(C);
    //int nbPointTot = comptePointsTotal(C);

    Reseau * res = (Reseau*) malloc(sizeof(Reseau));
    res->gamma = C->gamma;
    res->nbNoeuds = 0 ;
    res->noeuds = NULL;
    res->commodites = NULL;
    CellChaine *tmp_chaine = C->chaines;
    
    CellCommodite *liste_commo = NULL;
    for(int i = 0 ;  i < C->nbChaines ; i++){
        CellPoint *tmp_ptn = tmp_chaine->points;
        CellPoint *tmp_ptn_suiv = tmp_ptn->suiv;
        while(tmp_ptn_suiv){
            Noeud* nouveau = rechercheCreeNoeudListe(res,tmp_ptn->x,tmp_ptn->y);
            Noeud* nouveau_suiv = rechercheCreeNoeudListe(res,tmp_ptn_suiv->x,tmp_ptn_suiv->y);
            CellNoeud *v_inserer = res->noeuds; //l'element suivant se trouve forcement en tete de liste car insertion en tete
            nouveau->voisins = insererNoeud(nouveau->voisins , v_inserer); // pas sur pour la liste des voisin d'un nd
            
            
            

            tmp_ptn = tmp_ptn_suiv;
            tmp_ptn_suiv = tmp_ptn_suiv->suiv;

        }
        CellCommodite *commo = (CellCommodite*)malloc(sizeof(CellCommodite));
        commo->extrA = rechercheCreeNoeudListe(res,tmp_chaine->points->x, tmp_chaine->points->y);
        commo->extrB = rechercheCreeNoeudListe(res,tmp_ptn->x,tmp_ptn->y);
        commo->suiv =liste_commo;
        liste_commo= commo;


        tmp_chaine =tmp_chaine->suiv;
    } 
    res->commodites =liste_commo;
    

    return res;
}

int nbCommodites(Reseau *R){
    CellCommodite *commo = R->commodites; 
    int res = 0;
    while(commo){
        res+=1;
        commo = commo->suiv;
    }
    return res;
}

/*int nbLiaisons(Reseau *R){
    CellNoeud *l = R->noeuds;
    int res = 0;
    while(l){
        res+=1;
        l = l->suiv;
    }
    return res -1;
}*/

int nbLiaisons(Reseau *R){
    CellNoeud *l = R->noeuds;
    int res = 0;
    while(l){
        res+=1;
        l = l->suiv;
    }
    return res -1;
}


void ecrireReseau(Reseau *R, FILE *f){
    int nbl = nbLiaisons(R);
    int nbc = nbCommodites(R);
    fprintf(f,"NbNoeud :  %d\n NbLiaisons :  %d\n Nbcommodites :  %d\nGamma :  %d\n\n", R->nbNoeuds , nbl ,nbc, R->gamma);
    CellNoeud *liste_nd = R->noeuds;
    
    for(int  i = 0 ; i< R->nbNoeuds ; i++){
        fprintf(f,"v %d %.2f %.2f \n", liste_nd->nd->num,liste_nd->nd->x, liste_nd->nd->y);
        liste_nd = liste_nd->suiv;
    }
    fprintf(f, "\n");
    liste_nd = R->noeuds;
    CellNoeud * liste_nd_suiv = liste_nd->suiv;
    for(int j = 0 ; j < nbl ; j++){
        fprintf(f,"l %d %d \n ", liste_nd->nd->num, liste_nd_suiv->nd->num);
        liste_nd = liste_nd_suiv;
        liste_nd_suiv = liste_nd_suiv ->suiv;
    }
    
    fprintf(f, "\n");
    CellCommodite *liste_commo = R->commodites;
    for(int k = 0 ; k < nbc ; k++){
        fprintf(f, "k %d %d \n", liste_commo->extrA->num,liste_commo->extrB->num);
        liste_commo = liste_commo->suiv;
    }

    return ;
}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}