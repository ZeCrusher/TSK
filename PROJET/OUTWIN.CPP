// OUTWIN.CPP

// #pragma hdrfile 	 "c:\tsk\tsk.SYM"  // Changement du fichier entˆtes pr‚compil‚s.
 #pragma -O2		// vitesse
 #pragma -G		// vitesse du code EXE
 #pragma -ml		// Pour les pointeurs - ModŠle de m‚moire voir Option|Compiler|Code_generation|Large(ù)

 //#pragma warn -par

 // Test de la configuration de la M‚moire … la compilation .....
#include "C:\tsk\fct\fmem__.cpp" // Verifie les Erreurs du aux modeles de m‚moire

#if !defined( __CONIO_H )
 #include <conio.h>
 #define __CONIO_H
#endif
#if !defined( __STDIO_H )
 #include <stdio.h>
 #define __STDIO_H
#endif
#if !defined( __PROCESS_H )
 #include <process.h>
 #define __PROCESS_H
#endif

 #define  color(a,b)				textcolor(a);textbackground(b)
 #define CLS						textbackground(BLACK);clrscr()
 #define colorxy(x,y,color,fond) 	gotoxy(x,y);textcolor(color);textbackground(fond)

#if !defined( __FCADRE )
 #include "C:\tsk\fct\fcadre.h"
 #define __FCADRE
#endif
#if !defined( __FMOUSE )
 #include "C:\tsk\fct\fmouse.h"
 #define __FMOUSE
#endif

#if !defined( __FMENU )
 #include "C:\tsk\fct\fmenu.h"
 #define __FMENU
#endif
#if !defined( __FASCII )
 #include "C:\tsk\fct\fascii.h"
 #define __FASCII
#endif
#if !defined( __FFICHIER )
 #include "C:\tsk\fct\ffichier.h"
 #define __FFICHIER
#endif

 // Voir Macro Dans FINCLUD.H

 #define FICHIER_TEXTE		1
 #define INPUT_VAL          100
 #define VIDEO  			0x10

/* Touche de fonction */
 #define F1     			59
 #define F2     			60 // Touche de fonction pour enregistrer !
 #define F3     			61
 #define F4     			62 //
 #define F5     			63 //
 #define F10     			68 //
 #define PAS_DE_SOURIS      2  // Pour le message d'erreur quand il n'y a pas de souris


 // Touches de deplacement pour la barre des commandes
 #define FLECHE_A_DROIT		'M'
 #define FLECHE_A_GAUCHE	'K'
 #define FLECHE_EN_BAS  	'P'
 #define FLECHE_EN_HAUT 	'H'
 #define ENTREE				13
 #define DEROULER			10
//////Fonction externe /////////////////////////////

//////////////////////////  FINCLUD.H
extern void left(byte  *texte_source,byte  *texte_objet,int emplacement,int type_de_fichier);
extern void right(byte *texte_source,byte *texte_objet,int taille_du_source,int emplacement);
//////////////////////////  FMOUSE.H /////////////////////////////////////
extern int input(int x,int y,int nbr_lettre_saisie,char texte[132],int color);
////////////////////////// Dans FASCII.H /////////////////////////////////////
extern void table_ascii(void);
extern void init_ascii();  								// Init la cr‚ation des codes ASCII
extern void definition_ascii(char table[16],char ascii);   //
extern void change_palette_texte(int n,char color);

//////////////////////////  Dans FMOUSE  /////////////////////////////////////
extern void relacher_bsgauche(void);
//////////////////////////  FMENU  /////////////////////////////////////
extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
extern int  menu_der(int x,int y,byte largeur,byte hauteur,byte nbr_de_barre,byte type_de_cadre,byte couleur_barre_ecriture,byte couleur_barre_fond,byte couleur_cadre_ecriture,byte couleur_cadre_fond,byte couleur_texte,byte lettre,char *string[40]); // retourne le menu clicker
extern void bar_menu(int x,int y,char color,char fond,int lettre_surligner,char *titre);
////////////////////////// FCADRE  /////////////////////////////////////
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
extern void modif_fond(char x,char y,int longueur,char attribut,char type);

///////////////////////// Fmesserr ///////////////////////////////
extern  int message_err(int type);
///////////////////////// Fediteur ///////////////////////////////
extern int  edit(char *nom_fichier);
/////////////////////// Fonctions //////////////////////////////////////////
extern int strdecoupe(byte  *texte_source ,byte  *texte_objet,int debut,int fin); // prend une partie de la chaŒne source et la copie dans objet

/////////////////////// Fonctions //////////////////////////////////////////


void presentation(void); 	// C'est le premier cadre du debut (c)
void deco(void);  // Presentation du fond
void option_menu(int color);
void signification(int numb); // Explication des commandes de msdos.sys
void affiche(int numb);
void erreur_fichier(void);
 int quitter(void);
 int menu_fichier(void);
 int menu_aide(void);
 int menu_user(void);
 int menu_mode(void);
 int menu_edit(void);
 int faire_fichier_boot(void);
 int recup_info_msdos(char nom[32],char init);
 int recup_ligne(char element[30],char ligne[30],char valeur_ligne[80]);
 int sauve_msdos(int cpt);
void erreur_system(void);
void decrire_outwin(void);
void decrire_bootlog(void);
void decrire_echec(void);
 int choisir_editeur(void);
void aff_val(void);
 int installation(char file_source[20],char file_objet[20]);
 int lecteur_indefinie(void);
void screen(void);
int analyser_ligne(char ligne[128],char commande[32],char type[20],char min[10],char max[10],char commentaire[128]);
int analyse_table(int cpt);

	char  ligne_msdosys[70][91];
	int	nbr_ligne=0;
	char valeur_table[70][30];

	char tblx[20]={26,26,26,30,30,30,30,30,30,30,30,30,30,30,30,30,30};
	char tbly[20]={5,6,7,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};


	int nbr_commande=0;

	struct Msdosys {
		char win_commande[32];
		char commentaire[128];
		char type_donnee[32];
		char min[10];
		char max[10];
	};
	struct Msdosys Msdos95[50];

