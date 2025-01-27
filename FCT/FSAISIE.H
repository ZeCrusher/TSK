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
extern char	jocker_de_txt[80];
extern int localisation;
extern int jocker_mult;
extern void cache_souris();
extern void montre_souris();
