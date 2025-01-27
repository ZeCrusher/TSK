#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#if !defined( __FMOUSE )
 #include "C:\tsk\fct\fmouse.h"
 #define __FMOUSE
#endif



#define LONG_LIGNE  80
#define FOND_EDIT   27
#define EDIT        1
#define	FLECHE_A_DROIT		'M'
#define	FLECHE_A_GAUCHE		'K'
#define	FLECHE_EN_BAS  		'P'
#define	FLECHE_EN_HAUT 		'H'
#define	TOUCHE_DEBUT   		'G'
#define	TOUCHE_FIN   		'O'
#define	TOUCHE_SUPPR   		'S'
#define	TOUCHE_INSERT  		'R'
#define	TOUCHE_TAB   		 9
#define	TOUCHE_BACK_SPACE	 8
#define	TOUCHE_PAGE_UP	  	'Q'
#define TOUCHE_PAGE_DOWN	'I'
#define	INIT_VAR			-1
#define	CTRL_Y				25
#define	CTRL_H				8
#define	CTRL_K				11
#define	CTRL_B				2
#define	CTRL_C				3
#define	CTRL				4
#define	ALT					8
#define CTRL_KH_ON			1
#define CTRL_KH_OFF			-1
#define CTRL_KB				110
#define CTRL_KC				111
#define CTRL_KK				112
#define CTRL_KH				113
#define ENTREE				13
#define ECHAP				27
#define INSERT_ON           1
#define F11                 '…' // 133
#define F12                 '†' //code ascii 134
#define INSERT_OFF          0
#define NBL                 100
#define NBC                 255


	typedef unsigned char byte;

// / FCADRE
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
extern void bar_menu(int x,int y,char color,char fond,int lettre_surligner,char *titre);
extern int  menu_der(int x,int y,byte largeur,byte hauteur,byte nbr_de_barre,byte type_de_cadre,byte couleur_barre_ecriture,byte couleur_barre_fond,byte couleur_cadre_ecriture,byte couleur_cadre_fond,byte couleur_texte,byte lettre,char *string[40]); // retourne le menu clicker

 int edit(char *nom_fichier);
void presentation_editeur(char *nom);
void afficher_page(int cpt,int deb_line,char style,int comp);
void vt(int y);
void hr(int x);

void effacer_ligne(int cpt,int nbl);
void inserer_ligne(int cpt,int nbl,int x);
void copier_bloc(int x,int y);


 int menu_fichier_edit(char nom[13],int compteur);
 int menu_edit(int x,int y);
 int charger_edit(char nom_file[13]);
 int enregistre_edit(char nom_file[13],int compteur);
 int command_crtl(void);
char determiner_fin_ligne(int nbr,int x);
void couper_bloc(int x,int y);
void glisser_souris(int *x,int *y,int *deb_ligne,int *deb_page);
void etat_souris_edit(int *px,int *py,int *bt);

	unsigned char huge ligne[NBL][NBC+1];

	int ctrl_kb_ligne=-1; //emplacement
	int ctrl_kb_lettre=-1;
	int ctrl_kk_ligne=-1;//emplacement
	int ctrl_kk_lettre=-1;
	int ctrl_kh=CTRL_KH_ON;

	int compteurs=0;

