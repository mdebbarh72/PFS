#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

#define max_animaux 200
#define max_especes 50
#define taille 50
#define max_habitats 20

typedef struct{

    int id;
    char nom[taille];
    char espece[taille] ;
    char habitat[taille];
    int age;
    float poids;
    struct tm date_inscription;
    char categorie[taille];

}animal;

typedef struct 
{
    int id;
    char espece[taille];
    char habitat[5][taille];
    int nbr_habitat;
    int max_age;
    float max_poids;
    char categorie[taille];
}DB;

DB animaux_data[max_especes]=
{
    {0, "lion", {"Savane","Jungle"}, 2, 16, 200, "carnivore"},
    {1, "tigre", {"Savane","Jungle"}, 2, 26, 300, "carnivore"},
    {2, "girafe", {"Savane","Jungle"}, 2, 25, 1400, "herbivore"}
};

int menu();
void ajouter();
animal remplir_animal(int);
int test_nom(char[]);
int saisie_espece();
int saisie_habitat( int );
int saisie_age(int);
float saisie_poids(int );
void afficher();
int menu_affichage();
void afficher_list_complet();
void afficher_un_animal( int );
void trie_par_nom();
void trie_par_age();
void rechercher_par_habitat();
int selectionner_habitat();
void modifier();
int modification_menu();
void modifier_habitat();
int recherche_par_id(int);
int recherche_espece(char [] );
void modifier_age();
void supprimer();
void rechercher();
int recherche_menu();
int recherche_par_nom(char[]);
void rechercher_par_espece();
void statistiques();
int stat_menu();
float moyen_age();
void max_max_age();
void plus_present();
void trier(int []);



char habitats[max_habitats][taille]={"Savane", "Jungle"};

int nbr_espece=3;
int nbr_animaux=0;
int id_generateur=0;
int nbr_habitat=2;
animal animaux[max_animaux];




int main()
{
    
    int quitter=1;

    do{
        switch(menu())
    {
        case 1: ajouter(); break;

        case 2: afficher(); break;

        case 3: modifier(); break;

        case 4: supprimer(); break; 

        case 5: rechercher(); break;

        case 6: statistiques(); break;

        case 0: quitter=0; break;

    }

    }while(quitter);
    
    return 0;
}

int menu()
{
    
    int choix;

    do
    {
        printf("menu:\n");
        printf("\t1- Ajouter un animal.\n");
        printf("\t2- Afficher les animaux.\n");
        printf("\t3- Modifier un animal.\n");
        printf("\t4- Supprimer un animal.\n");
        printf("\t5- Rechercher un animal.\n");
        printf("\t6- Afficher des statistiques.\n");
        printf("\t0- Quitter le program.\n");

        printf("Votre choix est:");
        scanf("%d", &choix);

        if(choix < 0 || choix >6)
            printf("choix invalide!\n");
    }while(choix < 0 || choix >6);

    return choix;

}

void ajouter()
{
    if( nbr_animaux==max_animaux)
    {
        printf("impossile d\'ajouter un animal, vous avez atteint le nombre maximum des animaux autorises!\n");
        return;
    }

    int nbr_a_ajouter, choix;

    printf("entrer le nombre d\'animaux que tu veux ajouter, max 200: ");
    scanf("%d", &nbr_a_ajouter);

    if(nbr_a_ajouter<1 || nbr_a_ajouter > max_animaux)
    {
        printf("nombre invalide!\n");
        return ajouter();
    }

    if(nbr_a_ajouter+nbr_animaux> max_animaux)
    {
        printf("impossile d\'ajouter %d animaux, Il ne reste que %d places libres dans la zoo.\n", nbr_a_ajouter, max_animaux-nbr_animaux);

        do
        {
            printf("1- Changer le nombre des animaux qui tu veux ajouter.\n");
            printf("0- Quitter l\'operation.\n");
            scanf("%d", &choix);

            if(choix != 1 && choix != 0)
                printf("choix invalide!\n");

        } while (choix != 1 && choix != 0);

        if(choix)
            return ajouter();
        else
            return ;
    }
    
    for(int i=0; i<nbr_a_ajouter; i++)
    {
        animaux[nbr_animaux++] = remplir_animal(i);
        
    }

}

