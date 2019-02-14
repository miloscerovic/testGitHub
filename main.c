#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define COUPS_MAX 80
//cacanisette

static void afficher_aide();
static void afficherMenu();
static int isGameOver(int grille[100]);
static void login(char pseudos[20]);
char pseudos[20];
int nmbcoup = 0; //variable permettant de compter le nombre de coup
int main()
{
    int choix,x,y ; // Cette variable permet de trouver l'emplacement dans la grille
    int quitter = 1; //Cette variable permet a l'utilisiateur de quitter le programme dans le menu
    int continuer = 1; // Cette variable permet au programme de re afficher le menu
    int condition_continuer = 1; // Cette variable permet au programme de rester dans une boucle for et de continuer une partie
    int grille[100] ; //Grille a une dimension de 10 sur 10. Les 0 sont l'eau et les chiffres des bateaux
    char grille_2[100] ; //Creation du tableau qui sera afficher a l'utilisateur

    for (int i = 0; i<100; i++)
    {
        grille_2[i] = 'O';
    }
    login(pseudos);

    while(continuer==1)//Permet au programme de revenir dans le menu
    {
        afficherMenu();
        scanf("%d",&choix);//L'utilisateur choisi parmi plusieurs options proposées
        choisir_menu(choix,&continuer,condition_continuer,x,y,grille,grille_2);
    }
    return EXIT_SUCCESS;
}


/** \brief  asdsad asd asd asd asd asd asd
 *
 * \param
 * \param
 * \return
 *
 */