/*
void main(void)
{



}
*/
int  edit(char *nom_fichier)  // retourne si il y a assez de m‚moire en cas d'erreur
{
	FILE *ptr_fic;
	byte *str_color[16]={" _BLACK"," BLU_E"," GREE_N"," _CYAN"," RE_D"
						  ," _MAGENTA"," BRO_WN"," LIG_HTGRAY"," DAR_KGRAY"," _LIGHTBLUE"
						  ," L_IGHTGREEN"," LIGHTCY_AN"," LIGHT_RED"," LIGH_TMAGENTA"," YELL_OW",
						   " _WHITE"};

	int code=0,ce=11,cf=1;
	char style=27;
	char insert=INSERT_OFF;
	int debut_page=0,debut_ligne=0;
	int fin=0, // sortir de la boucle
		cp=0,  // variable temporaire pour menu_fichier
		value=0; // pour toute les touches de commande
	int x=0,y=0,ys=0;
	char touche=0;
	int valeur_xxreel=0,valeur_yyreel,bouton=0,posx=1,posy=1;

	char ecran[4000];

	gettext(1, 1, 80, 25, ecran);

	   compteurs=0;

	if ((ptr_fic = fopen(nom_fichier, "r+b"))== NULL)	{
//	if ((ptr_fic = fopen("c:\\borlandc\\l.doc","r+b"))== NULL)	{
	   fprintf(stderr, "Cannot open input file.\n");
	   return 1;
	}
	fseek(ptr_fic,0L, SEEK_SET); // On se deplace au debut du fichier car fopen(a+t);

	for (int e=0;e<NBL;e++)
		for (int l=0;l<NBC;l++)
			ligne[e][l]=' ';

	do
	{
		fgets(ligne[compteurs++],NBC,ptr_fic); // je lis ici une ligne de NBC char dans le fichier
		for (int i=strlen(ligne[compteurs-1]);i<NBC;i++)
			ligne[compteurs-1][i-2]=32;
	}
	while(!feof(ptr_fic)&&(compteurs<NBL)); // La je teste la fin du fichier
	fclose(ptr_fic);

 //	compteurs-=1; // Car la chaine debute a ZERO

	presentation_editeur(nom_fichier); // presentation de l'editeur
	afficher_page(0,0,style,compteurs); // Affiche la premier page

	_setcursortype(_SOLIDCURSOR);

	x=1;y=1;
	do
	{
		gotoxy(x+1,y+2);
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris_edit(&posx,&posy,&bouton);

		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==23)&&(valeur_xxreel==80))		{
			cache_souris();
			if ((++debut_page)>compteurs-21)
				debut_page=compteurs-21;
			afficher_page(debut_page,debut_ligne,style,compteurs);
			vt(y+debut_page);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==3)&&(valeur_xxreel==80))		{
			cache_souris();
				if ((--debut_page)<0)
					debut_page=0;
			afficher_page(debut_page,debut_ligne,style,compteurs);
			vt(y+debut_page);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==24)&&(valeur_xxreel==31))		{
			cache_souris();
			if (--debut_ligne<0) debut_ligne=0;
			afficher_page(debut_page,debut_ligne,style,compteurs);
			hr(x+debut_ligne);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==24)&&(valeur_xxreel==75))		{
			cache_souris();
			if (++debut_ligne>(NBC-78)) debut_ligne=NBC-78; // ET oui XX + 80 de x = NBC
			afficher_page(debut_page,debut_ligne,style,compteurs);
			hr(x+debut_ligne);
		}

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<21)&&(valeur_xxreel>18))		{
			relacher_bsgauche();
			printf("\a");
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<17)&&(valeur_xxreel>12))		{
			relacher_bsgauche();
			menu_edit(debut_ligne+x,debut_page+y);
			if (insert==INSERT_OFF)	_setcursortype(_SOLIDCURSOR); else _setcursortype(_NORMALCURSOR);
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<11)&&(valeur_xxreel>3))
		{
			relacher_bsgauche();
			cp=menu_fichier_edit(nom_fichier,compteurs);
			if (insert==INSERT_OFF)
				_setcursortype(_SOLIDCURSOR);
			else
				_setcursortype(_NORMALCURSOR);

			if (cp==-1)
				fin=1;
			else
				if (cp!=0)	compteurs=cp;
		}

		if ((bouton==BOUTON_GAUCHE)&&(valeur_xxreel>1)&&(valeur_xxreel<80)&&(valeur_yyreel<24)&&(valeur_yyreel>2))
		{
			ys=valeur_yyreel-1;
			if ((ys!=1)&&(ys>1)&&((ys+debut_page)<(compteurs+1))&&(ys<24)) {
				y=ys-1;x=valeur_xxreel-1;
				if (x==80) x--; // si x = 80 on se trouve sur l'ascenceur
				ctrl_kb_ligne=y+debut_page-1;
				ctrl_kb_lettre=x+debut_ligne-1;
				glisser_souris(&x,&y,&debut_ligne,&debut_page);
			}
			vt(y+debut_page); //une fois que la souris
			hr(x+debut_ligne); // a deplac‚ le curseur on r‚affiche l'ascenceur
		}
