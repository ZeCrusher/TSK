#include <stdio.h>                                     /* scanf, printf, gets */
#include <stdlib.h>                                     /* malloc, free, exit */
#include <conio.h>                                           /* getche, getch */
#include <string.h>                                         /* strcmp, strcpy */
#include <bios.h>                                            /* bioskey */
/***********  Macro pour en-tˆte de page d'‚cran  ******************/

typedef struct liste_fichier
{
	char nom_fichier[80];

	struct liste_fichier *premier_fichier;            /* pointeur vers ‚l‚ment pr‚c‚dent */
	struct liste_fichier *suivant_fichier;           /* pointeur vers ‚l‚ment suivant */
};




liste_fichier *debut_liste;                         /* pointeur vers d‚but de liste */
liste_fichier *fin_liste;                           /* pointeur vers fin de liste */
liste_fichier *nouvel_element;                       /* pointeur vers nouvel ‚l‚ment */
liste_fichier *dernier_inserer;            /* pointeur vers dernier l'expremier_fichierssion ins‚r‚ */
liste_fichier *variable_control;                                  /* variable de contr“le */


char buffer [81];                           /* pour contr“le de la saisie */
int nbr_fichier;                     /* compteur d'enregistrements */
int s=1;                                           /* compteur de pages */
int j,k,rep;                                   /* variables de contr“le */

/********************* D‚claration des Fonctions globales ******************/
void alloc_memoire_prem_fichier(void);
void alloc_memoire_nouv_fichier(void);
//void saisie_eleves(void);
//void saisie_livres(void);
void insertion_nouv_fichier(void);
void cacul_pos_nouv_fichier(void);
void cacul_pos_nouv_fichier_2(void);
void affichage_infos(void);
//void affichage_livres(void);
void liberer_memoire(void);

/********************* Programme principal ******************/
void main(void)
{
	clrscr();
	alloc_memoire_prem_fichier();
//		saisie_eleves();
		affichage_infos();
	liberer_memoire();
}
/******************* fin du programme principal ************************

void saisie_eleves(void)
{
do
 {
	clrscr();
	printf("Eleves Nø");
	textcolor(RED);cprintf("%d\n\n",nb_eleves+1);
	printf("--> Nom: ");
	gets(buffer);
	while (strlen(buffer) > 20)              //   /* contr“le d‚signation
	{
		clrscr();
		printf("\nD‚signation trop longue.");
		printf("\n Nom: ");
		gets(buffer);
	}
	strcpy(nouv_e->nom, buffer);      /* ajout d‚signation dans la liste
	if (strcmp(nouv_e->nom, "0"))           // si d‚signation != "0"
	{
		printf("Prenom: ");
		gets(buffer);
		while (strlen(buffer) > 20)			  // contr“le d‚signation
		{
			printf("\nD‚signation trop longue.");
			printf("\n Prenom: ");
			gets(buffer);
		}
		strcpy(nouv_e->prenom, buffer);      //* ajout d‚signation dans la liste
		insertion_nouv_ele();
	}    // fin if(strcmp(...)) sup‚rieur
	else der_e= nouv_e;	 /* si fin de saisie alors initialiser der_e … nouv_e
 } while (strcmp(der_e->nom, "0"));
}

************************************************************************/
void alloc_memoire_prem_ele(void)
{
	if ((debut_liste = (liste_fichier *) malloc(sizeof(liste_fichier))) == NULL)
	{
		printf("\n\nPlus de m‚moire libre.");
		printf("\n\nAppuyez sur une touche pour sortir.");
		getch();
		exit(1);                           /* Sortie du programme */
	}
	nbr_fichier = 0;
	fin_liste = nouvel_element = dernier_inserer = debut_liste;      /* initialise les pointeurs eleves */
	debut_liste->premier_fichier = debut_liste->suivant_fichier = NULL;
}

/**************************************************************************/
void insertion_nouv_ele(void)
{
	if (strcmp(nouvel_element->nom, debut_liste->nom) <= 0) /* nouveau <= premier */
	{
		if (nouvel_element != debut_liste)    /* si au moins 1 ‚l‚ment dans liste */
		{
			 nouvel_element->premier_fichier = NULL; /* insertion nouveau premier elt */
			 nouvel_element->suivant_fichier = debut_liste;
			 debut_liste->premier_fichier = nouvel_element;
			 debut_liste = nouvel_element;
		}
	}
	else if (strcmp(nouvel_element->nom, fin_e->nom) >= 0)	/* nouveau >= dernier */
	{
		if (nouvel_element != debut_liste)       /* si au moins 1 ‚l. dans liste  */
		{
			nouvel_element->premier_fichier = fin_e; /* insertion nouveau dernier ‚lt */
			nouvel_element->suivant_fichier = NULL;
			fin_e->suivant_fichier = nouvel_element;
			fin_e= nouvel_element;
		}
	}
	else if (strcmp(nouvel_element->nom, der_e->nom) >= 0) /* nouveau >= dernier ins‚r‚ */																								 /* nouveau >= dernier ins‚r‚ */
	{
		if (nouvel_element != debut_liste) cacul_pos_nouv_ele();		/* au moins 1 ‚l. dans liste */
	}
	else cacul_pos_nouv_ele_2();		/* nouveau < dernier ins‚r‚ */

	der_e = nouvel_element;         /* actualise pointeur vers dernier ‚l‚ment */
	alloc_memoire_nouv_ele();
	nb_eleves++;
}