void choisir_menu (int choix, int *continuer, int condition_continuer, int x, int y, int grille[100], char grille_2[100])
{
    int i = 1; //initialisation de la grille
    int valeurGrille = 1;
    int choixGrille = 1;
    int testchar = 0;
    int touche_coule = 0;
    char sortie = ' '; //Pour la sortie des scores
    char retourAcc = ' ';
    char fichierGrille = ' ';

    FILE *log = NULL; //Pour ouvrir le fichier pour les logs
    nmbcoup = 0; //a chaque fois que l'utilisateur retourn dans le jeu la valeur est remise a 0

    switch (choix)
    {
        case 1 :
            srand(time(NULL));
            choixGrille = rand()% 3;
            switch (choixGrille)
            {
                case 0 :
                    log = fopen("Grille1.txt","r");
                    break;
                case 1 :
                    log = fopen("Grille2.txt","r");
                    break;
                case 2 :
                    log = fopen("Grille3.txt","r");
                    break;
            }

            if(log!=NULL)
            {
                i=0;
                do
                {
                    fichierGrille = fgetc(log);
                    valeurGrille = fichierGrille - 48;
                    grille[i]= valeurGrille;
                    i++;
                }while(fichierGrille != EOF);
            }
            else
            {
                printf("\nProbleme ouverture de la grille\n");
            }

            fclose(log);

            for (int i=0;i<100;i++)
            {
                grille_2[i]='O';
            }

            while (condition_continuer == 1)
            {
                system("cls");
                printf("   1 2 3 4 5 6 7 8 9 10\n"); //affichage du quadrillage 1 à 10 colonne et lignes

                for(int j=0; j<10; j++)
                {
                    printf("%2i ", j + 1);
                    for(int i=0; i<10; i++)
                    {
                        printf("%c ",grille_2[j*10+i]);
                    }
                    printf("\n");
                }
                touche_coule = 0;
                printf("\n\n\t\tNombre de coup actuel : %i\n\n",nmbcoup);
                printf("\n\n\t\tCoup restant : %i\n\n",COUPS_MAX-nmbcoup);

                do //Placement des point donnes par l'utilisateur
                {
                    printf("\nVeuillez mettre une ligne x entre 1 et 10 : "); //L'utilisateur met une ligne
                    fflush(stdin);
                    testchar=scanf("%i",&x);//Verification si le scanf est un int
                }while((x>10 || x<=0) || testchar == 0);

                do
                {
                    printf("\nVeuillez mettre une colonne y entre 1 et 10 : "); //L'utilisateur met une colone
                    fflush(stdin);
                    testchar=scanf("%i",&y);
                }while((y>10 || y<=0) || testchar == 0);

                system("cls");

                int case_cible = (x - 1)*10 + (y - 1); //Calcul savant pour selectionner la case ciblée par l'utilisateur
                if(grille[case_cible]>0)
                {
                    grille[case_cible]-= 2*grille[case_cible]; //Change les valeurs dans la grille cachée
                    touche_coule = couler(grille,case_cible); //implemantation de la fonction permettant de verifier le touche coule
                    if(touche_coule)
                    {
                        printf("\nTouche coule !\n\n\n\n");
                        nmbcoup++;
                        Sleep(1000);
                        system("cls");
                    }
                    else
                    {
                        printf("\nTouche !\n\n\n\n");
                        nmbcoup++;
                        Sleep(1000);
                        system("cls");
                    }
                    grille_2[case_cible] = 'X';
                }
                else if(grille[case_cible]<0) //Verification si la case a deja ete choisie
                {
                    printf("Veuillez choisir une autre case\n\n");
                    Sleep(1000);
                    system("cls");
                }
                else
                {
                    printf("\nRater !\n\n\n");
                    grille[case_cible]= -12; //Les valeurs des cases de la mer sont changées en -12.
                    grille_2[case_cible] = '~';//Les "O" sont changé en -12
                    nmbcoup++;
                    Sleep(1000);
                    system("cls");
                }
                if(isGameOver(grille) == 1)
                {
                    condition_continuer = 0;
                }
                printf("   1 2 3 4 5 6 7 8 9 10\n"); //affichage du quadrillage 1 à 10 colonne et lignes
                for(int j=0; j<10; j++)
                {
                    printf("%2i ", j + 1);
                    for(int i=0; i<10; i++)
                    {
                        printf("%c ",grille_2[j*10+i]);
                    }
                    printf("\n");
                }

                system("cls");

            }
            //***************************LOG******************
            log = fopen("scoreLog.txt", "a+");
            if(log != NULL)
            {
                if(nmbcoup<COUPS_MAX)
                {
                     fprintf(log, "%s gagne avec %i coups\n", pseudos, nmbcoup);
                }
                else
                {
                     fprintf(log, "%s perdu avec %i coups\n", pseudos, nmbcoup);
                }
            }
            else
            {
                printf("Erreur ouverture fichier scoreLog");
            }
            fclose(log);
            printf("\n\n\t\tNombre de coup durant la partie : %i\n\n",nmbcoup);
            if(nmbcoup<COUPS_MAX)
            {
              printf("\n\n\nBravo vous avez coule tous les bateaux!\n\n\n");
            }
            else
            {
                printf("\n\n\nDommage vous avez perdu. Peut etre la prochaine fois. ");
            }
            Sleep(3000);
            system("cls");
            *continuer = 1;
            break;
        case 2 :
            system("cls");
            printf("\n\t\tBienvenue dans le leaderboard\n");
            //Affichage des scores
            log = fopen("scoreLog.txt", "a+");
            if(log != NULL)
            {
                printf("\t\t");
                do
                {
                    sortie = fgetc(log);
                    printf("%c", sortie);
                    if(sortie == '\n')
                    {
                        printf("\t\t");
                    }
                }while(sortie != EOF);
            }
            else
            {
                printf("Erreur ouverture fichier scoreLog");
            }
            fclose(log);
            do
            {
                printf("\nVeuillez appuyer sur enter pour revenir au menu : ");
                fflush(stdin);
                scanf("%c",&retourAcc);
                system("cls");
            }while(retourAcc != '\n');
            break;
        case 3 : afficher_aide();
            break;
        case 4 :
            system("cls");
            printf("\n\nAu revoir !\n\n\n\n");
            *continuer = 0;
            break;
    }
}

/** \brief afficher_aide - Cette fonction permet d'afficher l'aide
 *
 * \return void
 *
 */