/*************************************************************
*   Touche de commande crtl alt shift ....                   *
**************************************************************/
//*
	value=peek(0x0040, 0x0017); // peek renvoie le mot situ‚ … l'emplacement
								//   m‚moire d'adresse segment:offset
	if (value&ALT) { // Il sagit de tester la touche CTRL
		cp=menu_fichier_edit(nom_fichier,compteurs);
		if (insert==INSERT_OFF)	_setcursortype(_SOLIDCURSOR);	else	_setcursortype(_NORMALCURSOR);
		if (cp==-1) {
			fin=1;
		}
		else {
			if (cp!=0) {
				compteurs=cp;
			}
		}
	}
	if (value&CTRL) { // Il sagit de tester la touche CTRL
		code=command_crtl(); // Oui pour la touche CTRL
// CTRL_KY
		if (code==CTRL_Y) { // effacement d'une ligne
			if (debut_page+y<=ctrl_kb_ligne)	{
				ctrl_kb_ligne--;	ctrl_kk_ligne--;
			}
			if ((debut_page+y<=ctrl_kk_ligne)&&(debut_page+y>=ctrl_kb_ligne))	{
				ctrl_kk_ligne--;
			}
			if (compteurs>y+debut_page) compteurs--;

			effacer_ligne(debut_page+y-1,compteurs);
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}
// CTRL_KB
		if (code==CTRL_KB) { // debut d'un block
			ctrl_kb_ligne=y+debut_page-1;ctrl_kb_lettre=x+debut_ligne-1;
			ctrl_kh=CTRL_KH_ON; // initialise KH car on doit afficher le debut
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}
// CTRL_KH && CTRL_KH_ON
		if ((code==CTRL_KH)&&(ctrl_kh==CTRL_KH_ON))		{
			ctrl_kh=CTRL_KH_OFF;code=0;
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}
// CTRL_KH && CTRL_KH_OFF
		if ((code==CTRL_KH)&&(ctrl_kh==CTRL_KH_OFF))	{
			ctrl_kh=CTRL_KH_ON;code=0;
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}
// CTRL_KK
		if (code==CTRL_KK) { // #define CTRL_KK				111
			ctrl_kk_ligne=y+debut_page-1;
			ctrl_kk_lettre=x+debut_ligne-1;
			if (ctrl_kk_lettre<0) ctrl_kk_lettre=0;
			ctrl_kh=CTRL_KH_ON; // initialise KH car on doit afficher le debut

			if ((ctrl_kk_lettre==0)&&(ctrl_kk_ligne!=ctrl_kb_ligne)) {
				ctrl_kk_lettre=NBC-1;
				ctrl_kk_ligne--;
			}
			if ((ctrl_kk_ligne==ctrl_kb_ligne)&&(ctrl_kb_lettre==ctrl_kk_lettre))
				ctrl_kk_lettre++;
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}
// CTRL_KC
		if (code==CTRL_KC) {
			copier_bloc(debut_ligne+x,debut_page+y);
			afficher_page(debut_page,debut_ligne,style,compteurs);
		}

	}
