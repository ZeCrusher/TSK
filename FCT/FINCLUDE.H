#define __FFINCLUD

/*   FINCLUD version 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: __/__/1995
 DŠrniŠre modif: 17/01/96
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
 INTRO :
	Cette fonction est commune … toute les fonctions dont voici la liste et
	aussi une brˆve d‚scription :

	- FCADRE.CPP	> Pour tracer des cadres Ú É * en mode 80 et 132
	- FMODE.CPP    	> Pour changer de mode d'ecran 80x43 ,80x132 , 800x600 ect
	- FFICHIER.CPP  > Gestion des fichiers sur disques ( Voir findfirst ...)
	- FMATER		> Indique le materiel (8087 , ram ect ....)
	- FMENU.CPP     > G‚n‚ration de menu d‚roulant ect
	- FGRAPHTS.CPP  > Bouton windows , cadre  ect .....
	ect ...
	Toute les fonctions commencent par F sont d‚pourvue de #include <xxxx.h>
		( et bien sur ecrit par TSAKI_ SERGE. )

*/

#define FALSE	0
#define TRUE	1
#define FICHIER_BINAIRE	0
#define FICHIER_TEXTE	1

#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif

#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif

#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif

#define SPACE(x)			for(tmp=0;tmp<x;tmp++) cprintf(" ")
#define VIDEO 					0x10
#define BEEP					printf("\a")
#define PAUSE   				while(bioskey(1)==0)


typedef unsigned char byte;

void color(byte x,byte y);
void right(byte *texte_source,byte *texte_objet,int taille_du_source,int emplacement);
void left(byte  *texte_source,byte  *texte_objet,int emplacement,int type_de_fichier);
void string_copy(byte  *texte_source ,byte  *texte_objet,int emplacement);
void pause(void);
 int hexa(char hexa_code_1,char hexa_code_2);
 int instr(byte *texte,byte caractere);
 int strcompare(byte  *texte_source ,byte  *texte_objet,int longueur,int mode);
// Renvoie 0 si la chaŒne objet existe dans la source
// sinon -1
 int strirech(byte  *texte_source ,byte  *texte_objet); // sans distinguer majuscules et minuscules
 int strrech(byte  *texte_source ,byte  *texte_objet);
void atts(void);
 int strdecoupe(byte  texte_source[128],byte  texte_objet[128],int debut,int fin); // prend une partie de la chaŒne source et la copie dans objet
