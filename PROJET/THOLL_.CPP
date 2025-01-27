// Programme THOLL_ par TSAKIROPOULOS SERGE
// Editeur sous UNIX
// le: 25/08/1995.

#include <stdio.h>  // scanf, printf, gets
#include <stdlib.h> // malloc, free, exit
#include <conio.h>
#include <string.h> // strcmp, strcpy
#include <bios.h>   // bioskey


//	Definition des directives pour UNIX
//////////////////////////////////////////////
// compatibilite UNIX   ANSI.sys
// Je pense qu'il faudrait utiliser pour les COULEURS 'enum'

#define 	CLS_UNIX    		printf("\033[2J")
#define 	POS(x,y)    		printf("\033[%d;%dH",x,y)  /* gotoxy		  */
#define 	Couleur_inverse		printf("\033[7m") 		   /* Couleur inverse */
#define 	C_NOIR				printf("\033[30m") 		   /* Couleur NOIR   */
#define 	C_ROUGE				printf("\033[31m") 		   /* Couleur ROUGE   */
#define 	C_VERT				printf("\033[32m") 		   /* Couleur VERT    */
#define 	C_JAUNE				printf("\033[33m") 		   /* Couleur CYAN    */
#define 	C_BLEUE				printf("\033[34m") 		   /* Couleur BLEUE   */
#define 	C_MAGENTA			printf("\033[35m") 		   /* Couleur MAGENTA */
#define 	C_CYAN				printf("\033[36m") 		   /* Couleur CYAN	 */
#define 	C_BLANC				printf("\033[37m") 		   /* Couleur BLANC	 */

#define 	CF_INVERSE			printf("\033[7m") 		   /* Couleur NOIR sur BLANC */
#define 	CF_NOIR				printf("\033[40m") 		   /* Couleur xx sur */
#define 	CF_ROUGE			printf("\033[41m") 		   /* Couleur xx sur */
#define 	CF_VERT				printf("\033[42m") 		   /* Couleur xx sur */
#define 	CF_JAUNE			printf("\033[43m") 		   /* Couleur xx sur */
#define 	CF_BLEUE			printf("\033[44m") 		   /* Couleur xx sur */
#define 	CF_MAGENTA			printf("\033[45m") 		   /* Couleur xx sur */
#define 	CF_CYAN				printf("\033[46m") 		   /* Couleur xx sur */
#define 	CF_BLANC			printf("\033[47m") 		   /* Couleur xx sur */

#define		CNORM				printf("\033[7m") 		   /* Couleur NORMAL  */


// D‚claration des variables globales

typedef struct editeur
{
	char ligne[255];
	struct editeur *pre;            /* pointeur vers ‚l‚ment pr‚c‚dent */
	struct editeur *suiv;             /* pointeur vers ‚l‚ment suivant */
};

editeur *deb_e;     /* pointeur vers d‚but de liste              */
editeur *fin_e;     /* pointeur vers fin de liste                */
editeur *nouv_e;    /* pointeur vers nouvel ‚l‚ment				 */
editeur *der_e;     /* pointeur vers dernier l'expression ins‚r‚ */
editeur *a_e;       /* variable de contr“le 					 */


char buffer [81];       /* pour contr“le de la saisie */
int nb_eleves;          /* compteur d'enregistrements */
int s=1;                /* compteur de pages */
int j,k,rep;            /* variables de contr“le */

/********************* D‚claration des Fonctions globales ******************/
void allocation_memoire_premiere_ligne(void);
void alloc_memoire_nouv_ele(void);
void th_edit(void);
void insertion_nouv_ele(void);
void cacul_pos_nouv_ele(void);
void cacul_pos_nouv_ele_2(void);
void affichage_infos(void);
void liberer_memoire(void);

/* Deco */
void decor_editeur(void);
void wind(int x1,int y1,int x2,int y2,int couleur);
/********************* Programme principal ******************/
/* Int pour ANSI */
int main(void)
{
	clrscr();
	allocation_memoire_premiere_ligne();
	decor_editeur();
	getch();
	th_edit();
	affichage_infos();
	liberer_memoire();
}
/******************* fin du programme principal *************************/

void th_edit(void)
{
do
 {
	clrscr();
	printf("Eleves Nø");
	printf("%d\n\n",nb_eleves+1);
	printf("--> Nom: ");
	gets(buffer);
	while (strlen(buffer) > 20)                 /* contr“le d‚signation */
	{
		clrscr();
		printf("\nD‚signation trop longue.");
		printf("\n Nom: ");
		gets(buffer);
	}
	strcpy(nouv_e->ligne, buffer);      /* ajout d‚signation dans la liste */

	if (strcmp(nouv_e->ligne, "0"))               /* si d‚signation != "0" */
	{
		insertion_nouv_ele();
	}
	else
	{
		der_e= nouv_e;	 /* si fin de saisie alors initialiser der_e … nouv_e */
	}
 }
 while (strcmp(der_e->ligne, "0"));
}