int main(char argc, char **argv)
{
	int choix_menu=0,y=0,indice=0;
	int resultat=0;
	char touche=0;
	int mode_menu=0;
	int lecteur=0;
	int delay_boot=0;
	int delay_demar=0;
	char fichier[20];
	char r[200]; // Pour la fonction found_file
	char sauve[4096]; // Pour stocker le fond pour la fonction charger

	byte *str_Menu_default[8] = {" _1 Normal ",
							" _2 Journal de d‚marrage (Bootlog.txt) ",
							" _3 Mode sans echec  ",
							" _4 Mode sans echec avec support r‚seau ",
							" _5 Confirmation pas … pas ",
							" _6 Ligne de commande uniquement ",
							" _7 Ligne de commande en mode sans echec",
							" _8 Version pr‚c‚dente de Ms-Dos "};

	if (argc==2) {
		if (strcmpi(argv[1],"/boot")==0)		{
			faire_fichier_boot();
			return(0);
		}
		if (strcmpi(argv[1],"/e")==0)		{
			if (_dos_setfileattr("C:\\MSDOS.SYS",0) != 0)	{
			   erreur_fichier();
			   color(7,0);clrscr();printf("OutWin 95 Ver 1 ( TSK )\n\n");
				_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM);
			   exit(1);
			}
			fond(0);
			edit("c:\\msdos.sys");
			cache_souris();color(7,0);
			clrscr();
			locatext(1,1,"Outwin 95 version 1.1 Copirate  Ó×ô ZeCrusher (Z!) ",15+16*0);
			if (_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM)!= 0)	{
				erreur_fichier();color(7,0);clrscr();
				locatext(1,1,"Outwin 95 version 1.1 Copirate  Ó×ô ZeCrusher (Z!)",15+16*0);
				exit(1);
			}
			 exit(0);
		}

		if (strcmpi(argv[1],"/?")==0)		{
			printf("\n OutWin 95 par ZeCrusher !!  (TSK_98)\n");
			printf(" Parametres : /?\n");
			printf(" Parametres : /e lance l'editeur de OUTWIN95\n");
			printf("            : /boot pour cr‚er le fichier c:\\dos\\zcboot.com\n");
			exit(0);
		}
		if (strcmpi(argv[1],"/p")==0)		{
			charger_table(argv[2]);   // Charge la police de caractere ALES
		}

	}

	if (mouse_presente()==MOUSE_ABSENTE)
	{
		message_err(PAS_DE_SOURIS);
		clrscr();
		exit(0);
	}

	_setcursortype(_NOCURSOR);

	table_ascii();		// F1 , Cr‚ation des nouveau char ASCII

	fond(0);

	presentation();
	CLS; // Effacement de l'ecran
	color(7,0);
	charger_table("c:\\dos\\long.als");   // Charge la police de caractere ALES
	clrscr();
	deco(); // Presentation du fond de l 'interface
	titre(2,3,7,8,DARKGRAY,9," Enregister ",0);

	affiche(0);
	cache_souris();
	deco(); // Presentation du fond de l 'interface
	choix_menu=0;
	recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
	installation("c:\\msdos.sys","c:\\msdos.zch");

	init_souris();

	y=0;indice=1;
	do
	{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();

		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);

		if (kbhit())
		{
			touche=getch();
			if (touche==0) {
				touche=getch();
				if (touche==F3) {
					cache_souris();
					gettext(1, 1, 80, 25,sauve);
					cadre_plein(23,15,56,17,SIMPLE,WHITE,7,1);      // dessine le cadre
					locatext(25,16," Fichier en chargement ",0+16*7);
					recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
					puttext(1, 1, 80, 25,sauve);
					montre_souris();
				}
				if (touche==F10) {
					cache_souris();
					quitter();
				}
				if (touche==F4) {
					edit("c:\\MSDOS.SYS"); // Lance l editeur ZC
					deco();
					gettext(1, 1, 80, 25,sauve);
					cadre_plein(23,15,56,17,SIMPLE,WHITE,7,1);      // dessine le cadre
					locatext(25,16," Fichier en chargement ",0+16*7);
					recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
					puttext(1, 1, 80, 25,sauve);
//					locatext(50,25,"Le fichier a ‚t‚ charg‚     ",15+16*9);
					recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
				}

				if (touche==F5) {
					installation("c:\\msdos.zch","c:\\msdos.sys");
					recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
					aff_val();
				}
				if (touche==F1) {
					decrire_outwin();
				}
				if (touche==F2) {
					cache_souris();
					titre(2,3,14,1,DARKGRAY,9, " Enregister ",1);
					sauve_msdos(nbr_commande);
					titre(2,3,14,1,DARKGRAY,9, " Enregister ",0);
				}
				if (touche==FLECHE_EN_BAS) {
					if (++y==3) y=6;
					if (y>19) {
							y=19;
					}
				}
				if (touche==FLECHE_EN_HAUT) {
					if (--y==5) y=2;
					if (y<0) y=0;
				}

			}
		}

/*		if (bouton==BOUTON_GAUCHE_DROIT) {
			choix_menu=1;
		}
*/
/*		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<39)&&(valeur_xxreel>27)) {
/*		if (bouton==BOUTON_GAUCHE_DROIT) {
			choix_menu=1;
		}
			cache_souris();locatext(27,1," Utilisateur ",15+16*3);
			relacher_bsgauche();
			menu_user();
			printf("\a");
			bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit  E_xpress  _Utilisateur                                   _Aide  ");
		}
*/
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<11)&&(valeur_xxreel>3)) {
			cache_souris();locatext(3,1," Fichier ",15+16*3);
			relacher_bsgauche();
			menu_fichier();
			bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit  E_xpress                                                 _Aide  ");
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<17)&&(valeur_xxreel>12)) {
			cache_souris();
			locatext(12,1," Edit ",15+16*3);
			relacher_bsgauche();
			resultat=menu_edit();
			bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit  E_xpress                                                 _Aide  ");
		}

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<26)&&(valeur_xxreel>18))
		{
			cache_souris();locatext(18,1," Express ",15+16*3);
			relacher_bsgauche();
			resultat=menu_mode();
			bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit  E_xpress                                                 _Aide  ");
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==1)&&(valeur_xxreel<79)&&(valeur_xxreel>74))
		{
			cache_souris();locatext(74,1," Aide ",15+16*3);
			relacher_bsgauche();
			resultat=menu_aide();
			bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit  E_xpress                                                 _Aide  ");
		}

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==3)&&(valeur_xxreel<14)&&(valeur_xxreel>3)) {
			cache_souris();
			titre(2,3,14,1,DARKGRAY,9, " Enregister ",1);
			sauve_msdos(nbr_commande);
			titre(2,3,14,1,DARKGRAY,9, " Enregister ",0);
		}

		if ((bouton==BOUTON_GAUCHE)&&(y!=valeur_yyreel-5)) {
			y=valeur_yyreel-5;
			cache_souris();
			relacher_bsgauche();
			montre_souris();
			delay(60);
		}

//		if ((valeur_yyreel<8)&&(valeur_yyreel>3)&&(valeur_xxreel<29)&&(valeur_xxreel>3))		{

			if ((y==0)&&(indice!=0)) { affiche(y);locatext(4,5,"WinDir              ",15+16*12);indice=0;}
			if ((y==1)&&(indice!=1)) { affiche(y);locatext(4,6,"WinBootDir          ",15+16*12);indice=1;}
			if ((y==2)&&(indice!=2)) { affiche(y);locatext(4,7,"HostWinBootDrv      ",15+16*12);indice=2;}
//		}
//		if (valeur_yyreel<25)&&(valeur_yyreel>7)&&(valeur_xxreel<24)&&(valeur_xxreel>3))		{

			if ((y==6)&&(indice!=6)) { affiche(y);locatext(4,11,"Bootdelay               ",15+16*12);indice=6;}
			if ((y==7)&&(indice!=7)) { affiche(y);locatext(4,12,"BootFailSafe            ",15+16*12);indice=7;}
			if ((y==8)&&(indice!=8)) { affiche(y);locatext(4,13,"BootGUI                 ",15+16*12);indice=8;}
			if ((y==9)&&(indice!=9)) { affiche(y);locatext(4,14,"BootKeys                ",15+16*12);indice=9;}
			if ((y==10)&&(indice!=10)) { affiche(y);locatext(4,15,"BootMenu                ",15+16*12);indice=10;}
			if ((y==11)&&(indice!=11)) { affiche(y);locatext(4,16,"BootMenuDefault         ",15+16*12);indice=11;}
			if ((y==12)&&(indice!=12)) { affiche(y);locatext(4,17,"BootMenuDelay           ",15+16*12);indice=12;}
			if ((y==13)&&(indice!=13)) { affiche(y);locatext(4,18,"BootMulti               ",15+16*12);indice=13;}
			if ((y==14)&&(indice!=14)) { affiche(y);locatext(4,19,"BootWarn                ",15+16*12);indice=14;}
			if ((y==15)&&(indice!=15)) { affiche(y);locatext(4,20,"BootWin                 ",15+16*12);indice=15;}
			if ((y==16)&&(indice!=16)) { affiche(y);locatext(4,21,"DoubleBuffer            ",15+16*12);indice=16;}
			if ((y==17)&&(indice!=17)) { affiche(y);locatext(4,22,"Logo                    ",15+16*12);indice=17;}
			if ((y==18)&&(indice!=18)) { affiche(y);locatext(4,23,"LoadTop                 ",15+16*12);indice=18;}
			if ((y==19)&&(indice!=19)) { affiche(y);locatext(4,24,"Network                 ",15+16*12);indice=19;}