animal remplir_animal(int i)
{
    animal un_animal;
    int indice;

    while(getchar()!='\n');
    do{
        printf("entrer le nom de l\'animal %d: ",i+1 );
        fgets(un_animal.nom, taille, stdin);
        un_animal.nom[strcspn(un_animal.nom, "\n")]= '\0';
    }while(test_nom(un_animal.nom) || recherche_par_nom(un_animal.nom)>=0);

    indice = saisie_espece();

    strcpy(un_animal.espece, animaux_data[indice].espece);

    strcpy(un_animal.habitat, animaux_data[indice].habitat[saisie_habitat(indice)]);

    un_animal.age= saisie_age(indice);
    un_animal.poids= saisie_poids(indice);

    time_t date=time(NULL);
    struct tm *t=localtime(&date);

    un_animal.date_inscription= *t;

    strcpy(un_animal.categorie, animaux_data[indice].categorie);

    un_animal.id= id_generateur++;

    return un_animal;
}

int test_nom(char nom[])
{
    if(strlen(nom)<3)
    {
        printf("le nom est tres petit!\n");
        return 1;
    }

    for(int i=0; nom[i]; i++)
    {
        if(nom[i]<'A' || (nom[i]>'Z' && nom[i]<'a') || nom[i]>'z')
        {
            printf("juste les alphabets sont autoriser!\n");
            return 1;
        }
    }

    return 0;

}

int saisie_espece()
{
    
    int choix;

    do
    {
        printf("Choisir un espece:\n");
        for(int i=0; i<nbr_espece; i++)
        {
            printf("\t %d- %s\n", i+1, animaux_data[i].espece);
        }
        printf("Votre choix est: ");
        scanf("%d", &choix);
        
        if(choix < 1 || choix > nbr_espece)
       
            printf("Choix invalide!\n");

    }while(choix < 1 || choix > nbr_espece);

    choix--;
    return choix;
}

int saisie_habitat(int indice)
{
    int choix;

    while(getchar()!='\n');

    do
    {
        printf("Choisir une habitat:\n");
        for(int i=0; i<animaux_data[indice].nbr_habitat; i++)
        {
            printf("\t %d- %s\n", i+1, animaux_data[indice].habitat[i]);
        }
        printf("Votre choix est: ");
        scanf("%d", &choix);
        
        if(choix < 1 || choix >animaux_data[indice].nbr_habitat)
       
            printf("Choix invalide!\n");

    }while(choix < 1 || choix > animaux_data[indice].nbr_habitat);

    choix--;

    return choix;
    
}

int saisie_age(int indice)
{
    int age;

    do
    {
        printf("Entrer l\'age: ");
        scanf("%d", &age);

        if(age < 1)
            printf("Age tres petit!\n");
        else if(age > animaux_data[indice].max_age)
            printf("Age tres grand!, le maximum age de %s est: %d\n", animaux_data[indice].espece, animaux_data[indice].max_age);
    }while(age < 1 || age > animaux_data[indice].max_age);

    return age;
}

float saisie_poids(int indice)
{
    float poid;

    do
    {
        printf("Entrer le poid: ");
        scanf("%f", &poid);

        if(poid < 1)
            printf("poid tres petit!\n");
        else if(poid > animaux_data[indice].max_poids)
            printf("poid tres grand!, le maximum poid de  %s est: %2.f\n",animaux_data[indice].espece, animaux_data[indice].max_poids);
    }while(poid < 1 || poid > animaux_data[indice].max_poids);

    return poid;
}

int menu_affichage()
{
    int choix;

    do
    {
        printf("menu d\'affichage:\n");
        printf("\t1- Afficher la list complet des animaux.\n");
        printf("\t2- Afficher la list trie par nom. \n");
        printf("\t3- Afficher la list trie par age.\n");
        printf("\t4- Afficher les animaux d\'un habitat specifique.\n");

        printf("Votre choix est:");
        scanf("%d", &choix);

        if(choix < 1 || choix >4)
            printf("choix invalide!\n");
    }while(choix < 1 || choix >4);

    return choix;

}

