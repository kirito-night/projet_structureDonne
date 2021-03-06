#include "biblioLC.h"
#include "entreeSortieLC.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Pour obtenir le temps de calcul avec une liste chainée.

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("veuilez entrer le nom du fichier à lire.\n");
        return 0;
    }
    char *nomfic = argv[1];
    int nb_lignes;
    printf("Combien de lignes du fichier voulez vous lire ?\n");
    scanf("%d",&nb_lignes);


    FILE *f = fopen("sortie_vitesse.txt", "w");  /* Ouverture du fichier pour gnuplot */
    if(f == NULL){
        printf("erreur d'ouverture de fichier");
        exit(1);
    }

    clock_t temps_initial; 
    clock_t temps_final;
    double temps_cpu;
    Biblio* b_LC = charger_n_entrees(nomfic, nb_lignes);

    
    /* Recherche avec le numero du livre. */
    
    // int n; 
    // for(n = 0 ; n <  nb_lignes; n++){
    //     temps_initial = clock();
    //     recherche_ouvrage_num(b_LC, n);
    //     temps_final = clock();
    //     temps_cpu = ((double)(temps_final -temps_initial));
    //     printf("Temps pour rechercher le livre n°%d avec une liste chainée : %.1f\n",n ,temps_cpu);
    // }

    
    /* Recherche à partir du nom d'un auteur */

    // char* auteur = (char*) malloc(sizeof(char) * 50);
    // printf("Veuillez saisir l'auteur du livre que vous recherchez\n");
    // scanf("%s",auteur);
    // temps_initial = clock();
    // recherche_ouvrage_auteur(b_LC, auteur);
    // temps_final = clock();
    // temps_cpu = ((double)(temps_final -temps_initial));
    // printf("Temps pour rechercher le livre écrit par %s avec une liste chainée : %.1f\n", auteur,temps_cpu);

    
    /* Recherche à partir du nom du livre */

    char* titre = (char*) malloc(sizeof(char) * 50);
    printf("Veuillez saisir le titre du livre que vous recherchez\n");
    scanf("%s",titre);
    temps_initial = clock();
    recherche_ouvrage_titre(b_LC, titre);
    temps_final = clock();
    temps_cpu = ((double)(temps_final -temps_initial));
    printf("Temps pour rechercher le livre %s avec liste chainée : %.1f\n", titre,temps_cpu);

    fclose(f);  /* Fermeture du fichier pour gnuplot */

    return 0;
}