//		}

		if ((bouton==BOUTON_GAUCHE)||(touche==ENTREE)||(touche=='+')||(touche=='-')) {
			cache_souris();
			if (y==0) {
				if (found_file(fichier,r,"win.com","  Repertoire ou Windows est install‚ ")!=-1) {
					strcpy(valeur_table[0],r);
				}
				locatext(26,5+y,"                                 ",14+16*9);
				locatext(26,5+y,valeur_table[0],14+16*9);
			}
			if (y==1) {
				if (found_file(fichier,r,"win.com","  Repertoire ou Windows est Execut‚ ")!=-1) {
					strcpy(valeur_table[1],r);
				}
				locatext(26,5+y,"                                 ",14+16*9);
				locatext(26,5+y,valeur_table[1],14+16*9);
			}

			if (y==2) {
				if ((lecteur=lecteur_indefinie())!=0) { // 0 car la fonction revoie -1 + 1
					valeur_table[2][0]=(char)lecteur+65;
				}
				locatext(26,5+y,valeur_table[2],14+16*9);
			}
			if (y==6) { // Bootdelay
				if ((bouton==BOUTON_GAUCHE)||(touche=='+')) {
					delay_boot++;
				}
				if ((bouton==BOUTON_DROIT)||(touche=='-')) {
					delay_boot--;
				}
				if (delay_boot>60) 	{ delay_boot = 0; }
				if (delay_boot<0) 	{ delay_boot = 59; }
				delay(90);
				itoa(delay_boot,valeur_table[3],10); // Convertit delay_boot ( un entier ) en une chaŒne de caractŠres
				locatext(30,11,"   ",14+16*9); 		 // efface de l'ecran la precedente valeur
				locatext(30,11,valeur_table[3],14+16*9);  // Affiche la valeur itoa(delay_boot)
			}
			if ((y>6)&&(y<11)) {
				relacher_bsgauche();
				if (valeur_table[y-3][0]!='1') valeur_table[y-3][0]='1'; else valeur_table[y-3][0]='0';
				locatext(30,y+5,valeur_table[y-3],14+16*9);
			}
			if (y==11) { // BootMenuDelay
				relacher_bsgauche();
				mode_menu=menu_der(30,12,41,9,9,SIMPLE,11,12,8,11,1,4,str_Menu_default);
				if ((mode_menu>0)&&(mode_menu<9)) {
					delay(50);
					itoa(mode_menu,valeur_table[8],10);
					locatext(30,16,"  ",14+16*9);
					locatext(30,16,valeur_table[8],14+16*9);
				}
			}
			if (y==12) { // BootMenuDelay
				if ((bouton==BOUTON_GAUCHE)||(touche=='+')) {
					delay_demar++;
				}
				if ((bouton==BOUTON_DROIT)||(touche=='-')) {
					delay_demar--;
				}
				if (delay_demar>60) 	{ delay_demar= 0; }
				if (delay_demar<0) 	{ delay_demar= 59; }
				delay(50);
				itoa(delay_demar,valeur_table[10],10);
				locatext(30,17,"  ",14+16*9);
				locatext(30,17,valeur_table[10],14+16*9);
			}
			if ((y>12)&&(y<20)) {
				 relacher_bsgauche();
				if (valeur_table[y-3][0]!='1')
					valeur_table[y-3][0]='1';
				else
					valeur_table[y-3][0]='0';
				locatext(30,17+(y-12),valeur_table[y-3],14+16*9);
			}
///************************************************************************
			touche=-1; // Initialise la touche pour eviter les boucles ;
///************************************************************************
			montre_souris();
		}
	}
	while(choix_menu==0);
	init_souris();
	color(7,0);clrscr();
	cprintf("Outwin 95 par ");color(4,0);cprintf("Ó×ô ");color(7,0);cprintf("ZeCrusher");
	_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM);
	_setcursortype(_NORMALCURSOR);

	return(0);

}