void afficher()
{
    switch(menu_affichage())
    {
        case 1: afficher_list_complet();break;

        case 2: trie_par_nom(); afficher_list_complet(); break;

        case 3: trie_par_age(); afficher_list_complet(); break;
        
        case 4: rechercher_par_habitat(); break;
    }
}

void afficher_list_complet()
{
    if(nbr_animaux == 0)
    {
        printf("la list est vide!\n");
        return;
    }

    printf("|  id |      nom      |    espece    | categorie |   habitat    | age | poids   |    date_inscription    |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for(int i=0; i<nbr_animaux; i++)
    {
        afficher_un_animal (i);      
    }
}

void afficher_un_animal(int indice)
{
    printf("| %-3d |   %-10s  |  %-10s  | %10s |  %-10s  | %-2d  | %7.2f | %-02d/%-02d/%-04d  %-02d:%-02d:%-02d |\n",
            animaux[indice].id, 
            animaux[indice].nom,
            animaux[indice].espece,
            animaux[indice].categorie,
            animaux[indice].habitat,
            animaux[indice].age,
            animaux[indice].poids,
            animaux[indice].date_inscription.tm_mday,
            animaux[indice].date_inscription.tm_mon+1,
            animaux[indice].date_inscription.tm_year+1900,
            animaux[indice].date_inscription.tm_hour,
            animaux[indice].date_inscription.tm_min,
            animaux[indice].date_inscription.tm_sec
            );
    printf("------------------------------------------------------------------------------------------------------\n");
}

void trie_par_nom()
{
    int i_min=0;
    animal temp;

    for(int i=0; i<nbr_animaux-1; i++)
    {
        i_min=i;
        for(int j=i+1; j<nbr_animaux; j++)
        {
            if(strcmp(animaux[i_min].nom, animaux[j].nom)>0)
                i_min=j;
        }
        temp=animaux[i_min];
        animaux[i_min]=animaux[i];
        animaux[i]=temp;
    }
}

void trie_par_age()
{
    int i_min=0;
    animal temp;

    for(int i=0; i<nbr_animaux-1; i++)
    {
        i_min=i;
        for(int j=i+1; j<nbr_animaux; j++)
        {
            if(animaux[i_min].age < animaux[j].age)
                i_min=j;
        }
        temp=animaux[i_min];
        animaux[i_min]=animaux[i];
        animaux[i]=temp;
    }
}

void rechercher_par_habitat()
{
    int indice=selectionner_habitat();
    int test=1;

    for(int i=0; i<nbr_animaux; i++)
    {
        if(strcmp(habitats[indice], animaux[i].habitat)==0)
        {
            afficher_un_animal(i);
            test=0;
        }    

    }

    if(test)
        printf("pas d\'animal dans la zoo avec cette habitat\n");

}

int selectionner_habitat()
{
    int choix;

    printf("selectionner une habitat:\n");
    do
    {
        for(int i=0; i<nbr_habitat; i++)
        {
            printf("\t %d- %s\n", i+1, habitats[i]);
        }

        printf("Votre choix est: ");
        scanf("%d", &choix);
        
        if(choix < 1 || choix >nbr_habitat)
            printf("Choix invalide!\n");

    }while(choix < 1 || choix > nbr_habitat);

    choix--;

    return choix;

}

void modifier()
{
    switch(modification_menu())
    {
        case 1: modifier_habitat(); break;

        case 2: modifier_age(); break; 
    }

}

int modification_menu()
{
    int choix;

    do
    {
        printf("menu de modefication:\n");
        printf("\t1- Modifier l\'habitat d\'un animal.\n");
        printf("\t2- Modifier l\'age d\'un animal.\n");

        printf("Votre choix est:");
        scanf("%d", &choix);

        if(choix != 1 && choix != 2)
            printf("choix invalide!\n");
    }while(choix != 1 && choix != 2);

    return choix;
}

void modifier_habitat()
{
    int id;
    int indice_animal, indice_espece, indice_habitat;
    int confirmation;
    do
    {
        printf("entrer l\'id de l\'animal:");
        scanf("%d", &id);

        indice_animal= recherche_par_id(id);

        if(indice_animal==-1)
            printf("cet id n\'existe pas dans la zoo!\n");

    }while(indice_animal==-1);

    indice_espece= recherche_espece(animaux[indice_animal].espece);

    afficher_un_animal(indice_animal);

   do
   {
        printf("confirmation: \n");
        printf("1- modifier cet animale.\n");
        printf("0- annuler la modefication.\n");
        scanf("%d", &confirmation);

        if(confirmation != 0 && confirmation != 1)
            printf("choix invalide!\n");

   }while(confirmation != 0 && confirmation != 1);

   indice_habitat= saisie_habitat(indice_espece);

   strcpy(animaux[indice_animal].habitat, animaux_data[indice_espece].habitat[indice_habitat]);

   printf("habitat modifie avec succse!\n");

}

int recherche_par_id( int id)
{
    for(int i=0; i<nbr_animaux; i++)
    {
        if(id==animaux[i].id)
            return i;
    }

    return -1;
}

int recherche_espece(char espece[] )
{
    for(int i=0; i<nbr_espece; i++)
    {
        if(strcmp(espece, animaux_data[i].espece)==0)
            return i;
    }
}

void modifier_age()
{
    int id;
    int indice_animal, indice_espece, indice_habitat;
    int confirmation;
    do
    {
        printf("entrer l\'id de l\'animal:");
        scanf("%d", &id);

        indice_animal= recherche_par_id(id);

        if(indice_animal==-1)
            printf("cet id n\'existe pas dans la zoo!\n");

    }while(indice_animal==-1);

    indice_espece= recherche_espece(animaux[indice_animal].espece);

    afficher_un_animal(indice_animal);

   do
   {
        printf("confirmation: \n");
        printf("1- modifier cet animale.\n");
        printf("0- annuler la modefication.\n");
        scanf("%d", &confirmation);

        if(confirmation != 0 && confirmation != 1)
            printf("choix invalide!\n");

   }while(confirmation != 0 && confirmation != 1);

   animaux[indice_animal].age= saisie_age(indice_espece);

   printf("age modifie avec succse!");

}

void supprimer()
{
    int id;
    int indice_animal;
    int confirmation;
    do
    {
        printf("entrer l\'id de l\'animal:");
        scanf("%d", &id);

        indice_animal= recherche_par_id(id);

        if(indice_animal==-1)
            printf("cet id n\'existe pas dans la zoo!\n");

    }while(indice_animal==-1);

    afficher_un_animal(indice_animal);

   do
   {
        printf("confirmation: \n");
        printf("1- supprimer cet animale.\n");
        printf("0- annuler la suppression.\n");
        scanf("%d", &confirmation);

        if(confirmation != 0 && confirmation != 1)
            printf("choix invalide!\n");

   }while(confirmation != 0 && confirmation != 1);

   if(confirmation==0)
        return;
   for(int i=indice_animal; i<nbr_animaux-1; i++)
   {
        animaux[i]=animaux[i+1];
   }

   nbr_animaux--;

   printf("animal supprime avec succse!");
}

void rechercher()
{
    int annulation;
    switch(recherche_menu())
    {
        case 1: int indice_animal, id;

            printf("entrer l\'id de l\'animal:");
            scanf("%d", &id);

            indice_animal= recherche_par_id(id);

            if(indice_animal==-1)
            {
                printf("cet id n\'existe pas dans la zoo!\n");
                
                do
                {
                    printf("effectuer un autre recherche:\n");
                    printf("\t1- effectuer.\n");
                    printf("\t0- annuler.\n");
                    scanf("%d", &annulation);

                    if(annulation==1)
                        return rechercher();
                    else if(annulation==0)
                        return ;
                } while (annulation != 0 && annulation != 1);
                
            }

        afficher_un_animal(indice_animal);
        
        break;

        case 2: int indice ;
                char nom[taille];

                while(getchar()!='\n');
                fgets(nom, taille, stdin);
                nom[strcspn(nom, "\n")]= '\0';

                indice =recherche_par_nom(nom);
                if(indice==-1)
                {
                    printf("cet nom n\'existe pas dans la zoo!\n");

                    do
                    {
                        printf("effectuer un autre recherche:\n");
                        printf("\t1- effectuer.\n");
                        printf("\t0- annuler.\n");
                        scanf("%d", &annulation);

                        if(annulation==1)
                            return rechercher();
                        else if(annulation==0)
                            return ;
                    } while (annulation != 0 && annulation != 1);
                }
                afficher_un_animal(indice);
         break; 

         case 3: rechercher_par_espece(); break;
    }

}

int recherche_menu()
{
    int choix;

    do
    {
        printf("menu du recherche:\n");
        printf("\t1- Rechercher par id.\n");
        printf("\t2- Rechercher par nom.\n");
        printf("\t3- Rechercher par espece.\n");

        printf("Votre choix est:");
        scanf("%d", &choix);

        if(choix < 1 && choix > 3 )
            printf("choix invalide!\n");
    }while(choix < 1 && choix >3 );

    return choix;
}

int recherche_par_nom(char nom[])
{
    for(int i=0; i<nbr_animaux; i++)
    {
        if(strcmpi(nom, animaux[i].nom)==0)
            return i;
    }
    return -1;     
}

void rechercher_par_espece()
{
    int indice=saisie_espece() ;
    int non_trouve=1, annulation;
    
    for(int i=0; i<nbr_animaux; i++)
    {
        if(strcmp(animaux_data[indice].espece, animaux[i].espece)==0)
        {
            afficher_un_animal(i);
            non_trouve=0;
        }
    }

    if(non_trouve)
    {
        do
        {
            printf("effectuer un autre recherche:\n");
            printf("\t1- effectuer.\n");
            printf("\t0- annuler.\n");
            scanf("%d", &annulation);

            if(annulation==1)
                return rechercher();
            else if(annulation==0)
                return ;
        } while (annulation != 0 && annulation != 1);
    }
}

void statistiques()
{
     switch(stat_menu())
    {
        case 1: printf("le nombre total d\'animaux dans le zoo est: %d.\n", nbr_animaux); break;

        case 2: printf("\t2- l\'age moyen des animaux est: %.2f\n", moyen_age()); break;

        case 3: max_max_age(); break;
        
        case 4: plus_present(); break;
    }
}

int stat_menu()
{
    int choix;

    do
    {
        printf("menu de statistiques:\n");
        printf("\t1- Afficher Nombre total d\'animaux dans le zoo.\n");
        printf("\t2- Afficher l\'age moyen des animaux.\n" );
        printf("\t3- Afficher les Plus vieux et plus jeune animal.\n");
        printf("\t4- Afficher les especes les plus representes.\n");

        printf("Votre choix est:");
        scanf("%d", &choix);

        if(choix < 1 || choix >4)
            printf("choix invalide!\n");
    }while(choix < 1 || choix >4);

    return choix;
}

float moyen_age()
{
    int somme=0;
    
    for(int i=0; i<nbr_animaux; i++)
    {
        somme+=animaux[i].age;
    }

    return (float)somme/nbr_animaux;
}

void max_max_age()
{
    int i_max_age, i_min_age;

    i_max_age=i_min_age=0;
    for(int i=1; i<nbr_animaux; i++)
    {
        if(animaux[i_max_age].age< animaux[i].age)
            i_max_age=i;
        if(animaux[i_min_age].age> animaux[i].age)
            i_min_age=i;
    }
    
    printf("l\'animal le plus vieux:\n");
    afficher_un_animal(i_max_age);
    printf("l\'animal le plus jeune:\n");
    afficher_un_animal(i_min_age);
}

void plus_present()
{
    int nbr_presence[max_especes];
    int cmp;
    for(int i=0; i<nbr_espece; i++)
    {
        cmp=0;

        for(int j=0; j<nbr_animaux; j++)
        {
            if(strcmp(animaux_data[i].espece, animaux[j].espece)==0 )
                cmp++;
        }
        nbr_presence[i]=cmp;
    }

    trier(nbr_presence);

    printf("les espece les plus present sont: %s, %s, %s.\n",animaux_data[0].espece, animaux_data[1].espece, animaux_data[2].espece);
    
}

void trier(int nbr[])
{
    int i_min=0;
    int temp;

    for(int i=0; i<nbr_espece-1; i++)
    {
        i_min=i;
        for(int j=i+1; j<nbr_animaux; j++)
        {
            if(nbr[i_min] < nbr[j])
                i_min=j;
        }
        temp=nbr[i_min];
        nbr[i_min]=nbr[i];
        nbr[i]=temp;
    }  
}



