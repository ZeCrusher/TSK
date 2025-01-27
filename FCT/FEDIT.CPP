#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define LONG_LIGNE  128
///*
#if !defined( __FCADRE )
 #define __FCADRE // si pas declarer
#endif
//*/
 #include "c:\tsk\fct\fcadre.cpp"
 #include "c:\tsk\fct\finclud.cpp"

//
//Indique que l'emplacement r‚el du corps de ma fonction
// ///////////////////////  //////////// FCADRE
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);

	typedef struct editeur	{
		char ligne[LONG_LIGNE]; // chaŒne de caractere .
		struct editeur *premier; // Pointeur sur le premier element
		struct editeur *suivant; // Pointeur sur l'element suivant
	} liste; // Type personalis‚ par pour struct ‚diteur .

	liste *debut;   // debut de la liste chaŒne .
	liste *courant; // Pointeur de Travail .
	liste *secours; // Pointeur de secours .


 int edit(char *nom_fichier);
void presentation_editeur(void);
void afficher_page(int emplacement);


void main(void)
{
	edit("c:\\borlandc\\l.doc");  // retourne si il y a assez de m‚moire en cas d'erreur

}
int  edit(char *nom_fichier)  // retourne si il y a assez de m‚moire en cas d'erreur
{
	FILE *ptr_fic;
	int nbr_ligne_lu=0;


	if (( debut=(liste *) malloc(sizeof(liste)))== NULL )	{
		printf("\n Il n'y … pas assez de m‚moire de libre ...!!!!\n");
		return(7); // renvoie un code d'erreur .
	}

	// j'initialise les Pointeurs
	secours=courant=debut;

	if ((ptr_fic = fopen(nom_fichier, "rt"))== NULL)	{
	   fprintf(stderr, "Le fichier n'a pas ‚t‚ ouvert .\n");
	   return 1;
	}
	fseek(ptr_fic,0L, SEEK_SET); // On se deplace au debut du fichier car fopen(a+t);

	do
	{
		fgets(courant->ligne,LONG_LIGNE,ptr_fic); // je lis ici une ligne dans le fichier
		// Allocation de la m‚moire pour l'‚l‚ment suivant !!!

		// je refait une demande de r‚servation d'espace m‚moire pour la struct
		if ((courant->suivant = (liste*) malloc(sizeof(liste)))==NULL)		{
			printf("\n Il n'y … pas assez de m‚moire de libre .\n");
			return(7); // Code 7 , voir Doc
		}
		printf("%d %s",nbr_ligne_lu,courant->ligne);

		secours=courant; // Sauvegarde de l'adresse .
		courant=courant->suivant; //Range l'adresse du prochain element

		nbr_ligne_lu++;

	} while(!feof(ptr_fic)); // La je teste la fin du fichier

	secours->suivant=NULL; // Je Range NULL dans le pointeur du dernier enregistrement
	secours=courant;		  //

	// A partir d'ici le fichier a ‚t‚ charger completement OUF !!!
//	presentation_editeur();

//	afficher_page(0);


	for (courant=debut;courant!=NULL;courant=secours)	{
		secours=courant->suivant;
		free(courant);
	}

	return(0); // renvoie

}
void presentation_editeur(void)
{
	textbackground(1);
	clrscr();
	for(int i=0;i<80;i++) {
		locatcar(1+i,1,' ',1+16*7);
		locatcar(1+i,25,' ',1+16*7);
	}
}
/*
void afficher_page(int emplacement)
{
	char texte[80],t[132];
	int k=0,taille=0;

	liste *i;

	i=i->debut;

	do
	{
		textcolor(14);
		textbackground(1);
		gotoxy(1,2+k);
		cprintf("%s\n",i->ligne);
		i=i->suivant; // La , on incremente le pointeur
		k++;
	}
	while((i!=NULL)&&(k<22)); // Il faut v‚rifie si on est pas … la fin

}
*/