//*/

		if (kbhit())
		{
			touche=getch();
// Type de Touche ZERO
			if (touche==0) {
				touche=toupper(getch());
				if (touche==TOUCHE_PAGE_UP) {
					if ((debut_page<(compteurs-21))&&(compteurs>21))
						debut_page+=21;
					else {
						if (compteurs>10) {
							debut_page=compteurs-10;y=10;
						}
						if (debut_page-compteurs<20) { y=debut_page-compteurs; }
						if (y<1) y=(debut_page-compteurs)*-1;
					}
					afficher_page(debut_page,debut_ligne,style,compteurs);
				}
				if (touche==TOUCHE_PAGE_DOWN) {
					debut_page-=21;
					if (debut_page<0) { debut_page=0;y=1; }
					afficher_page(debut_page,debut_ligne,style,compteurs);
				}
// TOUCHE_INSERT
				if ((touche==TOUCHE_INSERT)&&(insert==INSERT_OFF)) {
					insert=INSERT_ON;touche=-1;
					_setcursortype(_NORMALCURSOR);
					cache_souris();
					locatext(38,25,"Insert",1+16*7);locatext(45,25,"ON ",11+16*7);
				}
// TOUCHE_INSERT
				if ((touche==TOUCHE_INSERT)&&(insert==INSERT_ON)) {
					insert=INSERT_OFF;touche=-1;
					_setcursortype(_SOLIDCURSOR);
					cache_souris();
					locatext(38,25,"Insert",1+16*7);locatext(45,25,"OFF",3+16*7);
				}

				if (touche==F11) {
					locatext(50,3," Couleur Ecriture ",0+16*15);
					ce=menu_der(50,4,17,17,17,0,WHITE,LIGHTRED,BLACK,WHITE,BLACK,RED,str_color);
					ce--;
					if ((ce<0)&&(ce>15)) style=31; else style=ce+16*cf;
					afficher_page(debut_page,debut_ligne,style,compteurs);
					if (insert==INSERT_OFF) _setcursortype(_NORMALCURSOR); else _setcursortype(_SOLIDCURSOR);
				}
				if (touche==F12) {
					locatext(55,3," Couleur du Fond  ",0+16*15);
					cf=menu_der(55,4,17,17,17,0,WHITE,LIGHTRED,BLACK,WHITE,BLACK,RED,str_color);
					cf--;
					if ((cf<0)&&(cf>15)) style=31; else style=ce+16*cf;
					afficher_page(debut_page,debut_ligne,style,compteurs);
					if (insert==INSERT_OFF) _setcursortype(_NORMALCURSOR); else _setcursortype(_SOLIDCURSOR);
				}

				if (touche==TOUCHE_DEBUT) { // fleche debut
					x=1;debut_ligne=0;
					afficher_page(debut_page,0,style,compteurs);
				}
// TOUCH_FIN
				if (touche==TOUCHE_FIN) { // fleche debut
					for (int margo=0;margo<NBC;margo++) {
						if (ligne[debut_page+y-1][margo]!=' ')
							debut_ligne=margo;
					}
					if (debut_ligne<78)  {
						x=debut_ligne+2;debut_ligne=0;
					} else {
						debut_ligne-=76;x=77;
					}
					afficher_page(debut_page,debut_ligne,style,compteurs);
				}
//  TOUCHE_SUPPR
				if (touche==TOUCHE_SUPPR) { //Supprimer
					if (determiner_fin_ligne(debut_page+y,x+debut_ligne)!=0) { // ICI on verifie la fin de la chaine
						ligne[debut_page+y-1][NBC-1]=32;
						for (int m=x+debut_ligne;m<NBC;m++) {				   // car on peut ainsi copier la chaine+1 … la fin de la premiere si
							ligne[debut_page+y-1][m-1]=ligne[debut_page+y-1][m]; // on est en fin de chaine sinon on efface
						}                                                        // le caractere qui doit l'etre
						if ((x+debut_ligne-1<ctrl_kk_lettre)&&(debut_page+y-1==ctrl_kk_ligne))
							ctrl_kk_lettre--;
						if ((x+debut_ligne-1<ctrl_kb_lettre)&&(debut_page+y-1==ctrl_kb_ligne))
							ctrl_kb_lettre--;
					}
					else
					{
						for (int d=x+debut_ligne;d<NBC;d++) {
							ligne[debut_page+y-1][d-1]=ligne[debut_page+y][d-(x+debut_ligne)];
						}
						effacer_ligne(debut_page+y,compteurs);
						if (compteurs>y+debut_page) compteurs--;
						if (compteurs<0) compteurs=1;
						if ((debut_page+y<=ctrl_kk_ligne)&&(debut_page+y>=ctrl_kb_ligne)&&(ctrl_kb_ligne!=ctrl_kk_ligne))	{  // le curseur se trouve dans le bloc
							ctrl_kk_ligne--;                                                   // et on efface une ligne .
						}
						if (debut_page+y<=ctrl_kb_ligne)	{   // Le curseur se trouve
							ctrl_kb_ligne--;  					// avant le bloc est il faut decaler
							ctrl_kk_ligne--;                    // le block
						}
						if (debut_page+y-1==ctrl_kk_ligne)	{
							ctrl_kk_lettre=ctrl_kk_lettre+x+debut_ligne-1;
						}
					}
					afficher_page(debut_page,debut_ligne,style,compteurs);
				}
// FLECHE_A_DROIT
				if (touche==FLECHE_A_DROIT) { /****************************/
					if ((++x)>78) {
						x=78;
						if (++debut_ligne>(NBC-78))
							debut_ligne=NBC-78; // ET oui XX + 80 de x = NBC
						afficher_page(debut_page,debut_ligne,style,compteurs);
					}
				}
// FLECHE_A_GAUCHE
				if (touche==FLECHE_A_GAUCHE) {
					if ((--x)<1) {
						x=1;
						if (--debut_ligne<0) debut_ligne=0;
						afficher_page(debut_page,debut_ligne,style,compteurs);
					}
				}
// FLECHE_EN_BAS
				if (touche==FLECHE_EN_BAS) { //vers le bas
					if ((y)>20) {
						y=21;
						if ((++debut_page)>compteurs-21)
							debut_page=compteurs-21;
						if (y==21)
							afficher_page(debut_page,debut_ligne,style,compteurs);
					}
					else {
						if (compteurs>debut_page+y)
								y++;
					}
					if (y>compteurs) y--;
					if (debut_page!=compteurs-21) // Pour eviter toute repetition de l'affichage
						if (y==21)
							afficher_page(debut_page,debut_ligne,style,compteurs);
				}
// FLECHE_EN_HAUT
				if (touche==FLECHE_EN_HAUT) { // Vers le Haut !
					if ((--y)<1) {
						y=1;
						afficher_page(debut_page,debut_ligne,style,compteurs);
							if ((--debut_page)<0)  debut_page=0;
					}
/*						if (debut_page!=0)	afficher_page(debut_page,debut_ligne,style,compteurs);
*/
				}
				gotoxy(4,25);textcolor(15);textbackground(7);
				cprintf("%d:%d   ",y+debut_page,x+debut_ligne);
				hr(x+debut_ligne);
				vt(y+debut_page);
			} ////////////////////////////////////////////////////////////
			else
			{
				hr(x+debut_ligne);
				vt(y+debut_page);
//-- Autre touche
				if (touche<32) { //########################################
// TOUCHE_TAB
					if (touche==TOUCHE_TAB) {
						ys=int(x/4);x=ys*4;
						x+=4;
						if (x>78) { x=78;
							debut_ligne+=4;
						}
						if (debut_ligne+x>NBC-1)
							debut_ligne=NBC-78;
						gotoxy(4,25);textcolor(15);textbackground(7);
						cprintf("%d:%d   ",y+debut_page,x+debut_ligne);
						afficher_page(debut_page,debut_ligne,style,compteurs);
					}
					if (touche==TOUCHE_BACK_SPACE) {
						if (x+debut_ligne-1>0) {
							for (int a=x+debut_ligne-1;a<NBC;a++) {
								ligne[debut_page+y-1][a-1]=ligne[debut_page+y-1][a];
							}
							x--;
							if (x<0) { x=0;
								if (debut_ligne>0)
									debut_ligne--;
							}
							if ((debut_ligne+x-2<ctrl_kb_lettre)&&(debut_page+y-1==ctrl_kb_ligne))
								ctrl_kb_lettre--;
							if ((debut_ligne+x-2<ctrl_kk_lettre)&&(debut_page+y-1==ctrl_kk_ligne))
								ctrl_kk_lettre--;
							afficher_page(debut_page,debut_ligne,style,compteurs);
						}
					}
// ECHAP
					if (touche==ECHAP)	fin=1;
// ENTREE
					if (touche==ENTREE)	{ /******************* 13 */
						if (insert==INSERT_ON) {
							if (debut_page+y-1<ctrl_kb_ligne)	{
								ctrl_kk_ligne++;ctrl_kb_ligne++;
							}
							if ((debut_page+y-1==ctrl_kb_ligne)&&(x+debut_ligne>ctrl_kb_lettre)) {
								ctrl_kk_ligne++;
								//ctrl_kk_lettre=ctrl_kk_lettre-(x+debut_ligne)+1;
							}
							if ((debut_page+y-1<ctrl_kk_ligne)&&(debut_page+y-1>ctrl_kb_ligne))	{
								ctrl_kk_ligne++;
							}
							if ((debut_page+y-1>ctrl_kb_ligne)&&(debut_page+y-1==ctrl_kk_ligne)&&(x+debut_ligne<ctrl_kk_lettre)) {
								ctrl_kk_ligne++;
								ctrl_kk_lettre=ctrl_kk_lettre-(x+debut_ligne)+1;
							}
							if ((debut_page+y-1==ctrl_kb_ligne)&&(debut_page+y-1<=ctrl_kk_ligne)&&(x+debut_ligne<ctrl_kb_lettre)) {
								ctrl_kb_ligne++; // deplacement du block
								ctrl_kk_ligne++; // vers le bas
								ctrl_kk_lettre=ctrl_kk_lettre-(x+debut_ligne)+1;
							}

							inserer_ligne(debut_page+y-1,compteurs,debut_ligne+x);
							afficher_page(debut_page,debut_ligne,style,compteurs);
							x=1;debut_ligne=0; // Une fois que le texte est plac‚ au debut il faut remetre le curseur au debut
							compteurs++; 	   // Car inserer_ligne , donc le fichier comporte une ligne de plus .
						}
						if (debut_page+y==compteurs) {
							if (compteurs>NBL)
								compteurs=NBL;
							else
								compteurs++;
						}
						if ((y==21)&&(debut_page+y==compteurs)) {
							if (compteurs>NBL) compteurs=NBL; else compteurs++;
						}
						if ((++y)>21) {
							y=21;
							if ((++debut_page)>compteurs-25)	debut_page=++compteurs-25;
							if (compteurs>NBL) compteurs=NBL;
						}
						afficher_page(debut_page,debut_ligne,style,compteurs);
						gotoxy(4,25);textcolor(15);textbackground(7);
						cprintf("%d:%d   ",y+debut_page,x+debut_ligne);
					}  /******************* 13 */
				}
				else	{//##### if (touche<32)
					if (x>78) { x=78;
						if ((debut_ligne+x)<NBC)
							debut_ligne++;
						else
							debut_ligne=NBC-78;
					}
////////////////////////////////////////////////////******************
					if (x+debut_ligne<NBC) {//****************************
						if (insert==INSERT_OFF) {
							ligne[debut_page+y-1][((x++)-1+debut_ligne)]=touche;
						}
						else {
							for (int a=NBC;a>x+debut_ligne-1;a--) {
								ligne[debut_page+y-1][a]=ligne[debut_page+y-1][a-1];
							}
							ligne[debut_page+y-1][((x++)-1+debut_ligne)]=touche;
							if ((debut_ligne+x-2<ctrl_kb_lettre)&&(debut_page+y-1==ctrl_kb_ligne))
								ctrl_kb_lettre++;
							if ((debut_ligne+x-2<ctrl_kk_lettre)&&(debut_page+y-1==ctrl_kk_ligne))
								ctrl_kk_lettre++;
						}
					}
////////////////////////////////////////////////////******************
					gotoxy(4,25);textcolor(15);textbackground(7);
					cprintf("%d:%d   ",y+debut_page,x+debut_ligne);
					if (compteurs>NBL-1) compteurs=NBL;

					afficher_page(debut_page,debut_ligne,style,compteurs);
				}//####### if (touche<32)
			}
		}

	}
	while (fin!=1);
	_setcursortype(_NOCURSOR);
	cache_souris();
	puttext(1, 1, 80, 25, ecran);


	return(0);
}
void presentation_editeur(char *nom)
{
	int taille=strlen(nom);
	textbackground(1);
	clrscr(); // Effacement de l'ecran
	for(int i=0;i<80;i++) {
		locatcar(1+i,1,' ',15+16*7);
		locatcar(1+i,25,' ',15+16*7);
	}
	locatcar(15,25,'³',12+16*7);
	locatext(4,25," 1:1 ",15+16*7);
	bar_menu(4,1,BLACK,LIGHTGRAY,RED,"_Fichier  _Edit  _Aide ");
	locatext(36,25,"³",12+16*7);
	locatext(38,25,"Insert",1+16*7);
	locatext(45,25,"OFF",3+16*7);
	locatext(49,25,"³",12+16*7);
	cadre_plein(1,2,80,24,0,15,1,0);     // dessine le cadre
	for (int j=0;j<21;j++)
		locatext(80,3+j,"±",3+16*1);
	locatext(80,3,"",1+16*3);
	locatext(80,23,"",1+16*3);
	for (int k=0;k<43;k++)
		locatext(32+k,24,"±",3+16*1);
	locatext(31,24,"\x11",1+16*3);
	locatcar(75,24,0x10,1+16*3);
	hr(1); // Affiche la barre horizontale
	vt(1);
	locatext((80-taille)/2-2,2,"´ ",15+16*1);
	locatext((80-taille)/2,2,nom,14+16*1);
	locatext((80-taille)/2+taille,2," Ã",15+16*1);

}
void afficher_page(int cpt,int deb_line,char style,int comp)
{
	int	color_base=0;
	char texte[79]; // l'ecran ne fais que 80 char - 2 * '³' d'ou 78+1 pour
					//    le caractere de contr“le
	int aff=0; // pour ne pas afficher les lignes qui n'existerais pas si le
	long double emdb=0,emfn=0,cpti=0; // voir si-dessous

	// Note sur emdb et sur emfn
	// je presente le tableau char huge *ligne[] un peut comme un
	// ecran donc , je considere qu'il n'y a qu'une chaŒne de
	// caractŠre de 128 * debut_block_ligne + debut_ligne_block
	// Pour acceder … une partie du tableau et voir ou l'utilisateur
	// … s‚lectionner sont texte je fais donc 	emdb=128L*ctrl_kb_ligne+ctrl_kb_lettre; //
	// emdb => (e)mplace(m)ent (d)e(b)ut
	// emfn => (e)mplace(m)ent (f)i(n)

	if (ctrl_kb_ligne>ctrl_kk_ligne) {
		emdb=ctrl_kk_ligne;
		ctrl_kk_ligne=ctrl_kb_ligne;
		ctrl_kb_ligne=emdb;
	}

	emdb=128L*ctrl_kb_ligne+ctrl_kb_lettre; //
	emfn=128L*ctrl_kk_ligne+ctrl_kk_lettre; //

	cache_souris();  // pour toute affichage il faut effacer la souris
	if (comp>20) { // si le fichier fait plus de 20 lignes
		aff=comp-cpt; 			// 	OUI
		if (aff>21) aff=21;
	}
	else
		aff=comp;				// Non il ne faut afficher que aff ligne
	color_base=11;
	for (int i=0;i<aff;i++)
	{//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		cpti=(cpt+i)*128;
/*		if ((i<20)&&(comp-deb_line<21))
			locatext(2,3+i,"                                                                              ",color_base);
		locatext(2,3+i,"                                                                              ",color_base);
*/
		for(int mg=0;mg<78;mg++)		{
			texte[mg]=ligne[cpt+i][mg+deb_line];
		}
		for (int j=0;j<78;j++)
		{
			if ((cpti+j+deb_line>=emdb)&&(cpti+j+deb_line<emfn)) {
				if (ctrl_kh==CTRL_KH_ON) {
					color_base=style/16+16*11;
				}
			}
			else {
				color_base=style;  // Couleur de base fix‚ par le User ( F11 et F12 )
			}
			if ((ligne[cpt+i][j+deb_line]!='\n')&&(ligne[cpt+i][j+deb_line]!='\r'))
					locatcar(2+j,3+i,texte[j],color_base);
		}
	} //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	if (aff<20) {
		locatext(2,aff+3,"ÄÄ<                      >ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ",15+16*1);
		locatext(6,aff+3,"Fin de votre Fichier",12+16*1);
	}

	for (int u=aff+1;u<21;u++)
		locatext(2,u+3,"                                                                              ",14+16*1);
}
void effacer_ligne(int cpt,int nbl)
{

	for (int i=cpt;i<nbl+1;i++) {
		strncpy(ligne[i],ligne[i+1],NBC);
	}
}
void inserer_ligne(int cpt,int nbl,int x)
{

	for (int i=nbl;i>cpt;i--) {
		strncpy(ligne[i],ligne[i-1],NBC);
	}

	for (int a=x;a<NBC;a++) {
		ligne[cpt+1][a-x]=ligne[cpt][a-1];
	}
	for (int b=x;b<NBC;b++) {
		ligne[cpt][b-1]=' ';
	}

}

