#define __FINPUTXT
/*   FINPUTXT version 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: __/__/1995
 DŠrniŠre modif: 04/03/96
 Programmation & conception: ZeCrusher
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
*/
#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif
#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif
#if !defined( __CTYPE_H )
#include <ctype.h>
#define __CTYPE_H
#endif
#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif

//#include "c:\tsk\fct\fcadre.cpp"

#define SPACE(x)			for(tmp=0;tmp<x;tmp++) cprintf(" ")
#define	INSERTION			'R'
#define	ALT_L               '&'
#define	ALT_A               30
#define	ALT_I				23
#define	ALT_V               47
#define TXTEXIST			500

#define	LANCER   			666
#define	QUITTER  			222
#define	VALEUR   			444
#define	INITI     			333

#define	FLECHE_A_DROIT		'M'
#define	FLECHE_A_GAUCHE		'K'
#define	FLECHE_EN_BAS  		'P'
#define	FLECHE_EN_HAUT 		'H'
#define	TOUCHE_DEBUT   		'G'
#define	TOUCHE_FIN   		'O'
#define	TOUCHE_SUPPR   		'S'
#define	INIT_VAR			-1
#define TOUCHE_BACKSPACE	'\b'
#define	OFF					 0
#define	ON					 1
#define INPUT_VAL          	100

// FCADRE.H ----------------------------------------------------------------
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);
extern void space(int x,int y,int l,int color);
// fonction Interne
int input(int x,int y,int nbr_lettre_saisie,char texte[132],int color);

/*
void main(void)
{
	char texte[132]={0};

	textbackground(0);
	clrscr();
	strcpy(texte,"Serge Tsakiropoulos est ZeCrusher !!!");
	input(10,10,TXTEXIST+30,texte,15+16*7);

}
//*/
int input(int x,int y,int nbr_lettre_saisie,char texte[132],int color)
{
	static int insert=OFF;
	char touche=0,touche_special=0;
	int increment=0;
	 gotoxy(x,y); // Place le curseur

	_setcursortype(_SOLIDCURSOR);


	if (nbr_lettre_saisie<INPUT_VAL)	{
		for (int e=0;e<nbr_lettre_saisie;e++)
			texte[e]='\x0';
	}
	else
	{
			nbr_lettre_saisie=nbr_lettre_saisie-INPUT_VAL;
			if (strlen(texte)>nbr_lettre_saisie)
				increment=nbr_lettre_saisie-1;
			else
				increment=strlen(texte)-1;
	}

	for( int er=0;er<nbr_lettre_saisie;er++) {
		locatcar(x+er,y,texte[er],color);
	}


 do
 {
	gotoxy(x+increment,y);
	touche=getch();

	_setcursortype(_SOLIDCURSOR);
	if (touche==27) return(27);

		if (touche=='\x0')
		{
				touche_special=toupper(getch());


				if ((touche_special==INSERTION)&&(insert==ON)) { insert=OFF;touche_special='\x0';_setcursortype(_SOLIDCURSOR);}
				if ((touche_special==INSERTION)&&(insert==OFF)) { insert=ON;touche_special='\x0';_setcursortype(_NORMALCURSOR);}
				if (touche_special==TOUCHE_DEBUT) {increment=0;insert=OFF;}

				if (touche_special==FLECHE_EN_BAS) {
					return(FLECHE_EN_BAS);
				}
				if (touche_special==FLECHE_EN_HAUT) {
					return(FLECHE_EN_HAUT);
				}

				if (touche_special==TOUCHE_FIN)				{
					increment=0;insert=OFF;
					increment=strlen(texte);
				}

				if (touche_special==FLECHE_A_DROIT)				{
						if ((increment<=(nbr_lettre_saisie-1))&&(texte[increment]!='\x0'))
						{
							increment++;
							if (increment>strlen(texte))
								texte[increment]=' ';
						}
				}
				if (touche_special==FLECHE_A_GAUCHE)				{
						if ((increment<=(nbr_lettre_saisie-1))&&(texte[increment-1]!='\x0'))						{
							if (increment!=0)  { increment--; }
						}
				}
		}
		if ((touche==TOUCHE_BACKSPACE)&&(increment==(nbr_lettre_saisie-1)))		{
			texte[increment-1]='\x0';
			increment--;
			touche='\x0';
		}
		gotoxy(x+increment,y);	// affiche le curseur a l'emplacement ou se trouve increment
		if (increment<(nbr_lettre_saisie-1))	{
			if ((touche==TOUCHE_BACKSPACE))			{

					if (increment>0) increment--;
					if ((texte[increment+1]!=0))
					{
						 for (int i=0;i<(strlen(texte)-increment);i++)   {
							 texte[increment+i]=texte[increment+1+i];
                         }
					}
					else
					{
						texte[increment]=0;
					}
			}
			else
			{
				if ((touche!='\x0')&&(touche!='\r'))
				{
					if (insert==OFF)
					{
						texte[increment]=touche;                                    // -1 = INIT_VAR
					}
					else
					{
						if ((strlen(texte)<80)&&((strlen(texte)<(nbr_lettre_saisie)-1)))
						{
							for (int d=(strlen(texte));d>(increment);d--)
							{
								texte[d]=texte[d-1];
							}
						}
						texte[increment]=touche;
					}
					increment++;
				}
			}
		}

		space(x,y,nbr_lettre_saisie,color);
		for (int l=0;l<nbr_lettre_saisie-1;l++)
			locatcar(x+l,y,texte[l],color);
		gotoxy(x+increment,y);
 }
 while (touche!='\r');

	_setcursortype(_NOCURSOR);  // Cache le curseur

	return(strlen(texte));

}
