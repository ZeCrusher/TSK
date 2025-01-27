#define __FFINCLUD

/*   FINCLUD version 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: __/__/1995
 DŠrniŠre modif: 17/01/96
 Programmation & conception: ZECRUSHER!
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
 INTRO :
	Cette fonction est commune … toute les fonctions dont voici la liste et
	aussi une brˆve d‚scription :

	- FCADRE.CPP	> Pour tracer des cadres Ú É * en mode 80 et 132
	- FMODE.CPP    	> Pour changer de mode d'ecran 80x43 ,80x132 , 800x600 ect
	- FFICHIER.CPP  > Gestion des fichiers sur disques ( Voir findfirst ...)
	- FMATER		> Indique le materiel (8087 , ram etc ....)
	- FMENU.CPP     > G‚n‚ration de menu d‚roulant etc
	- FGRAPHTS.CPP  > Bouton windows , cadre  etc .....
	ect ...
	Toute les fonctions commencent par F sont d‚pourvue de #include <xxxx.h>
		( et bien sur ecrit par ZeCrusher )

*/

#define FALSE	0
#define TRUE	1
#define FICHIER_BINAIRE	0
#define FICHIER_TEXTE	1
#define DIFFERENT		-1
#define PAS_DIFFERENT	0

#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif

#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif

#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif

#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif
#if !defined( __CTYPE_H )
#include <ctype.h>
#define __CTYPE_H
#endif

#define SPACE(x)			for(tmp=0;tmp<x;tmp++) cprintf(" ")
#define VIDEO 					0x10
#define BEEP					printf("\a")
#define PAUSE   				while(bioskey(1)==0)

typedef unsigned char byte;

void pause(void);
 int hexa(char hexa_code_1,char hexa_code_2);
void color(int x,byte y);
void right(byte *texte_source,byte *texte_objet,int taille_du_source,int emplacement);
void left(byte  *texte_source,byte  *texte_objet,int emplacement,int type_de_fichier);
 int instr(byte *texte,byte caractere);
void string_copy(byte  *texte_source ,byte  *texte_objet,int emplacement);
 int strcompare(byte  *texte_source ,byte  *texte_objet,int longueur,int mode);

// Renvoie 0 si la chaŒne objet existe dans la source
// sinon -1
 int strirech(byte  *texte_source ,byte  *texte_objet); // sans distinguer majuscules et minuscules
 int strrech(byte  *texte_source ,byte  *texte_objet);
 int strdecoupe(byte  texte_source[128],byte  texte_objet[128],int debut,int fin); // prend une partie de la chaŒne source et la copie dans objet


// void atts(void);

/*
void main(void)
{
	byte  tex1[80]="FICHIER.EXE",
		  tex2[80]="mExE";

	printf("resultat > %d \n",strirech(tex1,tex2));

}
//*/
int strrech(byte *texte_source ,byte  *texte_objet)
{
	char *texte={0};


	for (int i=0;i<((int) strlen(texte_source));i++)
	{

		if (texte_source[i]==texte_objet[0])
		{
			for (int e=0;e<strlen(texte_source)-i;e++)	{
				texte[e]=texte_source[i+e];
			}
			texte[e]='\x0'; // Zero terminal
			return(strcompare(texte,texte_objet,3,1));

		}
	}
	return(-1);
}
int strirech(byte *texte_source,byte *texte_objet)
{
	char *texte={0};


	for (int i=0;i<strlen(texte_source);i++)
	{

		if (texte_source[i]==texte_objet[0])
		{
			for (int e=0;e<strlen(texte_source)-i;e++)	{
				texte[e]=texte_source[i+e];
			}
			texte[e]='\x0';
			return(strcompare(texte,texte_objet,3,2));// ,2) -> Majuscule

		}
	}
	return(-1);
}
int strcompare(byte  *texte_source ,byte  *texte_objet,int longueur,int mode)
{
	int done_=-1;
	int verification=0;

		for (int i=0;i<longueur;i++)
		{
		 switch (mode)
		 {
			case 1:
				if(texte_source[i]==texte_objet[i])	{
					done_=PAS_DIFFERENT;verification++;
				}
				else	{
					done_=DIFFERENT;
					return (done_);
				}
			break;
			case 2:
				if(toupper(texte_source[i])==toupper(texte_objet[i]) )	{
					done_=PAS_DIFFERENT;
					verification++;
				}
				else	{
					done_=DIFFERENT;
					return (done_);
				}
			break;
		 }
		}


	if (verification+1>longueur)	{
			return (PAS_DIFFERENT);
	}
	else	{
		done_=DIFFERENT;
		return (done_);
	}

}
void color(int x,char y)
{
	textcolor(x);
	textbackground(y);
}
void string_copy(char *texte_source,char *texte_objet,int emplacement)
{
	int taille=0,compteur=0;
	taille=strlen(texte_source);
	for (int i=emplacement;i<taille;i++)	{
		texte_objet[compteur]=texte_source[i];
		compteur++;
	}
}
void left(byte  *texte_source,byte  *texte_objet,int emplacement,int type_de_fichier)
{
	if (type_de_fichier==FICHIER_BINAIRE)
	{
		for (int i=0;i<emplacement;i++) 	{
			texte_objet[i]=texte_source[i];
		}
	}
	else { // Beaucoup plus rapide pourtant pas OPTIMISEE
	 strncat(texte_objet,texte_source,emplacement);
	}
}
void right(byte *texte_source,byte *texte_objet,int taille_du_source,int emplacement)
{	//

	strnset(texte_objet, 0,255);

	for (int i=0;i<((emplacement));i++)	{
		texte_objet[i]=texte_source[taille_du_source-emplacement+i];
	}
	texte_objet[i]='\x0';

}
int instr(byte *texte,byte caractere)
{
	int len=0;

	len=strlen(texte);

	for (int i=0;i<len;i++)
	{
		if (texte[i]==caractere)
			return(i);
	}
	return (-1);
}

void pause(void)
{
	char touche;
		touche=getch(); 		// indique qu'il s'agit d'un touche … deux code ASCII comme les
		if (touche=='\x0')	{ 	// touche F1 F2 ect
			touche=getch();
		}

}
int hexa(char hexa_code_1,char hexa_code_2)
{
		int valeur_decimal=0;

		if ((hexa_code_1>64)&&(hexa_code_1<71))	{
			valeur_decimal= (hexa_code_1 - 55)*16;
		}
		if ((hexa_code_1>48)&&(hexa_code_1<58))	{
			valeur_decimal= (hexa_code_1 - 48)*16;
		}

		if ((hexa_code_2>64)&&(hexa_code_2<71))	{
			valeur_decimal= valeur_decimal+(hexa_code_2 - 55);
		}
		if ((hexa_code_2>47)&&(hexa_code_2<58))	{
			valeur_decimal= valeur_decimal+(hexa_code_2 - 48);
		}
	return (valeur_decimal);
}
int strdecoupe(byte  texte_source[128],byte  texte_objet[128],int debut,int fin) // prend une partie de la chaŒne source et la copie dans objet
{
	int compteur=0;

	if (fin>strlen(texte_source))
		return(-1);
	if (debut>fin)
		return(-1);

	for (int i=debut;i<fin;i++) {
		texte_objet[compteur++]=texte_source[i];
	}
	texte_objet[compteur]=0; // Fin de la chaŒne
	return (0); // OK
}
/* void atts(void)
{
	asm	 mov dx,0x3Da
	deb1:
	asm	in al,dx
	asm	test al,8
	asm	jne deb1
	deb2:
	asm	in al,dx
	asm	test al,8
	asm	je deb2

}  */