void etat_souris_edit(int *px,int *py,int *bt)
{
		union REGS reg,reg_out;
		reg.x.ax=0x03;
		int86(0x33,&reg,&reg_out);
		*px=reg_out.x.cx;
		*py=reg_out.x.dx;
		*bt=reg_out.x.bx;
}
int menu_edit(int x,int y)
{
	int resultat_menu=0;

	byte *str_fichier[1]={" _Coller "};

	resultat_menu=menu_der(10,2,16,2,2,0,14,1,BLACK,WHITE,BLACK,RED,str_fichier);

	if (resultat_menu==1) {
		couper_bloc(x,y);
	}
	return(0);
}
int menu_fichier_edit(char nom[13],int compt)
{
	int resultat_menu=0;

	byte *str_fichier[5] = {" _Enregister ","ÿ"," _Charger ","ÿ"," _Fermer "};

	resultat_menu=menu_der(2,2,15,6,6,0, 14,1, 0,15, 0,12,str_fichier);

	if (resultat_menu==1) {
		return(enregistre_edit(nom,compt));
	}
	if (resultat_menu==3) {
		return(charger_edit(nom));
	}
	if (resultat_menu==5) {
		return(-1);
	}
	return(0);
}
int enregistre_edit(char nom_file[13],int compt)
{

   FILE *out;
   int debut_ligne=0;

   if ((out = fopen(nom_file, "w+t"))== NULL)   {
	  fprintf(stderr, "Cannot open input file.\n");
	  return 1;
   }
	fseek(out,0L, SEEK_SET); // On se deplace au debut du fichier car fopen(a+t);

	for (int i=0;i<compt;i++) {
		for (int margo=0;margo<NBC-1;margo++) {
			if (ligne[i][margo]!=' ')
				debut_ligne=margo;
		}
		for (int w=0;w<debut_ligne+1;w++)
			fputc(ligne[i][w], out);
		fputc('\n', out);
	}

	fclose(out);
	return (compt);
}
int charger_edit(char nom_file[13])
{
	int compt=0;

	FILE *ptr_fic;

	if ((ptr_fic = fopen(nom_file, "r+t"))== NULL)	{
	   fprintf(stderr, "Cannot open input file.\n");
	   return 1;
	}
	fseek(ptr_fic,0L, SEEK_SET); // On se deplace au debut du fichier car fopen(a+t);

	for (int e=0;e<NBL;e++)
		for (int l=0;l<NBC;l++)
			ligne[e][l]=' ';

	do
	{
		fgets(ligne[compt++],NBC-1,ptr_fic); // je lis ici une ligne de LONG_LIGNE dans le fichier
		for (int i=strlen(ligne[compt-1]);i<NBC;i++)
			ligne[compt-1][i-1]=32;
	}
	while(!feof(ptr_fic)&&(compt<NBL)); // La je teste la fin du fichier

	fclose(ptr_fic);

	afficher_page(0,0,11+16*1,compt); // Affiche la premier page

	return(compt);

}
int command_crtl(void)
{
	int value=0;
	int code=0;
	int touche=0;

	locatext(51,25," Ctrl + K  B | K | H | Y | C",112); //0+16*7 =112

	do
	{
		value = peek(0x0040, 0x0017);
		if (kbhit())		{
			touche=toupper(getch());
			if (touche==CTRL_Y)	return(CTRL_Y);

			if (touche==CTRL_K)
			{
				touche=toupper(getch());
				if ((touche=='K')||(touche==CTRL_K)) {
					code=CTRL_KK;value=0;
				}
				if ((touche=='B')||(touche==CTRL_B)) {
					code=CTRL_KB;value=0;
				}
				if ((touche=='H')||(touche==CTRL_H)) {
					code=CTRL_KH;value=0;
				}
				if ((touche=='C')||(touche==CTRL_C)) {
					code=CTRL_KC;
					value=0;
				}
			}
		}
	}
	while (value & 4); // CTRL !

	locatext(51,25,"                              ",112); //0+16*7 =112

	return(code);
}
/** TSK ZC **³ 24 7 98 ³*³17:09³********************************************
	Cette fonction , comme son nom l'indique determine si le curseur
	ce trouve en fin de la chaine . Cela est utile pour la fonction
	SUPP
	D‚claration: char determiner_fin_ligne(int nbr,int x);
	Valeur Renvoy‚e:
		 ³ Si succŠs,
		 ÀÂ>	0 si il n'y a plus de caractere apres le curseur
		  À>	nbr le nombre de char
****************************************************************************/
char determiner_fin_ligne(int nbr,int x)
{
	int strlenligne=0;

	for (int i=x-1;i<NBC;i++) { // de x a la fin de la chaine , d'ou NBC
		if (ligne[nbr-1][i]!=32) // L 'espace est le seul char qui peut rester
			strlenligne++; // nbr de char
	}

	return(strlenligne);
}
void copier_bloc(int x,int y)
{
	int kb=ctrl_kb_lettre; // est l'emplacement en x sur la ligne ctrl_kb_lettre

	x--;

	if (ctrl_kb_ligne==ctrl_kk_ligne) {	// ici on est sur la mˆme ligne !
		for (int i=ctrl_kb_lettre;i<ctrl_kk_lettre+1;i++) {
			for (int a=NBC;a>x;a--) {
				ligne[y-1][a]=ligne[y-1][a-1];
			}
			ligne[y-1][x++]=ligne[ctrl_kb_ligne][kb++];
		}
   }
	if (ctrl_kb_ligne<ctrl_kk_ligne) {
			inserer_ligne(y-1,compteurs++,x+1);
		for (int j=0;j<(ctrl_kk_ligne-ctrl_kb_ligne);j++) {
			inserer_ligne(y+j,compteurs++,1);
		}
		// ici ce passe la copie
		for (int k=ctrl_kb_lettre;k<NBC;k++)
			ligne[y-1][x+(k-ctrl_kb_lettre)]=ligne[ctrl_kb_ligne][k];

		for (int l=ctrl_kb_ligne+1;l<ctrl_kk_ligne+1;l++)
			strcpy(ligne[y+(l-ctrl_kb_ligne)-1],ligne[ctrl_kb_ligne+(l-ctrl_kb_ligne)]);
	}

}
void vt(int y)
{
	for (int j=0;j<19;j++)
		locatext(80,4+j,"±",3+16*1);
	locatext(80,4+((int)(18*y)/compteurs),"\x9",12+16*1);
}
void hr(int x)
{
	for (int k=0;k<43;k++)
		locatext(32+k,24,"±",3+16*1);
	locatext(32+(x*42/NBC),24,"\x9",12+16*1);
}

void couper_bloc(int x,int y)
{



}
void glisser_souris(int *x,int *y,int *deb_ligne,int *deb_page)
{
	int valeur_xxreel=0,valeur_yyreel,bouton=0,posx=1,posy=1;
	int x1=0,y1=0;
	int ys=0;

	ctrl_kh=CTRL_KH_ON;

	do
	{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris_edit(&posx,&posy,&bouton);

		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);

		if ((valeur_yyreel>2)&&(valeur_xxreel>1)&&(valeur_xxreel<80)&&(valeur_yyreel<24))		{
			ys=valeur_yyreel;
			if ((ys!=1)&&(ys>1)&&((ys+*deb_page)<(compteurs+1))&&(ys<24)) {
				*y=ys-2;
				*x=valeur_xxreel-1;
				ctrl_kk_ligne=*y+*deb_page;
				ctrl_kk_lettre=valeur_xxreel+*deb_ligne-2;
				ctrl_kk_ligne--;
				y1=*deb_page;
				x1=*deb_ligne;
				cache_souris();
				afficher_page(y1,x1,27,compteurs);
			}
		}

	}
	while(bouton==BOUTON_GAUCHE);

}