void affiche(int numb)
{
	option_menu(15);cache_souris();
	signification(numb);

}
void presentation(void)
{
	cache_souris();
	fcadre_plein(20,7,61,20,SIMPLE,0,15,1);  // cadre rep
	//locatext(35,7,"",12+16*15);
	locatext(36,9,"OutWin 95",12+16*15);
	locatext(35,11,"Version 1.1",0+16*15);
	locatext(32,13,"Copirate  (Z) 1998",0+16*15);
	locatext(31,15,"Outwin95 by ZeCrusher",0+16*15);
	titre(37,18,14,1,DARKGRAY,15,"   Ó×ô   ",0);
	montre_souris();
	bouton_xyl(37,18,9); // Gestion du Bouton OK
	titre(37,18,14,1,DARKGRAY,15,"   Ó×ô   ",1);
	relacher_bsgauche();
	cache_souris();

}
void erreur_fichier(void)
{
	cache_souris();
	cadre_plein(24,7,56,11,0, 7  , 7   ,1);  // cadre rep
	locatext(24,7,"  Fichier MSDOS.SYS Introuvable  ",RED+16*WHITE);
	titre(36,9,YELLOW,1,DARKGRAY,7, " Quitter ",0);
	montre_souris();
	bouton_xyl(36,9,9); // Gestion du Bouton OK
	titre(36,9,YELLOW,1,DARKGRAY,7," Quitter ",1);
	cache_souris();
}
void deco(void)
{
 //	char police=-1;
	cache_souris();
	cadre_plein(1,1,80,26,1, 9 , 9 ,9);  // cadre rep
	locatext(1,1,"                                              							         ",LIGHTRED+16*WHITE);
	bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit  E_xpress                                                 _Aide  ");
	gotoxy(1,1);
	locatext(1,25,"                                                                             Ó×ô",1+16*9);
	titre(16,3,15,7,DARKGRAY,9, "                 Section Path               ",0);
	titre(16,9,15,7,DARKGRAY,9, "                Section Option              ",0);
	titre(40,11,15,7,DARKGRAY,9, " Signification ",0);
	titre(2,3,14,1,DARKGRAY,9, " Enregister ",0);

}
void option_menu(int color)
{
	locatext(4,5,"WinDir              ³",color+16*9);
	locatext(4,6,"WinBootDir          ³",color+16*9);
	locatext(4,7,"HostWinBootDrv      ³",color+16*9);
	locatext(4,11,"Bootdelay               ",color+16*9);
	locatext(4,12,"BootFailSafe            ",color+16*9);
	locatext(4,13,"BootGUI                 ",color+16*9);
	locatext(4,14,"BootKeys                ",color+16*9);
	locatext(4,15,"BootMenu                ",color+16*9);
	locatext(4,16,"BootMenuDefault         ",color+16*9);
	locatext(4,17,"BootMenuDelay           ",color+16*9);
	locatext(4,18,"BootMulti               ",color+16*9);
	locatext(4,19,"BootWarn                ",color+16*9);
	locatext(4,20,"BootWin                 ",color+16*9);
	locatext(4,21,"DoubleBuffer            ",color+16*9);
	locatext(4,22,"Logo                    ",color+16*9);
	locatext(4,23,"LoadTop                 ",color+16*9);
	locatext(4,24,"Network                 ",color+16*9);
	locatext(35,13,"  Type de donn‚es       Valeur par defaut  ",15+16*7);

	for(int i=0;i<14;i++) {
		locatext(28,11+i,"³",15+16*9);
	}
}
void signification(int numb)
{
	window(35,14,77,23);
	color(9,9);
	clrscr();
		locatext(65,15,"-",15+16*1);
	if (numb==0) {
		locatext(37,15,"R‚pertoire",14+16*1);
		locatext(37,17,"Le r‚pertoire o— Windows est install‚",15+16*1);
	}
	if (numb==1) {
		locatext(37,15,"R‚pertoire",14+16*1);
		locatext(37,17,"Le r‚pertoire … partir duquel Windows",15+16*1);
		locatext(37,18,"est ex‚cut‚.",15+16*1);
	}
	if (numb==2) {
		locatext(37,15,"Lecteur",14+16*1);
		locatext(37,17,"Le Lecteur de d‚marrage de Windows.",15+16*1);
		locatext(37,18,"(note N'indiquez pas les ' : ')",15+16*1);
	}

	if (numb==6) {
		locatext(37,15,"Nombre de seconde             2",14+16*1);
		locatext(37,17,"  Dur‚e pendant laquelle le message",15+16*1);
		locatext(37,18,"'D‚marrage de Windows 95' reste … ",15+16*1);
		locatext(37,19,"l'‚cran",15+16*1);
	}
	if (numb==7) {
		locatext(37,15,"   1 ou 0                     0",14+16*1);
		locatext(37,17,"1 = L'ordinateur d‚marre toujours en",15+16*1);
		locatext(37,18,"mode 'sans ‚chec'.",15+16*1);
		locatext(37,19,"0 = L'ordinateur d‚marre selon le mode",15+16*1);
		locatext(37,20,"appropri‚ , avec ou sans ‚chec'.",15+16*1);
	}
	if (numb==8) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Windows pr‚sente l'interface gra-",15+16*1);
		locatext(37,18,"phique (le bureau ).",15+16*1);
		locatext(37,19,"0 = Windows en reste … la ligne de com-",15+16*1);
		locatext(37,20,"mande du DOS.",15+16*1);
	}
	if (numb==9) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Les touches de fonction du demar-",15+16*1);
		locatext(37,18,"rage seront disponible.",15+16*1);
		locatext(37,19,"0 = Aucune touche de fonction ne sera  ",15+16*1);
		locatext(37,20,"utilisable . BootDelay sera ignor‚ et ",15+16*1);
		locatext(37,21,"le message 'D‚marrage de Windows 95' ne",15+16*1);
		locatext(37,22,"restera que deux secondes .",15+16*1);
	}
	if (numb==10) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Le menu de d‚marrage sera affich‚ ,",15+16*1);
		locatext(37,18,"mˆme sans enfoncer la touche F8",15+16*1);
		locatext(37,19,"0 = Le menu de d‚marrage sera affich‚  ",15+16*1);
		locatext(37,20,"uniquement si la touche F8 est enfonc‚e",15+16*1);
	}
	if (numb==11) {
		locatext(37,15,"   1 … 8                   1 ou 3",14+16*1);
		locatext(37,17,"1 = si le systŠme fonctionne",15+16*1);
		locatext(37,18,"3 = si le systŠme doit d‚marrer en mode",15+16*1);
		locatext(37,19,"sans ‚chec",15+16*1);
		locatext(37,20,"1 … 8 = est le num‚ro de l'option du",15+16*1);
		locatext(37,21,"menu qui sera ‚xecut‚e.A condition que",15+16*1);
		locatext(37,22,"le menu soit affich‚ avec Bootmenu =1",15+16*1);
	}
	if (numb==12) {
		locatext(37,15,"  Nombre de secondes          30",14+16*1);
		locatext(37,17,"La dur‚e d'affichage du menu. Si le com-",15+16*1);
		locatext(37,18,"pteur affich‚ atteint la valeur 0 sans",15+16*1);
		locatext(37,19,"intervention de l'utilisateur , l'option",15+16*1);
		locatext(37,20,"par defaut (BootMenuDefault) sera alors",15+16*1);
		locatext(37,21,"‚x‚cut‚e ",15+16*1);
	}
	if (numb==13) {
		locatext(37,15,"   1 ou 0                     0",14+16*1);
		locatext(37,17,"1 = La touche F4 sera disponible pour",15+16*1);
		locatext(37,18,"le chargement du systŠme d'exploitation",15+16*1);
		locatext(37,19,"ant‚rieure .",15+16*1);
		locatext(37,20,"0 = Seul Windows sera disponible",15+16*1);
	}
	if (numb==14) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Le message vous informant du mode",15+16*1);
		locatext(37,18,"'sans ‚chec' sera affich‚ si n‚cessaire",15+16*1);
		locatext(37,19,"0 = Ce message ne sera Jamais affich‚.",15+16*1);
	}
	if (numb==15) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = le systŠme d'exploitation Windows",15+16*1);
		locatext(37,18,"sera charg‚.",15+16*1);
		locatext(37,19,"0 = Le systŠme ant‚rieur sera charg‚ …",15+16*1);
		locatext(37,20,"condition que Windows le permette.",15+16*1);
	}
	if (numb==16) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Le double tampon est activ‚ , pour",15+16*1);
		locatext(37,18,"les contr“leurs de disques durs qui le",15+16*1);
		locatext(37,19,"demandent.",15+16*1);
		locatext(37,20,"0 = Le double tampon est d‚sactiv‚.",15+16*1);
	}
	if (numb==17) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Affiche le Logo Windows 95",15+16*1);
		locatext(37,19,"0 = N'Affiche PAS le Logo Windows 95",15+16*1);
	}
	if (numb==18) {
		locatext(37,15,"   1 ou 0                     1",14+16*1);
		locatext(37,17,"1 = Windows 95 charge Command.com      ",15+16*1);
		locatext(37,18,"DrvSpace.bin,DblSpace.bin dans la zone",15+16*1);
		locatext(37,19,"superieur de la Mem Conventionnelle",15+16*1);
		locatext(37,20,"0 = Windows occupe normalement la Mem",15+16*1);
		locatext(37,21,"conventionelle",15+16*1);
	}
	window(1,1,80,25);

}
int sauve_msdos(int cpt)
{
	FILE *out;


	if ((out = fopen("C:\\MSDOS.SYS","wt"))== NULL)	{
	   fprintf(stderr, "Impossible de cr‚er le fichier MSDOS.SYS\n");
	   exit(1);
	}
/* "Windir","WinBootDir","HostWinBootDrv","BootDelay","BootFailSafe",
   "BootGui","BootKeys","BootMenu","BootMenuDefault",
   "BootMenuDelay","BootMulti","BootWarn","BootWin",
   "DoubleBuffer","Logo","LoadTop","Network" */

	fputs("[Options]\n",out); // +1 l'index de l'ecran et nom pas du tableau char *table
	for (int i=0;i<cpt;i++)	{
		locatext(78,25,"Ó×ô",1+16*9);delay(10);
		if ((strlen(valeur_table[i])!=0)&&(Msdos95[i].type_donnee[8]=='o'))	{
			fputs(Msdos95[i].win_commande,out);
			locatext(78,25,"Ó×ô",3+16*9);delay(10);
			fputs("=",out);
			fputs(valeur_table[i],out);
			locatext(78,25,"Ó×ô",11+16*9);delay(10);
			fputs("\n",out);
		}
	}

	fputs("\n",out);
	fputs(";  Pour des raisons de compatibilit‚ , la taille de ce fichier\n",out);
	fputs(";  ne doit pas ˆtre inferieur … 1024 octets .\n",out);

//  The following lines are required for compatibility with other programs .
//  Do not remove them <MSDOS.sys needs to be > 1024 bytes> .

	fputs(";\n",out);
	fputs("\n",out);
	fputs(";/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxa\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxb\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxc\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxd\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxz\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxe\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxc\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxr\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxu\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxs\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxh\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxe\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxr\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxn\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxp\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxq\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxr\n",out);
	fputs(";xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxs*/\n",out);
	fputs("\n",out);

	fputs("[Paths]\n",out);
	for (int z=0;z<cpt;z++)	{
		locatext(78,25,"Ó×ô",1+16*9);delay(10);
		if ((strlen(valeur_table[z])!=0)&&(Msdos95[z].type_donnee[8]=='p'))	{
			locatext(78,25,"Ó×ô",3+16*9);delay(10);
			fputs(Msdos95[z].win_commande,out);
			fputs("=",out);
			locatext(78,25,"Ó×ô",11+16*9);delay(10);
			fputs(valeur_table[z],out);
			fputs("\n",out);
		}
	}
/*	fputs("WinDir=",out);fputs(valeur_table[0],out);fputs("\n",out);
	fputs("WinBootDir=",out);fputs(valeur_table[1],out);fputs("\n",out);
	fputs("HostWinBootDrv=",out);fputs(valeur_table[2],out);fputs("\n",out);
*/
	fclose(out);
	// replace les Attribut du fichier

	return(0);

}
int recup_info_msdos(char nom[32],char init)
{
	FILE *in;
//	int cpt=0;

	char *etat; // Pour la fin du fichier MSDOS.SYS
				// voir la boucle while

	if (init==1) {
		for (int j=0;j<69;j++) {
			strcpy(ligne_msdosys[j],"");
			strcpy(valeur_table[j],"");
		}
	}
	if (_dos_setfileattr("C:\\MSDOS.SYS",0) != 0)	{
	   erreur_fichier();
	   color(7,0);clrscr();
	   printf("OutWin 95 Ver 1 ( TSK )\n\n");
		// +h +r +s -a = _dos_setfileattr
		_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM);
	   exit(1);

	}
	// Important Copie le fichier pour plus de securite
	// Ligne … Changer en Fonction
	//	system("copy C:\MSDOS.SYS C:\MSDOS.95 >NUL");

	if ((in = fopen("C:\\MSDOS.SYS","rt"))== NULL)	{
	   erreur_fichier();
	   color(7,0);clrscr();
	   printf("OutWin 95 Ver 1 ( TSK )\n\n");
		_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM);
	   exit(1);
	}
	// initialise le nombre de ligne … zero
	nbr_ligne=0;

	do	{

		etat=fgets(ligne_msdosys[nbr_ligne++],90,in);

	}
	while(etat!=NULL);

	fclose(in);

	// tblx Position en x des ‚lements … afficher … l'ecran
	// tbly Position en y des ‚lements … afficher … l'ecran
	// valeur_table stocke les valeurs lue dans le fichier MSDOS.SYS
	// table sert de reference … valeur_table
	// table[0]="Windir" , etc voir char *table

	affiche(0);

	strcpy(Msdos95[0].win_commande,"Windir");		strcpy(Msdos95[0].type_donnee,"fichier_path");
	strcpy(Msdos95[1].win_commande,"WinBootDir");	strcpy(Msdos95[1].type_donnee,"fichier_path");
	strcpy(Msdos95[2].win_commande,"HostWinBootDrv");strcpy(Msdos95[2].type_donnee,"lecteur_path");

	strcpy(Msdos95[3].win_commande,"BootDelay");	strcpy(Msdos95[3].type_donnee,"decimal_option");
	strcpy(Msdos95[4].win_commande,"BootFailSafe");	strcpy(Msdos95[4].type_donnee,"binaire_option");
	strcpy(Msdos95[5].win_commande,"BootGui");		strcpy(Msdos95[5].type_donnee,"binaire_option");
	strcpy(Msdos95[6].win_commande,"BootKeys");		strcpy(Msdos95[6].type_donnee,"binaire_option");
	strcpy(Msdos95[7].win_commande,"BootMenu");		  strcpy(Msdos95[7].type_donnee,"decimal_option");
	strcpy(Msdos95[8].win_commande,"BootMenuDefault");strcpy(Msdos95[8].type_donnee,"binaire_option");
	strcpy(Msdos95[9].win_commande,"BootMenuDelay");strcpy(Msdos95[9].type_donnee,"binaire_option");
	strcpy(Msdos95[10].win_commande,"BootMulti");	strcpy(Msdos95[10].type_donnee,"binaire_option");
	strcpy(Msdos95[11].win_commande,"BootWarn");	strcpy(Msdos95[11].type_donnee,"binaire_option");
	strcpy(Msdos95[12].win_commande,"BootWin");		strcpy(Msdos95[12].type_donnee,"binaire_option");
	strcpy(Msdos95[13].win_commande,"DoubleBuffer");strcpy(Msdos95[13].type_donnee,"binaire_option");
	strcpy(Msdos95[14].win_commande,"Logo");		strcpy(Msdos95[14].type_donnee,"binaire_option");
	strcpy(Msdos95[15].win_commande,"LoadTop");		strcpy(Msdos95[15].type_donnee,"binaire_option");
	strcpy(Msdos95[16].win_commande,"Network");		strcpy(Msdos95[16].type_donnee,"binaire_option");

	nbr_commande=16;
	nbr_commande=analyse_table(17);

	for(int nbr_element_table=0;nbr_element_table<16;nbr_element_table++) {
		for(int i=0;i<nbr_ligne;i++) {
			if (recup_ligne(Msdos95[nbr_element_table].win_commande,ligne_msdosys[i],valeur_table[nbr_element_table])==0)		{
				locatext(tblx[nbr_element_table],tbly[nbr_element_table],valeur_table[nbr_element_table],14+16*9);				// Affiche les ‚lements de la table trouv‚s
			}
		}
	}

	_dos_setfileattr("c:\\Msdos.sys",0); // Supprime la Protection -hrsa

	return(nbr_ligne); // renvoie le nombre de ligne lue dans MSDOS.SYS

}

