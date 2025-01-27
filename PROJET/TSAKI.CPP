/*   TSAKI version 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: 16/08/1995
 DŠrniŠre modif: 17/08/95
 Programmation & conception: Tsakiropoulos Serge
*/

//
// TSAKI par TSAKIROPOULOS SERGE ............	  (Allein in der Finsternis)
// Editeur pour UNIX

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


// compatibilite UNIX   ANSI.sys
#define 	POS(x,y)    printf("\033[%d;%dH",x,y)  // gotoxy
#define 	CLEAR		printf("\033[2J")
#define 	CREV		printf("\033[7m") 		   // Couleur inverse
#define 	CCYAN		printf("\033[33m") 		   // Couleur CYAN
#define		CNORM		printf("\033[37m") 		   // Couleur NORMAL
// les fonctions
void allocation_premiere_ligne(void);
void insertion_nouvel_element(void);
// erreur dans main si edit etait dans main
	typedef struct edit
		{
		  char ligne[256];
		  struct edit *pre;
		  struct edit *suiv;
		} liste;

	liste *deb;		// pointeur vers la ligne suivante
	liste *fin;			// pointeur vers la fin de la liste
	liste *nouv;		// pointeur vers une nouvelle ligne
	liste *der;		// pointeur vers la derniere ligne inserer
	char backup[256];	// variable de contr“le

int main(void)
{
	char string[255];
	int s;
	char ss;
	CNORM;CLEAR;
	CCYAN; POS(3,1);printf("==============================================================================");

	allocation_premiere_ligne();
	ss=getc(stdin);

//	ANSI int ÄÄ¿
			 return (s);
}
void allocation_premiere_ligne(void)
{
	if ((deb = (liste *) malloc(sizeof( liste))) == NULL)
		{
		  printf("\n\nPlus de memoire !!!!??");
		  exit (1);	// retour err
		}
		// initialise pointeur //
   fin = nouv = der = deb;
   deb -> pre = deb ->suiv = NULL;
	POS(1,1);
	printf("\n Cr‚ation de la premier ligne ->");
//	CREV;
	printf("< OK >");
}
void insertion_nouvel_element(void)
{

}