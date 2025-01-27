/*   FMESSERR   version 2.00
 Utilitaire en Mode texte 80x25 ( x10 0x03 )
 R‚alis‚ le: 22/02/1996
 DŠrniŠre modif: 22/02/96
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
#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif
#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif
#define OK  		1
#define ANNULER	22
#define ATTRIBUT	33
#define SUPPRIMER 5


typedef unsigned char byte;
extern void color(unsigned char x,unsigned char y);
extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
// Mouse . H
extern void cache_souris();
extern void montre_souris();
extern int bouton_type(int x,int y,int l,char lettre,int numero,int precedent);
// Fcadre . H
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern int ev_bouton(int XBouton,int YBouton,int longueur,int Numero,int etat);
extern void bouton_xyl(int x,int y,int l);
/// ici !
int  message_err(int type);
void bouton(int x,int y,int longueur,int numeroe);

int message_err(int type)
{
		char erreur_ecran[4000];
		int ev_recu=0;

		cache_souris();
		gettext(1, 1, 80, 25,erreur_ecran); 		// Pour ne pas ˆtre obliger de tout r‚afficher
		switch (type)
		{
		  case 1:
				cadre_plein(24,9,55,15,0,WHITE,WHITE,1);  // cadre rep
				locatext(24,9,"        ChaŒne non saisie       ",WHITE+16*LIGHTRED);
				locatext(24,11,"  Vous n'avez pas saisie votre",BLACK+16*WHITE);
				locatext(24,12,"  chaŒne pour la recherche   ",BLACK+16*WHITE);
				titre(35,14,LIGHTRED,RED,DARKGRAY,WHITE, " < OK > ",0);
				bouton_xyl(35,14,8);
				titre(35,14,LIGHTRED,RED,DARKGRAY,WHITE, " < OK > ",1);
				delay(200);
		  break;
		  case 2:
				cadre_plein(24,9,55,15,0,WHITE,WHITE,1);  // cadre rep
				locatext(24,9,"    Pas de  Souris connect‚e    ",WHITE+16*LIGHTRED);
				locatext(24,11,"  La souris n'est pas install‚",BLACK+16*WHITE);
				locatext(24,12,"  ou elle n'est pas branch‚e.",BLACK+16*WHITE);
				titre(35,14,LIGHTRED,RED,DARKGRAY,WHITE, " Entr‚e ",0);
				bouton_xyl(35,14,8);
				titre(35,14,LIGHTRED,RED,DARKGRAY,WHITE, " Entr‚e ",1);
				delay(200);
		  break;
		  case 3:
				cadre_plein(19,9,60,12,0,WHITE,WHITE,1);  // cadre rep
				locatext(19,9,"      Interruption par l'utilisateur      ",BLACK+16*2);
				titre(25,11,LIGHTRED,RED,DARKGRAY,WHITE, " Reprendre ",0);
				titre(45,11,LIGHTRED,RED,DARKGRAY,WHITE, "  Fin  ",0);
				montre_souris();
				do
				{
					ev_recu=ev_bouton(25,11,11,1,ev_recu);
					ev_recu=ev_bouton(45,11,7, 2,ev_recu);
				}
				while(ev_recu==0);
				if (ev_recu==1)	titre(25,11,LIGHTRED,RED,DARKGRAY,WHITE, " Reprendre ",1);
				if (ev_recu==2) titre(45,11,LIGHTRED,RED,DARKGRAY,WHITE, "  Fin  ",1);
				delay(200);
		  break;
		  case 4:
				cadre_plein(14,5,65,16,0,WHITE,WHITE,1);  // cadre rep
				locatext(14,5,"        Attention !!! Le fichier est prot‚g‚        ",WHITE+16*LIGHTRED);
				locatext(18,7," Le fichier est peut ˆtre proteg‚ en ‚criture",0+16*WHITE);
				locatext(18,8," ou support invalide",0+16*WHITE);
				locatext(18,10,"  Le bouton \'Continuer\' supprime l\'attribut",0+16*WHITE);
				locatext(18,11,"lecture seule du fichier s‚lŠctionn‚.",0+16*WHITE);
				locatext(18,12,"L'attribut est r‚stitu‚ une fois l'‚dition",0+16*WHITE);
				locatext(18,13,"termin‚ .",0+16*WHITE);
				locatext(16,7,"\7",12+16*WHITE);
				locatext(16,8,"\7",12+16*WHITE);
				titre(25,15,LIGHTRED,RED,7,WHITE, " Annuler ",0);
				titre(45,15,LIGHTRED,RED,7,WHITE, " Continuer ",0);
				locatext(26,15,"A",15+16*4);
				locatext(46,15,"C",15+16*4);

				do
				{
						  ev_recu=bouton_type(25,15,9,'A',ANNULER,0);
						  ev_recu=bouton_type(45,15,11,'C',ATTRIBUT,ev_recu);
				}
				while(ev_recu==0);
					 if (ev_recu==ANNULER) titre(25,15,LIGHTRED,RED,7,WHITE, " Annuler ",1);
					 if (ev_recu==ATTRIBUT) titre(45,15,LIGHTRED,RED,7,WHITE, " Continuer ",1);
				delay(200);
		  break;
		  case 5:
				cadre_plein(14,5,65,10,0,WHITE,WHITE,1);  // cadre rep
				locatext(14,5,"        Attention !!! Suppression de fichier        ",WHITE+16*LIGHTRED);
				locatext(18,7,"les fichiers s‚lectionn‚s vont ˆtre effac‚s.",0+16*WHITE);
				titre(25,9,LIGHTRED,RED,7,WHITE, " Annuler ",0);
				titre(45,9,LIGHTRED,RED,7,WHITE, " Continuer ",0);
				locatext(26,9,"A",15+16*4);
				locatext(46,9,"C",15+16*4);

				do
				{
				  ev_recu=bouton_type(25,9,9,'A',ANNULER,0);
				  ev_recu=bouton_type(45,9,11,'C',SUPPRIMER,ev_recu);
				  ev_recu=bouton_type(45,9,11,13,SUPPRIMER,ev_recu);
				  // 13 correspond a Entr‚e
				}
				while(ev_recu==0);

				if (ev_recu==ANNULER) titre(25,9,LIGHTRED,RED,7,WHITE, " Annuler ",1);
				if (ev_recu==SUPPRIMER) titre(45,9,LIGHTRED,RED,7,WHITE, " Continuer ",1);
				delay(200);
		  break;

		}

		cache_souris();
		puttext(1, 1, 80, 25,erreur_ecran); 		// Pour ne pas ˆtre obliger de tout r‚afficher

	return((int) ev_recu);
}
