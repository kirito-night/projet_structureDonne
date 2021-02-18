#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void menu(){
    putchar('\n');
    printf("##########\n");
    putchar('\n');
    printf("entrer 0 pour sortir du programme \n");

    printf("entrer 1 pour afficher la bibliotheque \n");
    printf("entrer 2 pour inserer un ouvrage a la tete de la bibliotheque  \n");
    printf("entrer 3 pour supprimer un ouvrage avec son num son titre et son auteur\n");
    printf("entrer 4 pour rechercher un ouvrage dans la bibliotheque \n");
    putchar('\n');


}
int main(int argc, char* argv[]){
    if(argc != 3){
        printf("veuilez entrer le nom du fichier a lire et le nb de ligne a lire\n");
        return 0;
    }
    char *nomfic = argv[1];
    int nbligne_alire = atoi(argv[2]);

    Biblio *b  = charger_n_entrees(nomfic,nbligne_alire);
   
    int rep;

    do{
        menu();
        printf("entrer votre choix : ");
        scanf("%d", &rep);
        
        switch (rep){
        case 1:
            /* code */
            putchar('\n');
            printf("##########\n");
            putchar('\n');
            afficherBiblio(b);

            break;
        case 2: 
            putchar('\n');
            printf("##########\n");
            putchar('\n');
            //char buffer[256];
            int num;
            char titre[100], auteur[100];
            printf(" veuillez entre le num , le titre et l'auteur de l'ouvrage : ");
            //fgets(buffer, 256, stdin);
            //sscanf(buffer, "%d %s %s",&num ,titre, auteur);
            scanf( "%d %s %s",&num ,titre, auteur);
            inserer_en_tete(b,num,titre,auteur);

            break;
        case 3 :
            //int num;
            //char titre[100], auteur[100];
            printf(" veuillez entre le num , le titre et l'auteur de l'ouvrage : ");
            scanf( "%d %s %s",&num ,titre, auteur);
            printf("%d %s %s\n", num, titre, auteur);
            suppression_ouvrage(b,num,titre,auteur);
            
            break;
        default:
            printf("saisie invalide\n");
            break;
        }
    }while (rep!=0);
    printf("vous etes sorti de la boucle\n");
    liberer_biblio(b);
    return 0;
}