/**************************************************************************/
void allocation_memoire_premiere_ligne(void)
{
	if ((deb_e = (editeur *) malloc(sizeof(editeur))) == NULL)
	{
		printf("\n\nPlus de m‚moire libre.");
		printf("\n\nAppuyez sur une touche pour sortir.");
		getch();
		exit(1);                           /* Sortie du programme */
	}
	nb_eleves = 0;
	fin_e = nouv_e = der_e = deb_e;      /* initialise les pointeurs eleves */
	deb_e->pre = deb_e->suiv = NULL;
}

/**************************************************************************/
/**************************************************************************/
void insertion_nouv_ele(void)
{
	if (strcmp(nouv_e->ligne, deb_e->ligne) <= 0) /* nouveau <= premier */
	{
		if (nouv_e != deb_e)    /* si au moins 1 ‚l‚ment dans liste */
		{
			 nouv_e->pre = NULL; /* insertion nouveau premier elt */
			 nouv_e->suiv = deb_e;
			 deb_e->pre = nouv_e;
			 deb_e = nouv_e;
		}
	}
	else if (strcmp(nouv_e->ligne, fin_e->ligne) >= 0)	/* nouveau >= dernier */
	{
		if (nouv_e != deb_e)       /* si au moins 1 ‚l. dans liste  */
		{
			nouv_e->pre = fin_e; /* insertion nouveau dernier ‚lt */
			nouv_e->suiv = NULL;
			fin_e->suiv = nouv_e;
			fin_e= nouv_e;
		}
	}
	else if (strcmp(nouv_e->ligne, der_e->ligne) >= 0) /* nouveau >= dernier ins‚r‚ */																								 /* nouveau >= dernier ins‚r‚ */
	{
		if (nouv_e != deb_e) cacul_pos_nouv_ele();		/* au moins 1 ‚l. dans liste */
	}
	else cacul_pos_nouv_ele_2();		/* nouveau < dernier ins‚r‚ */

	der_e = nouv_e;         /* actualise pointeur vers dernier ‚l‚ment */
	alloc_memoire_nouv_ele();
	nb_eleves++;
}

void cacul_pos_nouv_ele(void)
{
	for(a_e = der_e; strcmp(a_e->suiv->ligne, nouv_e->ligne) < 0;
	a_e = a_e->suiv);
	nouv_e->pre = a_e;        /* insertion nouvel ‚l‚ment */
	nouv_e->suiv = a_e->suiv;
	a_e->suiv->pre = nouv_e;
	a_e->suiv = nouv_e;
}

void cacul_pos_nouv_ele_2(void)
{
	for(a_e = der_e; strcmp(nouv_e->ligne, a_e->pre->ligne) < 0;
	a_e = a_e->pre);
	nouv_e->pre = a_e->pre;         /* insertion nouvel ‚l‚ment */
	nouv_e->suiv = a_e;
	a_e->pre->suiv = nouv_e;
	a_e->pre = nouv_e;
}

void alloc_memoire_nouv_ele(void)
{
	if ((nouv_e = (editeur *) malloc(sizeof(editeur))) == NULL)
	{
		printf("\n\nPlus de m‚moire. <Entr‚e> pour continuer.");
		getch();
		nb_eleves++;                          /* actualise compteur enr. */
/*		 break;                                sortie de boucle */
	}
}

void affichage_infos(void)
{
	if (nb_eleves > 0)                             /* au moins 1 enregistrement saisi */
	{
		 CLS_UNIX;
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
				CLS_UNIX;
			for (a_e = deb_e, k = 1; a_e != NULL; a_e = a_e->suiv, k++)
			{
				printf(" \n \n %d \t \t %-20s \t ", k, a_e->ligne);
				if ((k%9) == 0 && k != nb_eleves)
				{
					printf("\n\n<Entr‚e> pour page suivante.");
					getch();
					CLS_UNIX;
					s++;
				}
			}
			break;
			case 'd':
			CLS_UNIX;

			for (a_e = fin_e, k = 1; a_e != NULL; a_e = a_e->pre, k++)
			{	printf("\n\n%d\t\t%-20s\t\t ", k, a_e->ligne);
				if ((k%9) == 0 && k != nb_eleves)
				{
					printf("\n\n<Entr‚e> pour page suivante.");
					getch();
					CLS_UNIX;
					s++;                      /* compteur de pages */
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
	for (a_e = deb_e; a_e != NULL; a_e = nouv_e)
	{
		nouv_e = a_e->suiv;             /* sauve adresse suivante avant */
										/* lib‚ration de l'‚l‚ment actuel contenu */
										/* dans cette adresse. Autrement, cette adresse */
										/* serait perdue et l'accŠs … la liste impossible */
		free(a_e);
	}

}
void decor_editeur(void)
{
	int c;
	CF_BLEUE;CLS_UNIX;
	CF_BLEUE;C_CYAN;

//	POS(1,1);printf(" THOLL_ EDIT ");
//	C_NOIR;	printf(" -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
//	C_CYAN;printf(" Tsaki_ Serge ");

	CF_BLANC;
	C_NOIR;
	POS(1,1);
	printf("   Fichier    Edit                                                     Tsaki_95 ");
	CF_CYAN;
	C_NOIR;
	POS(2,1);
	printf("                                                                                ");

	while ((c = getchar()) != '\n')
		printf("%c", c);

	exit(0);
}