int recup_ligne(char element[30],char ligne[30],char valeur_ligne[80])
{
	// ligne , la ligne d'origine
	// Element , ce que l'on recherche
	// FICHIER_TEXTE , le type de fichier

	char chaine_decouper[30]={0};

	left(ligne,chaine_decouper,strlen(element),FICHIER_TEXTE);

	if (strcmpi(element,chaine_decouper)==0) { // ==0 ‚gale
	   // Ici l'element a ‚t‚ trouver  , ASCII 61 = ' = '
	   if ((ligne[strlen(element)])==61) {
		   right(ligne,valeur_ligne,strlen(ligne),strlen(ligne)-(strlen(element)+1));
		   valeur_ligne[strlen(valeur_ligne)-1]=0;
			return(0);
		}
	}
		return(-1);

}
int menu_user(void)
{


 return (0);
}
int menu_fichier(void)
{
	int resultat_menu=0;

	byte *str_fichier[7] = {" _Enregister MSDOS.SYS     F2","ÿ",
							" _Charger MSDOS.SYS        F3","ÿ",
							" _Restorer MSDOS.SYS       F5","ÿ",
							" _Quitter                 F10"};
	resultat_menu=menu_der(2,2,30,8,8,SIMPLE+DEROULER,15,12,BLACK,WHITE,BLACK,4,str_fichier);

	if (resultat_menu==1) {
		sauve_msdos(nbr_commande);
		locatext(50,25,"Le fichier a ‚t‚ enregist‚",15+16*9);
	}
	if (resultat_menu==3) {
		recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
		locatext(50,25,"Le fichier a ‚t‚ charg‚     ",15+16*9);
		aff_val();
	}
	if (resultat_menu==5) {
		installation("c:\\msdos.zch","c:\\msdos.sys");
		locatext(50,25,"Le fichier a ‚t‚ restor‚    ",15+16*9);
		recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
		aff_val();
	}
	if (resultat_menu==7) {
		quitter();
	}



	return(resultat_menu);
}
void erreur_system(void)
{
	char buffer[4096];

	cache_souris();

	gettext(1, 1, 80, 25, buffer);
	cadre_plein(24,7,56,11,0, 7  , 7   ,1);  // cadre rep
	locatext(24,7," ***          Erreur         *** ",LIGHTRED+16*WHITE);
	titre(36,9,15,RED,DARKGRAY,7, "    OK    ",0);
	montre_souris();
	bouton_xyl(36,9,10); // Gestion du Bouton OK
	titre(36,9,15,RED,DARKGRAY,7,"    OK    ",1);
	cache_souris();
	puttext(1, 1, 80, 25, buffer);

}

