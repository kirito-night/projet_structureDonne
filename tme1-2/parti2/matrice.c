#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "matrice.h"
int **alloue_matrice(int ** T, int n){ //1er version peu efficace car la matrice passer en argument fait une copie qui occupe une place memoire
    T=(int **) malloc(sizeof(int*)*n);
    int i;
    for(i = 0 ; i< n; i++ ){
         T[i]= (int *)malloc(sizeof(int)*n);
    }
    return T;

}
void alloue_matrice_2(int *** T, int n){ //2eme version plus efficace en donnant comme argument de la foncition une pointeur de matrice
    *T=(int **) malloc(sizeof(int*)*n);
    int i;
    for(i = 0 ; i< n; i++ ){
         (*T)[i]= (int *)malloc(sizeof(int)*n);
    }
    

}


void desalloue_matrice(int **T, int n){
    int **tab = T;
    int i;
    for(i = 0 ; i< n ; i++){
        free(tab[i]);
    }
    free(tab);
}

void remplir_matrice(int **T, int n, int V){
    int i , j;
    for(i =0 ; i< n; i++){
        for(j= 0 ; j < n ; j++){
            T[i][j] = rand()%V;
        }
    }
}
void remplir_matrice_trisup(int **T, int n, int V){
    int i , j;
    for(i =0 ; i< n; i++){
        for(j= 0 ; j < n ; j++){
            if(i > j){
                T[i][j] = 0;
            }else{
                T[i][j] = rand()%V;
            }
            
        }
    }
}
void remplir_matrice_triinf(int **T, int n, int V){
    int i , j;
    for(i =0 ; i< n; i++){
        for(j= 0 ; j < n ; j++){
            if(i > j){
                T[i][j] = rand()%V;
            }else{
                T[i][j] = 0;
            }
            
        }
    }
}

void afficher_matrice(int **T, int n){
    int i , j;
    for(i =0 ; i< n; i++){
        for(j= 0 ; j < n ; j++){
            printf("%d \t",T[i][j]);
        }
        putchar('\n');
    }
}

int all_diff_1(int **Mat, int n){
    int i, j, k, l; 
     for(i =0 ; i< n; i++){
        for(j= 0 ; j < n ; j++){
            for(k = 0; k < n ; k++){
                for(l = 0 ; l < n ; l ++){
                    if (Mat[i][j] == Mat[k][l]){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int all_diff_2(int **Mat, int n , int V){
    int *tab = (int *)malloc(sizeof(int)*V);
    int i , j; 
    for(i=0 ; i< n; i++){
        for(j=0 ; j < n ; j++){
            if(tab[Mat[i][j]]== 1){
                free(tab);
                return 0;
            }
            else{
                tab[Mat[i][j]] = 1;
            }
        }
     }
     free(tab);
     return 1;

}

int **produit_matrice(int **mat1, int ** mat2 , int n){
    int **res = NULL;
    alloue_matrice_2(&res,n);
    int i,j,k;
    for(i=0 ; i < n ; i++){
        for(j=0;j<n; j++){
            res[i][j] = 0;
            for(k=0;k<n; k++){
                res[i][j] += mat1[i][k]  * mat2[k][j];
                
            }
        }
    }
    return res;
}

int **produit_matrice_2(int **mat1, int **mat2,int n){
    int **res = NULL;
    alloue_matrice_2(&res,n);
    int i,j;
    int k, tmp;
    for(i=0 ; i < n ; i++){
        for(j=0;j<n; j++){
            res[i][j] =0;
            if (i>j){
                tmp = j;
            }else {
                tmp = i;
            }
            for (k = 0; k < tmp ; k++){//cette tour de boucle n'est pas de complexite O(n) mais de O(1)
                res[i][j] += mat1[i][k] * mat2[k][i];
            }
        }
    }

    return res;
    
}

