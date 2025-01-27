#define __FSAISIE
/*   FSAISIE version 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: __/__/1995
 DŠrniŠre modif: 04/03/96
 Programmation & conception: Tsakiropoulos Serge
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

#define SPACE(x)			for(tmp=0;tmp<x;tmp++) cprintf(" ")
#define	INSERTION			'R'
#define	ALT_L               '&'
#define	ALT_A               30
#define	ALT_I				23
#define	ALT_V               47

#define	LANCER   			666
#define	QUITTER  			222
#define	VALEUR   			444
#define	INITI     			333

#define	OFF					 0
#define	ON					 	 1
#define	FLECHE_A_DROIT		'M'
#define	FLECHE_A_GAUCHE		'K'
#define	TOUCHE_DEBUT   		'G'
#define	TOUCHE_FIN   		'O'
#define	TOUCHE_SUPPR   		'S'
#define	INIT_VAR			-1
#define TOUCHE_BACKSPACE	'\b'


typedef unsigned char byte;

int saisie(int x,int y,int nbr_lettre_saisie,byte jocker_de_txt[80]);
void init_jocker(byte jocker_init[80]);

// FMENU.H -----------------------------------------------------------------
extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
// FCADRE.H ----------------------------------------------------------------
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
// FMENU.H ----------------------------------------------------------------
extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
// PCBOSS.cpp -***********************************************************
extern void afficher_chaine_de_recherche(int x,int y,byte jocker_de_txt[80]);

extern char txt[80];
extern int increment;
extern int localisation;
extern int jocker_mult;
extern void cache_souris();
extern void montre_souris();

int saisie(int x,int y,int nbr_lettre_saisie,byte jocker_de_txt[80])
{
    int etat=0;
	static int insert=0;
	char touche=0,touche_special=0;
	cache_souris();
	gotoxy(x,y); // Place le curseur
	touche=getch();

		if (touche=='\x0')
		{
				touche_special=toupper(getch());

				if (touche_special==ALT_L) {	etat=LANCER;	}
				if (touche_special==ALT_I) {	etat=INITI;		}
				if (touche_special==ALT_V) {	etat=VALEUR;	}
				if (touche_special==ALT_A) {	etat=QUITTER;	}

				if ((touche_special==INSERTION)&&(insert==ON)) { insert=OFF;touche_special='\x0';_setcursortype(_SOLIDCURSOR);}
				if ((touche_special==INSERTION)&&(insert==OFF)) { insert=ON;touche_special='\x0';_setcursortype(_NORMALCURSOR);}
				if (touche_special==TOUCHE_DEBUT) {increment=0;insert=OFF;}
				if (touche_special==TOUCHE_FIN)				{
					increment=0;insert=OFF;
					increment=strlen(txt);
				}

				if (touche_special==FLECHE_A_DROIT)				{
						if ((increment<=(nbr_lettre_saisie-1))&&(txt[increment]!='\x0'))  {
							increment++;
								if (increment>strlen(txt)) txt[increment]=' ';
						}
				}
				if (touche_special==FLECHE_A_GAUCHE)				{
						if ((increment<=(nbr_lettre_saisie-1))&&(txt[increment-1]!='\x0'))						{
							if (increment!=0)  { increment--; }
						}
				}
		}
		if ((touche==TOUCHE_BACKSPACE)&&(increment==(nbr_lettre_saisie-1)))		{
			txt[increment-1]='\x0';
			increment--;
			touche='\x0';
		}
		gotoxy(x+increment,y);	// affiche le curseur a l'emplacement ou se trouve increment
		if (increment<(nbr_lettre_saisie-1))	{
			if ((touche==TOUCHE_BACKSPACE))			{
				if ((touche==TOUCHE_BACKSPACE)&&(localisation==0)&&(increment==0)) {
						  init_jocker(jocker_de_txt);
				}
				if ((touche==TOUCHE_BACKSPACE)&&(localisation+1==increment)&&(localisation==0)) {
						  init_jocker(jocker_de_txt);
				}
				if ((touche==TOUCHE_BACKSPACE)&&(localisation+1==increment)&&(localisation>0)) {
						  init_jocker(jocker_de_txt);
        	    }

					if (increment>0) increment--;
					if ((txt[increment+1]!=0))
					{
						 for (int i=0;i<(strlen(txt)-increment);i++)   {
							 txt[increment+i]=txt[increment+1+i];
                         }
                    	      if ((localisation>0)&&(localisation>increment)) {
									  jocker_de_txt[localisation-1]=jocker_de_txt[localisation];
							  jocker_de_txt[localisation]='0';
                              localisation--; // Comme je modifie la position du pointeur
                          	  }               // localisation il faut aussi le d'‚crementer
					}
					else
					{
						txt[increment]=0;
					}
			}
			else
			{
				if ((touche!='\x0')&&(touche!='\r'))
				{
					if (insert==OFF)
					{
						txt[increment]=touche;                                    // -1 = INIT_VAR
                    	if ((increment==localisation)&&(insert==OFF)) //&&(localisation==INIT_VAR))
						{   init_jocker(jocker_de_txt);
						}
					}
					else
					{
						if ((strlen(txt)<80)&&((strlen(txt)<(nbr_lettre_saisie)-1)))
						{
                    	      if ((localisation>0)&&(localisation>increment))
							  {
                        	  	jocker_de_txt[localisation+1]=jocker_de_txt[localisation];
							  	jocker_de_txt[localisation]='0';
                              	localisation++; // Comme je modifie la position du pointeur
                          	  }               // localisation il faut aussi le l'incrementer
							for (int d=(strlen(txt));d>(increment);d--)
							{
								txt[d]=txt[d-1];
							}
						}
						txt[increment]=touche;
					}
					increment++;
				}
			}
		}
		locatext(x,y,"..................................",BLACK+16*11);
		locatext(x,y,txt,BLUE+16*11);
		afficher_chaine_de_recherche(x,y,jocker_de_txt);
		gotoxy(x+increment,y);
		montre_souris();

	return(etat);

}
void init_jocker(byte jocker_init[80])
{
	jocker_init[localisation]='0';
	titre(16,10,LIGHTRED,WHITE,DARKGRAY,11, "  *  ",0);
	localisation=INIT_VAR;
	jocker_mult=0;

}