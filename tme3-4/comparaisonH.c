#include "biblioH.h"
// #include "biblioLC.h"
#include "entreeSortieH.h"
// #include "entreeSortieLC.h"
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("veuilez entrer le nom du fichier a lire\n");
        return 0;
    }
    char *nomfic = argv[1];
    int nb_lignes;
    printf("Combien de lignes du fichier voulez vous lire ?\n");
    scanf("%d",&nb_lignes);

    BiblioH* b_hachage = charger_n_entrees_h(nomfic, nb_lignes);
    // Biblio* b_lc = charger_n_entrees(nomfic, nb_lignes);

    int n; 
    for(n = 0 ; n <  nb_lignes; n++){
        clock_t temps_initial; 
        clock_t temps_final;
        double temps_cpu;


        // Avec liste chainée.
        // temps_initial = clock();
        
        // temps_final = clock();
        // temps_cpu = ((double)(temps_final -temps_initial));
        // printf("%d %f\n",nbligne_alire ,temps_cpu);


        // Avec hachage.
        temps_initial = clock();
        recherche_ouvrage_num(b_hachage, nb_lignes);
        temps_final = clock();
        temps_cpu = ((double)(temps_final -temps_initial));
        printf("Temps pour rechercher livre n°%d avec une table de hachage : %.1f\n",nb_lignes ,temps_cpu);
        

    }

    return 0;
}