int menu_edit(void)
{
	byte *str_edit[5]  ={" _Msdos              F4"," _Autoexec.bat"," _Config.sys ","ÿ"," _Choisir un ‚diteur"};

	int resultat_menu=0;

	resultat_menu=menu_der(11,2,24,6,6,SIMPLE+DEROULER,15,12,BLACK,WHITE,BLACK,4,str_edit);

	if (resultat_menu==1) {
		edit("c:\\MSDOS.SYS"); // Lance l editeur ZC
		deco();
		locatext(50,25,"Le fichier a ‚t‚ charg‚     ",15+16*9);
		recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS
	}
	if (resultat_menu==2) {
		edit("c:\\autoexec.bat"); // Lance l editeur ZC
	}
	if (resultat_menu==3) {
		edit("c:\\config.sys"); // Lance l editeur ZC
	}
	if (resultat_menu==5) {
		choisir_editeur();
	}
	return(0);

}
int menu_aide(void)
{
	int resultat_menu=0;
	char buffer[4096];


	byte *str_fichier[9]  ={" _Description de OUTWIN95     F1","ÿ"," _Un peu d'Histoire  ","ÿ"," _Mots cl‚s de Bootlog.txt"," _Effet du Mode sans ‚chec","ÿ"," A _Propo de ... "};

	byte *str_aide[33]  ={"  Le premier au poste ","  _Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä",
						  "    Les deux premiers fichiers charg‚s en m‚moire se nomment",
						  "   IO.SYS et MSDOS.SYS . Ils sont toujours  pr‚sents dans le",
						  "   r‚pertoire racine du disque … partir  duquel l'ordinateur",
						  "   d‚marre . ",
						  "   Leurs comp‚tences se  sont ‚tendues , Msdos.sys ‚tant mˆme ",
						  "   devenu un fichier texte . ",
						  "   IO.SYS est un fichier de 210 ko environ qui d‚finit",
						  "   entierement le systŠme. il regroupe les fonctionnalit‚s",
						  "   des anciens IO et MSDOS.sys.",
						  "   Il ne peut pas ˆtre ‚dit‚ : il est impossible de modifier",
						  "   directement les instructions et les valeurs par d‚faut."," ",
						  "   MSDOS.SYS","   _Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä"," ",
						  "       Msdos.sys est compos‚ de deux sections , … savoir",
						  "   [Paths] et [Options], contenant chacunne des instructions",
						  "   sp‚cifiques . La section [Paths] mentionne l'emplacement ",
						  "   des fichiers de Windows 95. La section [Options] est … la",
						  "   disposition des utilisateurs dans le but de personnaliser",
						  "   le lancement de Windows 95.",
						  "     En ‚ditant le fichier d'initialisation MSDOS.sys , vous",
						  "   remarquerez imm‚diatement qu'il comporte quelque lignes ",
						  "   de x apparemment inutiles . Ne les effacez pas : elles ",
						  "   permettent au fichier d'atteindre une taille sup‚rieure …",
						  "   1 024 octets. En effet une taille inferieure serait mal ",
						  "   interpret‚e ."," "
						  };

	cache_souris();
	gettext(1, 1, 80, 25, buffer);

	resultat_menu=menu_der(45,2,33,9,9,SIMPLE+DEROULER,15,12,BLACK,WHITE,BLACK,4,str_fichier);

	if (resultat_menu==1) {
		decrire_outwin();
	}
	if (resultat_menu==3) {
		menu_der(5,3,69,22,30,DOUBLE,0,11,1,11,0,8,str_aide);

	}
	if (resultat_menu==5) {
		decrire_bootlog();
	}
	if (resultat_menu==6) {
		decrire_echec();
	}

	if (resultat_menu==8) {
		fcadre_plein(20,7,61,20,SIMPLE,0,15,1);  // cadre rep
		locatext(35,7," A propo de ",12+16*15);locatext(36,9,"OutWin 95",0+16*15);
		locatext(35,11,"Version 1.1",0+16*15);locatext(32,13,"Copirate  (Z) 1998",0+16*15);
		locatext(31,15,"Outwin95 by ZeCrusher",0+16*15);
		titre(37,18,YELLOW,1,DARKGRAY,15,"   OK   ",0);
		montre_souris();
		bouton_xyl(37,18,8); // Gestion du Bouton OK
		titre(37,18,YELLOW,1,DARKGRAY,15,"   OK   ",1);
		relacher_bsgauche();cache_souris();
	}
	puttext(1, 1, 80, 25, buffer);

	locatext(30,25,"                                                 ",15+16*9);

	return(resultat_menu);
}
int faire_fichier_boot(void)
{
	FILE *out;
	char files_boot[16]={0xB8,0x40,0,0x8E,0xD8,0xB8,0x34,0x12,0xA3,0x72,0,0xEA,0,0,0xff,0xff};

	if ((out = fopen("c:\\DOS\\ZCBOOT.COM", "wb"))== NULL)	{
	   fprintf(stderr, "Cannot open input file.\n");
	   return 1;
	}
	for (int i=0;i<16;i++)
		fputc(files_boot[i],out);

	printf("\n Le fichier 'ZCBOOT' a ‚t‚ cr‚e avec succ‚s ...!!\n");

	return(0);
}
int quitter(void)
{
	int ev_recu=0;
	char buffer[4096];

	gettext(1,1,80,25, buffer);


	winp(15,5,68,15,BLACK,WHITE,3,"   Quitter OutWin 95 ....");

	titre(17,7,YELLOW,1,DARKGRAY,3, " Quitter ",0);
	locatext(29,7,"\7",10+16*3);locatext(31,7,"Le contr“le est rendu au dos ou",15+16*3);
	locatext(31,8,"au programme appelant en general.",15+16*3);
	titre(17,10,YELLOW,1,DARKGRAY,3, " Rebooter ",0);
	locatext(29,10,"\7",10+16*3);locatext(31,10,"L'ordinateur REDEMARRE pour que les",15+16*3);
	locatext(31,11,"changements soient pris en compte.",15+16*3);
	titre(17,13,15,12,DARKGRAY,3, " Annuler  ",0);
	locatext(29,13,"\7",12+16*3);locatext(31,13,"Retourne au programme ",15+16*3);
	locatext(18,7,"Q",12+16*1);
	locatext(18,10,"R",12+16*1);
	locatext(18,13,"A",4+16*12);
	init_souris();
	do
	{
	  ev_recu=bouton_type(17,7,8,'Q',1,0);
	  ev_recu=bouton_type(17,10,8,'R',2,ev_recu);
	  ev_recu=bouton_type(17,13,11,'A',3,ev_recu);
	}
	while(ev_recu==0);
	cache_souris();

	if (ev_recu==1) {
		titre(17,7,YELLOW,1,DARKGRAY,3, " Quitter ",1);
		init_souris();
		_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM);
		color(7,0);clrscr();
		cprintf("Outwin 95 par ");color(4,0);cprintf("Ó×ô ");color(7,0);cprintf("ZeCrusher");
		_setcursortype(_NORMALCURSOR);
		exit(0);
	}
	if (ev_recu==2) {
		init_souris();color(7,0);
		_dos_setfileattr("C:\\MSDOS.SYS",FA_RDONLY|FA_HIDDEN|FA_SYSTEM);
		if (execv("c:\\dos\\zcboot.com",NULL)==-1) {
			erreur_system();
		}
	}
	if (ev_recu==3) {
		titre(17,13,15,12,DARKGRAY,3, " Annuler  ",1);
	}

	relacher_bsgauche();
	cache_souris();
	puttext(1,1,80,25, buffer);
	montre_souris();

	return(0);
}
void decrire_outwin(void)
{

	byte *str_commande[48]  ={"  _1   Utilisation de l'Aide _º","  _Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_¼","",
							  "  Faites d‚filer pour voir la suite de l'‚cran","",
							  "  Le systŠme d'aide se manipule avec les commandes de menus. Vous",
							  "  pouvez  utiliser les  ascenseurs symbolis‚s par les  caracteres ",
							  "  '\x1E' '\x1F' plac‚ sur la droite du menu , soit avec les fl‚ches",
							  "  du clavier . ","","",
							  "   _2  OutWin en quelques mots _º",
							  "   _Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_Í_¼","",
							  "  "," "," "," "," "," "," "," "," "," "," "," ",""};

		menu_der(5,3,69,20,28,SIMPLE,0,11,1,11,0,4,str_commande);

}
void decrire_bootlog(void)
{

	byte *str_commande[42]  ={"  La d‚tection des d‚faillances  "," _Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_",
							  "  L'option Journal de d‚marrage permet de d‚crire dans",
							  "  un fichier journal (Bootlog.txt) le d‚roulement de la",
							  "  phase de lancement.",
							  "  afin de le consulter , vous le trouverez dans le ",
							  "  disque de d‚marrage C:\ .","",
							  "  Attention , il possede l'attribut cach‚ .","",
							  "  A chaque cr‚ation d'un nouveau fichier Bootlog la version",
							  "  pr‚cedente de Bootlog.txt est copi‚e dans Bootlog.prv","",
							  "  Les Mots cl‚s utilis‚s par BootLog.txt","",
							  "  Error                      Erreur survenue pendant le",
							  "                             d‚marrage",
							  "  Fail                       Echec survenu pendant le",
							  "                             d‚marrage",
							  "  Dynamic load success       Pilote de p‚riph‚rique charg‚",
							  "                             dynamiquement",
							  "  Load Start                 Debut de chargement",
							  "  LoadSuccess                Chargement r‚ussi",
							  "  Loading device             P‚ripherique charg‚",
							  "  Loading Vxd                P‚ripherique virtuel charg‚",
							  "  LoadFailed                 Echec de chargement",
							  "  SYSCRITINIT                Initialisation du systŠme",
							  "  SYSCRITINIT-SUCCEESS       Initialisation du systŠme",
							  "                             R‚ussie",
							  "  DEVICEINIT                 Initialisation de p‚ripherique",
							  "  DEVICEINIT-SUCCESS         Initialisation r‚ussie",
							  "  Dynamic load device        Chargement dynamique de",
							  "                             p‚ripherique",
							  "  Dynamic init device        Initialisation dynamique de",
							  "                             p‚ripherique",
							  "  Initing                    Initialisation",
							  "  Init Success               Initialisation r‚ussie",
							  "  INITCOMPLETE               Initialisation termin‚e",
							  "  InitDone                   Initialisation termin‚e",
							  "  Status                     Indicateur","",""};

		menu_der(5,3,62,20,42,SIMPLE,15,3,15,3,15,4,str_commande);
}
void decrire_echec(void)
{
	byte *str_commande[27]  ={"  Le Mode SANS ECHEC "," _Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_Ä_",
							  "    Suite … un problŠme qui , en principe , empˆcherait",
							  "    Windows de fonctionner , le Mode Sans Echecs d‚marre",
							  "    le systŠme.",""
							  "    Effet des deux principaux modes SANS ECHEC",
							  "    \x1( Voir BootFailSafe \x1)",
							  "                                                       Ligne de",
							  "                                      Mode         commande en mode",
							  "                                   Sans Echec         Sans Echec",
							  "",
							  "  \xe- Ex‚cution des Fichiers             \x4N\x4o\x4n                \x4N\x4o\x4n",
							  "    Config et Autoexec            ","",
							  "  \xe- Chargement de Himem.sys            \x1O\x1u\x1i                \x4N\x4o\x4n","",
							  "  \xe- Ex‚cution de la base de            \x4N\x4o\x4n                \x4N\x4o\x4n",
							  "    de registres                                             ","",
							  "  \xe- Chargement de command.com          \x4N\x4o\x4n                \x1O\x1u\x1i","",
							  "  \xe- Ouverture du bureau Windows        \x1O\x1u\x1i                \x4N\x4o\x4n","",
							  "  \xE- Chargement des pilotes             \x4N\x4o\x4n                \x4N\x4o\x4n",
							  "   virtuels 32 bits",
							  "",""
							  };

		menu_der(5,3,72,21,27,SIMPLE,15,3,15,3,15,4,str_commande);


}
int choisir_editeur(void)
{
	char fichier[20];
	char r[200];
	char editeur_extern[220];
	char editwinp[60];
	extern int errno;

	sauve_msdos(nbr_commande);

	if (found_file(fichier,r,"*.exe","  Choix d'un editeur externe ....")==-1)	{
		return(0); // Option Annuler
	}
	// OK
	cache_souris();
	strcpy(editeur_extern,r); // Je copie la chaine contenant le nom du rep
	strcat(editeur_extern,"\\");
	strcat(editeur_extern,fichier);
	strcat(editeur_extern," c:\\msdos.sys");
	strcpy(editwinp," Editeur externe  "); // Je copie la chaine contenant le nom du rep
	strcat(editwinp,fichier); // Je copie la chaine contenant le nom du rep

	if (system(editeur_extern)==-1) {
		erreur_system();
	}
	charger_table("long.als");   // Charge la police de caractere ALES
	cache_souris();
	fond(0);
	table_ascii();		// F1 , Cr‚ation des nouveau char ASCII
	deco();
	affiche(0);
	recup_info_msdos("c:\\MSDOS.SYS",1); // Recupere les donn‚es du fichier MSDOS.SYS

	return(0);
}