static void afficher_aide()
{
    char suivant;

    system("cls");
    scanf("%c",&suivant);
    printf("\n\nBienvenue dans le menu aide !\n");
    printf("\nIci vous aller apprendre a jouer a la bataille navale.");
    printf("\n\nQuel est le but de la bataille navale ?");
    printf("\n\nLe but est tres simple. Il faut toucher les bateaux dans votre grille.");
    printf("\nDes qu'un bateau est touche il faudra retoucher une de ses parties pour le couler.");
    printf("\n\nUn message disant <toucher> sera affiche.");
    printf("\nS'il ne reste plus aucune partie du bateau un message disant <touche couler> sera afficher.");
    printf("\nLorsqu'il n'y a plus de bateau dans la grille vous aurez gagne.");
    printf("\n\nAppuyez sur enter pour continuer.");
    scanf("%c",&suivant);
    system("cls");
    printf("\n\nComment lancer une partie ?");
    printf("\n\nPour lancer une partie vous devez etre dans le menu principal.");
    printf("\n\nUn menu avec plusieurs choix s'offre a vous.");
    printf("\nAppuyez sur la touche 1 puis enter.");
    printf("\nVous etes entre dans le menu <choix de la grille et jouer>.");
    printf("\n\nAppuyez sur enter pour continuer.");
    scanf("%c",&suivant);
    system("cls");
    printf("\n\nComment jouer a la bataille navale ?");
    printf("\n\nVous avez choisi votre grille et vous vous apprete a jouer.");
    printf("\nUne grille s'affiche devent vous constitue de <o>.");
    printf("\nCette grille a un quadrillage de 10 sur 10.");
    printf("\nLes colonnes vont de 1 a 10 de meme pour les lignes.");
    printf("\n\nPour lancer un missile choisissez en premier une ligne de 1 a 10 puis appuyez sur enter.");
    printf("\nPuis choissiez une colonne pour lancer votre bombe.");
    printf("\nSi vous touchez un bateau il prendra la forme d'un <X>.");
    printf("\nSi vous ratez alors il prendra la forme d'un <~>.");
    printf("\nSi vous relancer un missile au meme endroit un message d'erreur s'affichera.");
    printf("\nVous pourrez quand meme retirer.");
    printf("\n\nAppuyez sur enter pour continuer.");
    scanf("%c",&suivant);
    system("cls");
    printf("\n\nComment quitter le programme ?");
    printf("\n\nTrois manieres s'offrent a vous.");
    printf("\nLa premiere est lorsque vous etes dans le menu d'accueil il vous suffit d'appuyer sur 4 puis enter.");
    printf("\nLa deuxieme est d'appuyer sur <ctrl+c>.");
    printf("\nEt enfin la derniere est de simplement quitter le programme avec la croix rouge de meme avec <alt+f4>.");
    printf("\n\nAppuyez sur enter pour revenir au menu accueil.");
    scanf("%c",&suivant);
    system("cls");
}

/** \brief
 *
 * \return void
 *
 */
static void afficherMenu()
{
    printf("\n\t\tBienvenue dans la bataille navale");
    printf("\n\n\t           VOUS ETES DANS LE MENU       ");
    printf("\n\t-----------------------------------------");
    printf("\n\tTapez 1 pour choisir une grille et jouer");
    printf("\n\tTapez 2 pour voir les scores");
    printf("\n\tTapez 3 pour afficher l'aide");
    printf("\n\tTapez 4 pour quitter");
    printf("\n\t------------------------------------------");
    printf("\n\tMettez votre choix puis appuyez sur entrer  ");
}

/** \brief
 *
 * \param grille[100] int
 * \return int
 *
 */
static int isGameOver(int grille[100])
{
    for(int i=0; i<100; i++) //verification de la grille s'il reste des bateaux ou non
    {
        if(grille[i]>0)
        {
            return 0;
        }
    }
    return 1;
}

/** \brief
 *
 * \param pseudos[20] char
 * \return void
 *
 */
static void login(char pseudos[20])
{
    do //L'utilisateur se log
    {
        printf("\nVeuillez mettre votre pseudos : ");
        scanf("%s",&pseudos[0]); //Stockage du pseudos dans un tableau de caractère
        if (strlen(pseudos)>20)
        {
            system("cls");
            printf("\nVeuillez mettre un pseudos qui fait 20 caractres MAX\n");
            Sleep(1500);
        }
        else
        {
            system("cls");
            printf("\n\nBonjour %s\n\n\n",pseudos);
            Sleep(2000);
            system("cls");
        }
    }while(strlen(pseudos)>20);
}
int couler(int grille[100], int case_cible)
{
    int bateau = grille[case_cible];
    int sommeverif = 0;

    for(int i=0; i<100; i++)
    {
        if(grille[i]== -1 * bateau)
        {
            sommeverif += 1;
        }
    }
    if(sommeverif)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