void cacul_pos_nouv_ele(void)
{
	for(a_e = der_e; strcmp(a_e->suivant_fichier->nom, nouvel_element->nom) < 0;
	a_e = a_e->suivant_fichier);
	nouvel_element->premier_fichier = a_e;        /* insertion nouvel ‚l‚ment */
	nouvel_element->suivant_fichier = a_e->suivant_fichier;
	a_e->suivant_fichier->premier_fichier = nouvel_element;
	a_e->suivant_fichier = nouvel_element;
}

void cacul_pos_nouv_ele_2(void)
{
	for(a_e = der_e; strcmp(nouvel_element->nom, a_e->premier_fichier->nom) < 0;
	a_e = a_e->premier_fichier);
	nouvel_element->premier_fichier = a_e->premier_fichier;         /* insertion nouvel ‚l‚ment */
	nouvel_element->suivant_fichier = a_e;
	a_e->premier_fichier->suivant_fichier = nouvel_element;
	a_e->premier_fichier = nouvel_element;
}

void alloc_memoire_nouv_ele(void)
{
	if ((nouvel_element = (liste_eleves *) malloc(sizeof(liste_eleves))) == NULL)
	{
		printf("\n\nPlus de m‚moire. <Entr‚e> pour continuer.");
		getch();
		nb_eleves++;                          /* actualise compteur enr. */
//		 break;                               /* sortie de boucle */
	}
}

void alloc_memoire_nouv_liv(void)
{
	if ((nouv_l = (liste_livres *) malloc(sizeof(liste_livres))) == NULL)
	{
		printf("\n\nPlus de m‚moire. <Entr‚e> pour continuer.");
		getch();
		nb_livres++;                          /* actualise compteur enr. */
//		 break;                               /* sortie de boucle */
	}
}

void affichage_infos(void)
{
	if (nb_eleves > 0)                             /* au moins 1 enregistrement saisi */
	{
		 printf("\033[2J");
		 printf("\n\nNombre d'enregistrements saisis : %d", nb_eleves);
		 printf("\n\nAFFICHER LES ENREGISTREMENTS :\n\n");
		 printf("Tri‚s en ordre ascendant\t\t(a)\n");
		 printf("Tri‚s en ordre descendant\t\t(d)\n");
		 printf("\nFin par appui sur une touche quelconque\n\n");
		 printf("Votre choix : ");
		 rep = getche();
		switch (rep)
		{
			case 'a':
			printf("\033[2J");
			HEADER(s);                                       /* en-tˆte */
			for (a_e = debut_liste, k = 1; a_e != NULL; a_e = a_e->suivant_fichier, k++)
			{
				printf("\n\n%d\t\t%-20s\t\t%-20s", k, a_e->nom, a_e->prenom);
				if ((k%9) == 0 && k != nb_eleves)
				{
					printf("\n\n<Entr‚e> pour page suivante.");
					getch();
					printf("\033[2J");
					s++;                      /* compteur de pages */
					HEADER(s);
				}
			}
			break;
			case 'd':
			printf("\033[2J");
			HEADER(s);                                       /* en-tˆte */
			for (a_e = fin_e, k = 1; a_e != NULL; a_e = a_e->premier_fichier, k++)
			{
				printf("\n\n%d\t\t%-20s\t\t%-20s", k, a_e->nom, a_e->prenom);
				if ((k%9) == 0 && k != nb_eleves)
				{
					printf("\n\n<Entr‚e> pour page suivante.");
					getch();
					printf("\033[2J");
					s++;                      /* compteur de pages */
					HEADER(s);
				}
			}
			break;
			default: ;
		}
	getch();
	}                                      /* fin if i > 0 */
}

void liberer_memoire(void)
{
	for (a_e = debut_liste; a_e != NULL; a_e = nouvel_element)
	{
		nouvel_element = a_e->suivant_fichier;             /* sauve adresse suivante avant */
										/* lib‚ration de l'‚l‚ment actuel contenu */
										/* dans cette adresse. Autrement, cette adresse */
										/* serait perdue et l'accŠs … la liste impossible */
		free(a_e);
	}
}