int menu_mode(void)
{
	int resultat_menu=0;

	byte *str_fichier[16] = {" _0  D‚marrer avec le bureau Windows 95",
							" _1  D‚marrer sous MSDOS 7.xx","ÿ",
							" _2  Afficher le logo Windows 95",
							" _3  Ne pas afficher le logo Windows 95","ÿ",
							" _4  D‚marrer en mode sans Echec",
							" _5  D‚marrer en mode appropri‚ " ,"ÿ",
							" _6  Active le tampon double",
							" _7  D‚sactive le tampon double","ÿ",
							" _8  Afficher le menu de demarage",
							" _9  Ne pas afficher le menu de d‚marrage",
							};

	resultat_menu=menu_der(17,2,45,15,15,SIMPLE+DEROULER,15,12,BLACK,WHITE,BLACK,4,str_fichier);

	if (resultat_menu==1) strcpy(valeur_table[5],"1"); // 5 BootGui
	if (resultat_menu==2) strcpy(valeur_table[5],"0"); // 5 BootGui
	if (resultat_menu==4) strcpy(valeur_table[14],"1"); // 14 Logo
	if (resultat_menu==5) strcpy(valeur_table[14],"0"); // 14 Logo
	if (resultat_menu==7) strcpy(valeur_table[4],"1"); //  4 "BootFailSafe",
	if (resultat_menu==8) strcpy(valeur_table[4],"0"); //  4 "BootFailSafe",
	if (resultat_menu==10) strcpy(valeur_table[13],"1"); //  13 "DoubleBuffer",
	if (resultat_menu==11) strcpy(valeur_table[13],"0"); //  13 "DoubleBuffer",
	if (resultat_menu==13) strcpy(valeur_table[7],"1"); //  7 "BootMenu",
	if (resultat_menu==14) strcpy(valeur_table[7],"0"); //  7 "BootMenu",

	if ((resultat_menu!=-1)&&(resultat_menu!=555)&&(resultat_menu!=555)) {
		locatext(1,25," Les changements r‚ussie .....                                                  ",14+16*1);
		delay(400);
		locatext(1,25,"                                                                                ",9+16*9);
		cache_souris();
		titre(2,3,14,1,DARKGRAY,9, " Enregister ",1);
		sauve_msdos(nbr_commande);
		titre(2,3,14,1,DARKGRAY,9, " Enregister ",0);
		quitter();
	}
	aff_val();

	return(0);
}
void aff_val(void)
{
		for(int i=0;i<20;i++) {
			locatext(tblx[i],tbly[i],valeur_table[i],14+16*9);
		}
}
int installation(char file_source[20],char file_objet[20])
{
	FILE *in, *out;

	long length=0,copi=0,divid=0,incr=0;
	int pas=0;
	char sauve[4096];

	gettext(1, 1, 80, 25,sauve);

	textbackground(9);

		if ((in = fopen(file_source, "rb"))== NULL)
		{   locatext(6,25,"Cliquez sur Entr‚e ou tapez sur entr‚e pour continuer                ",1+16*15); // inscrit le nom du fichier en train d'ˆtre visualiser
			fenetre(20,8,52,14,LIGHTRED,WHITE,WHITE,"Erreur detect‚e");
			locatext(27,10,"Erreur sur fichier",BLACK+16*WHITE);
			locatext(26,11,"V‚rifi‚ la disquette",BLACK+16*WHITE);
			titre(31,13,LIGHTRED,RED,DARKGRAY,WHITE, "  Entr‚e  ",0);
			bouton_xyl(31,13,10);
			titre(31,13,LIGHTRED,RED,DARKGRAY,WHITE, "  Entr‚e  ",1);
			puttext(1, 1, 80, 25,sauve);
			return(1);
		}

	if ((out = fopen(file_objet, "wb"))== NULL)
	{  	fenetre(20,8,52,14,LIGHTRED,WHITE,WHITE,"Erreur detect‚e");
		locatext(27,10,"Impossible de cr‚er",BLACK+16*WHITE);
		locatext(26,11,"le fichier          ",BLACK+16*WHITE);
		titre(31,13,LIGHTRED,RED,DARKGRAY,WHITE, "  Entr‚e  ",0);
		bouton_xyl(31,13,10);
		titre(31,13,LIGHTRED,RED,DARKGRAY,WHITE, "  Entr‚e  ",1);
		puttext(1, 1, 80, 25,sauve);
		return(1);
	}

	fseek(in,0L, SEEK_END);
	length = ftell(in);
	fseek(in,0L,SEEK_SET);

	divid=length/33;
	cadre_plein(23,15,56,17,SIMPLE,WHITE,7,1);      // dessine le cadre
	locatext(25,15," En cours ",0+16*7);

	color(14,1);

	while (copi<length)
	{
		copi++;
		incr++;
		locatext(78,25,"Ó×ô",1+16*9);
		if (incr>divid) {
			gotoxy(36,16);
			locatext(78,25,"Ó×ô",3+16*9);
			delay(10);
			printf("<%% %2d>",pas*100/33);
			modif_fond(pas+24,16,1,15+16*9,0);
			pas++;incr=0;
			locatext(78,25,"Ó×ô",11+16*9);
			delay(10);
	  }
		fputc(fgetc(in), out);
	}

	puttext(1, 1, 80, 25,sauve);

	fclose(in);
	fclose(out);

	return (0);
}
int lecteur_indefinie(void)
{
	int resultat_menu;
	int nbr_lecteur=0;
	int taille=0;

	byte *str_disk[24]={" _C: ÏÐµ "," _D: ÏÐµ "," _E: ÏÐµ "," _F: ÏÐµ "," _G: ÏÐµ ",
						" _H: ÏÐµ "," _I: ÏÐµ "," _J: ÏÐµ "," _K: ÏÐµ "," _L: ÏÐµ "," _M: ÏÐµ "," _N: ÏÐµ ",
						" _O: ÏÐµ "," _P: ÏÐµ "," _Q: ÏÐµ "," _R: ÏÐµ "," _S: ÏÐµ "," _T: ÏÐµ "," _U: ÏÐµ ",
						" _W: ÏÐµ "," _X: ÏÐµ "," _Y: ÏÐµ "," _Z: ÏÐµ " };


	nbr_lecteur=recherche_nbr_lecteur();

	if (nbr_lecteur>10) taille=10; else taille=nbr_lecteur;

	relacher_bsgauche();
	resultat_menu=menu_der(30,7,9,taille+1,nbr_lecteur-1,SIMPLE,WHITE,LIGHTRED,DARKGRAY,11,BLACK,BLUE,str_disk);

	return(resultat_menu+1);

}
void screen(void)
{
	union REGS _r_in,_r_out;

	_r_in.h.ah=0x00;
	_r_in.h.al=0x03;
	int86(VIDEO,&_r_in,&_r_out); 	// Execution de l'interuption logiciel VIDEO
}
int analyse_table(int cpt)
{
	FILE *in;
	char msg[129];
	char buffer[310]; //  = ( 68 - 23 ) * ( 17 - 15 ) * 2 Voir CADRE_PLEIN ci-dessous
	char commande[64];  // commande cr‚e par le User .
	char comment[128]; // Pour les commentaires de l utilisateur … propos de la commande .
	char min[10]={0},max[10]={0}; // si il y a un type decimal_option ou decimal_path

	char type_com[20]={0};

	int val=0;

	gettext(23,15, 60,18, buffer); // Sauvegarde de l'ecran Outwin

//	cadre_plein(23,15,58,17,SIMPLE,15,7,1);      // dessine le cadre
//	locatext(25,15," Analyse du fichier Table.out ",0+16*7);

	if ((in = fopen("c:\\TSK\\table.out", "rt"))== NULL)	{
	   fclose(in);
	   return 1;
	}

	do
	{
		fgets(msg,128,in);
		val=analyser_ligne(msg,commande,type_com,min,max,comment);
		if (val!=1) {
				strcpy(Msdos95[cpt].win_commande,commande);
				strcpy(Msdos95[cpt].type_donnee,type_com);
				strcpy(Msdos95[cpt].min,min);
				strcpy(Msdos95[cpt].max,max);
				strcpy(Msdos95[cpt].commentaire,comment);
				cpt++; // incrementation du compteur pour la structure.
		}
	}
	while(!feof(in));


	puttext(23, 15, 60, 18, buffer); // Sauvegarde de l'ecran Outwin
//  exit(0);

  return(cpt);

}
int analyser_ligne(char ligne[128],char commande[32],char type[20],char min[10],char max[10],char commentaire[128])
{
	int taille=0,pvirgule=0,espace=0;
	char format[11]={'[',']','=',44,'(','-',')','"','"',';'};
	// [commande]=Texte,

//	strcpy(commande,0);
//	strcpy(commande,"");

	int emplacement[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	if ((taille=strlen(ligne))>128) taille=128;

	for (int i=0;i<taille-1;i++)	{ /////////////// for //////////////////////////////////////////////
		if (ligne[i]==';') pvirgule=1;
		if (ligne[i]==' ') espace++;
		if ((ligne[i]=='/')&&(ligne[i+1]=='/')) { // commentaire trouv‚
			if ((espace!=i)&&(pvirgule!=1)) {	  // Il y a t-il des chars autre que ' ' (0x20) devant et pas de ; devant
				return(0);						  // Erreur
			}
				return(1);                        // OK la ligne est un commentaire
		}
	}
	for (int j=0;j<taille;j++) 	{
		for (int a=0;a<10;a++) 		{ // Nombre de caractere , [ ] = ( ) , " " ;
			if (ligne[j]==format[a]) {
				emplacement[a]=j;
			}
		}
	}
	//0 ='[',1=']',2='=',3=44 , 4 ='(','-',')','"','"',';'};
	delay(10);
	if (emplacement[0]==-1)	return(1); 	//ici il y a une erreur car pas de [ trouver dans la ligne du fichier

	strdecoupe(ligne,commande,emplacement[0]+1,emplacement[1]);
	strdecoupe(ligne,type,emplacement[2]+1,emplacement[3]);

	if (type[0]=='d')
		strdecoupe(ligne,type,emplacement[2]+1,emplacement[4]);
	if (emplacement[4]!=-1)
		strdecoupe(ligne,min,emplacement[4]+1,emplacement[5]);
	if (emplacement[6]!=-1)
		strdecoupe(ligne,max,emplacement[5]+1,emplacement[6]);
	if (emplacement[7]!=-1)
		strdecoupe(ligne,max,emplacement[7]+1,emplacement[8]);
	return(0);
}
