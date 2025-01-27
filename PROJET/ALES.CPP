// Programme ALES  par ZeCrusher
// Utilitaire en Mode texte 80x25
// RÇalisÇ le: 12/12/1994
// Därniäre modif: 08/02/96


#if !defined( __DOS_H )
 #include <dos.h>
 #define __DOS_H
#endif

#if !defined( __CONIO_H )
 #include <conio.h>
 #define __CONIO_H
#endif
#if !defined( __CTYPE_H )
 #include <ctype.h>
 #define __CTYPE_H
#endif
#if !defined( __STDIO_H )
 #include <stdio.h>
 #define __STDIO_H
#endif
#if !defined( __STDLIB_H )
 #include <stdlib.h>
 #define __STDLIB_H
#endif
#if !defined( __IO_H )
 #include <io.h>
 #define __IO_H
#endif

 #define CLS 			textbackground(BLACK);clrscr();
 #define END			CLS;exit(EXIT_SUCCESS)
 #define SPACE(x)		for(tmp=0;tmp<x;tmp++) cprintf(" ")

 #define MOUSE_PRESENTE			1	// Definition des constantes pour mouse_present();
 #define MOUSE_ABSENTE 			-1	//
 #define ZERO_BOUTON			0	// definition des bouton de la souris ......
 #define ZERO_BOUTON_APPUYER	0	// definition des bouton de la souris .....
 #define INIT_BOUTON			0
 #define BOUTON_DROIT		    2	// Les boutons de la souris sont ici definie pour une souris
 #define BOUTON_GAUCHE 			1	// donc seulement deux boutons, le DROIT et le GAUCHE, sont actif
 #define BOUTON_GAUCHE_DROIT	3	// pour une souris Ö trois bouton
 #define INIT_SOURIS			0
 #define MONTRE_SOURIS			1
 #define CACHE_SOURIS			2
 #define ETAT_SOURIS			3
 #define MOUSE					0x33
 #define Fichier_max			999
 #define Repertoire_max			999


// Test de la configuration de la MÇmoire Ö la compilation .....

 #include "C:\tsk\fct\fmem__.cpp" // Verifie les Erreurs du au modele de mÇmoire
 #include "C:\tsk\fct\fmouse.h"
 #include "C:\tsk\fct\fmenu.h"
 #include "C:\tsk\fct\fcadre.h"
 #include "C:\tsk\fct\fascii.h"
 #include "C:\tsk\fct\finputxt.h"
 #include "C:\tsk\fct\ffichier.h"

typedef unsigned char byte;

extern void fond(int mode);
extern void winp(int x,int y,int x1,int y1,int color_texte,int color_fond,int winp_color,char *texte);
////////////////////// FMOUSE
extern void relacher_bsgauche(void);

 int charger_table_(char nom_police[80]);
 int fusionner_table_(char nom_police[80]);
void definition_ascii_(byte table[16],byte ascii);
 int recuperer_police(char *nom_source,char *nom_objet);

// int charger_table(char nom_police[80]);
 int sauver_table(char nom_police[80]);
void afficher_code_ascii(int numero);
void def(int n);
void init_tab(int num);
void menu_copie(int num);
void menu_fichier(void);
void presentation(void);
void creer_ligne(int num);
char afficher_liste(void);

extern int place_r,place_f;
extern long ficompt;

	extern int posx,posy,bouton,   // position de la souris sur l'ecran multiple de 8
		ScrMaxX,ScrMaxY,
		valeur_xxreel,     // coordonner de la sortie qui est Çgale a (posx/8)+1   1 a 25
		valeur_yyreel;

	extern int	nbr_fichier,nbr_repertoire,nbr_lecteur_logique,nbr_lecteur_totaux;
			struct liste_repertoire	{
					char repertoire[13];
//					char niveau;
			};
	extern	struct	liste_repertoire num_repertoire[Repertoire_max];

	struct liste_fichier	{
		char files[14];	// nom du fichier 13 = 8 char + 1 "." + 3 char extention
		unsigned long	taille;  // + 1 de code de spÇcification
		char attribut;
	};
	extern  struct	liste_fichier num_fichier[Fichier_max];

	int lettre=-1;
	byte table[8][16];
	byte copie[16];
	byte identificateur[16]={0};
	byte tab[256][16],touche=0;
	byte changer[256];
	byte nom_defaut[80];

int main(char argc, char **argv)
{
	char ecran[4096];
//	char fichier[100];
	int choix_menu=0,pas=0;
	strcpy(nom_defaut,"d:\\tsk\\table.als");

	fond(0);

//found_file(fichier,"*.*");
//	exit(0);


	 for (int a=0;a<255;a++) {
		for (int i=0;i<16;i++)  {
			 tab[a][i]='*';
			}
		changer[a]='X';
	 }

	if ((argc>3)||(argc==1)) {
		clrscr();
		color(15,1);
		cprintf("\n\r\n\r ALES changement des caractäres ascii [ T S K _96]\n\r");
		color(0,7);
		cprintf("\n\rALES /modif fichier.als ");
		color(7,0);
		cprintf("\n\r  pour modifier les codes acsii , police 16x8 \n\r");
		color(0,7);
		cprintf("\n\rALES /charger fichier.als \n\r");
		color(7,0);
		cprintf("  pour charger une police de caractäre dans l'Çditeur de caractäres (16x8)\n\r");
		printf("\n\n\n");
		exit(0);
	}

	if ( (strcmp(argv[1],"/CHARGER")==0)||(strcmp(argv[1],"/charger")==0) )
	{  CLS;color(0,7);
		cprintf(" TSK_ ZeCrusher   , Police dos  ALES version 1.00 [02-07-96]\n\r");
		color(7,0);
		cprintf("Chargement de la table >%s\n\r",argv[2]);
		charger_table_(argv[2]);
		cprintf("liste 1 : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\r");
		cprintf("liste 2 : abcdefghijklmnopqrstuvwxyz\n\r");
		cprintf("liste 3 : 0 1 2 3 4 5 6 7 8 9 0\n\r");
		cprintf("liste 4 : Ä Å Ç É Ñ Ö Ü á à â ä ã å ç\n\r");
		exit(0);
	}

	if ((strcmp(argv[1],"/modif")==0)||(strcmp(argv[1],"/MODIF")==0))
	{
		color(7,0);clrscr();printf(" ALES par ZeCrusher \n");
		if (argv[2]==NULL)		{
			if (charger_table_(nom_defaut)==-1)	{
				exit(0);
			}
		}
		else
		{
			if (charger_table_(argv[2])==-1)	{
				exit(0);
			}
			strcpy(nom_defaut,argv[2]);
		}
	}

	presentation();
	sauver_table("tabletsk.bak");

	color(7,0);
	clrscr();
	textcolor(WHITE);textbackground(LIGHTGRAY);
	for(int i1=0;i1<25;i1++) for(int i2=0;i2<5;i2++) cputs ("≤≤≤≤≤≤≤≤≤≤≤≤≤≤≤≤");
	cadre_plein(4,5,19,22,SIMPLE,WHITE,BLUE,1);      // dessine le cadre
	cadre_plein(24,4,72,22,DOUBLE,15,7,1);      // dessine le cadre

	for (int in=0;in<16;in++) {
		gotoxy(13,6+in);color(WHITE,1);
		cprintf("≥");
	}
	gotoxy(13,5);cprintf("¬");
	gotoxy(13,22);cprintf("¡");
	locatext(14,22,"¥   √",WHITE+16*BLUE);
	locatext(6,22,"¥   √",WHITE+16*BLUE);
	locatext(15,22,"- +",14+16*1);


	titre(26,5,YELLOW,1,DARKGRAY,LIGHTGRAY," Modification des codes ascii ",0);
	locatext(1,1,"                                   A L E S                        TSK_ ZECRUSHER",15+16*12);
	locatext(1,2,"  Fichier   Edition   Aide                                                      ",15+16*8);
	locatcar(3,2,'F',12+16*8);
	locatcar(13,2,'E',12+16*8);
	locatcar(23,2,'A',12+16*8);

	init_souris();

	afficher_liste();

	afficher_code_ascii(0);


	do 	// Boucle principal !!!!!!!!
	{
		_setcursortype(_NOCURSOR);  // supprime le curseur de l'ecran ..
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();
		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);

		if ((bouton==BOUTON_DROIT)&&(valeur_yyreel>5)&&(valeur_yyreel<22)&&(valeur_xxreel<13)&&(valeur_xxreel>4))		{
			creer_ligne(pas);
		}
		if ((valeur_yyreel>5)&&(valeur_yyreel<22)&&(valeur_xxreel<13)&&(valeur_xxreel>4))		{
			gotoxy(1,25);printf(" X %2d Y %2d",valeur_xxreel-4,valeur_yyreel-5);
		}

//		gotoxy(1,1);printf(" X %d | Y %d   ",valeur_xxreel,valeur_yyreel);

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel>6)&&(valeur_yyreel<20)&&(valeur_xxreel>27)&&(valeur_xxreel<67))
		{
			pas=((valeur_xxreel-27)/2+20*(valeur_yyreel-7));
			gotoxy(28,21);color(0,7);
			cprintf("car %03d <=> %c",pas,pas);
			changer[pas]='K';
			cache_souris();
			afficher_code_ascii(pas);
			afficher_liste();
			montre_souris();
		}
		if ((bouton==BOUTON_DROIT)&&(valeur_yyreel>6)&&(valeur_yyreel<20)&&(valeur_xxreel>27)&&(valeur_xxreel<67))
		{
			cache_souris();
			gettext(1, 1, 80, 25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
			pas=((valeur_xxreel-27)/2+20*(valeur_yyreel-7));
			gotoxy(28,21);color(0,7);
			cprintf("car %03d <=> %c",pas,pas);
			changer[pas]='D'; //
//			changer[pas]='X'; // Desactiver!
			afficher_code_ascii(pas);
			afficher_liste();
			cadre_plein(20,7,70,9,SIMPLE,WHITE,BLUE,1);      // dessine le cadre
			gotoxy(23,8);color(YELLOW,BLUE);
			cprintf("Le caractäre dÇsactivÇ pour l'enregistrement");
			delay(500);
			puttext(1,1,80,25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
			afficher_liste();
			montre_souris();
		}

		if ((valeur_yyreel==21)&&(valeur_xxreel==17))	{
			locatext(14,25," utilisez le pour selectionner un caractere superieur     ",BLACK+16*7);
		}

		if ((valeur_yyreel==21)&&(valeur_xxreel==15))	{
			locatext(14,25," utilisez le pour selectionner un caractere inferieure    ",BLACK+16*7);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==22)&&(valeur_xxreel==15))
		{
			if (pas>0) pas--;
			gotoxy(7,22);
			printf("%3d",pas);
			afficher_code_ascii(pas);
			delay(250);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==22)&&(valeur_xxreel==17))
		{
			if (pas<255) pas++;
			gotoxy(7,22);
			printf("%3d",pas);
			afficher_code_ascii(pas);
			delay(250);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==2)&&(valeur_xxreel>2)&&(valeur_xxreel<10))	{
			cache_souris();
			relacher_bsgauche();
			menu_fichier();

		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==2)&&(valeur_xxreel>12)&&(valeur_xxreel<20))	{
			cache_souris();
			relacher_bsgauche();
			menu_copie(pas);
		}

		if (kbhit())
		{	touche=toupper(getch());
//			if (touche==27) choix_menu=1; // Fin du programme
			if (touche=='+')	{
				if (pas<256)	pas++;
				gotoxy(7,22);
				printf("%3d",pas);

				afficher_code_ascii(pas);
			}
			if (touche=='-')	{
				if (pas>0) pas--;
				gotoxy(7,22);
				printf("%3d",pas);
				afficher_code_ascii(pas);
			}
			if (touche=='S')
			{  cache_souris();
				gettext(1, 1, 80, 25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
				cadre_plein(20,7,70,9,SIMPLE,WHITE,BLUE,1);      // dessine le cadre
				gotoxy(23,8);color(YELLOW,BLUE);
				cprintf("Engeristrement de la table >");
				color(11,BLUE);cprintf(" %s",nom_defaut);
				delay(500);
				sauver_table(nom_defaut);
				puttext(1,1,80,25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
				montre_souris();
			}
		 }
		if ((valeur_yyreel>4)&&(valeur_yyreel<21)&&(valeur_xxreel<13)&&(valeur_xxreel>4))
		{  locatext(14,25," Modifiez un caractere avec le bouton gauche de la souris  ",BLACK+16*7);

		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel>5)&&(valeur_yyreel<22)&&(valeur_xxreel<13)&&(valeur_xxreel>4))
		{
			cache_souris();
			if (table[valeur_xxreel-5][valeur_yyreel-6]==0) {
				gotoxy(valeur_xxreel,valeur_yyreel);color(12,1);
				cprintf("€");
				table[valeur_xxreel-5][valeur_yyreel-6]=1;
				delay(200);
			}
			else {
				gotoxy(valeur_xxreel,valeur_yyreel);
				color(1,1);cprintf(" ");
				table[valeur_xxreel-5][valeur_yyreel-6]=0;
				delay(200);
			}
			for (int i=0;i<16;i++)  {
					tab[pas][i]=128*table[0][i]+64*table[1][i]+32*table[2][i]+16*table[3][i]+8*table[4][i]+4*table[5][i]+2*table[6][i]+1*table[7][i];
			}
			for (int b=0;b<16;b++) {
				color(15,1);gotoxy(14,6+b);
				cprintf(" %3d ",tab[pas][b]);
			}
			def(pas);
			montre_souris();
		}

	}
	while (choix_menu==0);
	color(7,0);CLS;
	cache_souris();
	_setcursortype(_NORMALCURSOR);
	printf(" ALES par ZeCrusher !!! \n");
	return (0);
}

void definition_ascii_(byte table[16],int ascii)
{
//	union REGS regs;
	struct REGPACK regpack; //Structure mÇmorisant les valeurs ÇchangÇes avec intr.

	regpack.r_cx=1;
	regpack.r_dx=ascii; //'';
	regpack.r_bx=0x1000;
	regpack.r_ax=0x1100;
	regpack.r_es=FP_SEG((char far *) table); // le segment de adresse longue
	regpack.r_bp=FP_OFF((char far *) table); // valeur de dÇplacement de adresse longue
	intr(0x10,&regpack); // interface avec les interruptions logicielles du 80x86.

}
int charger_table_(char nom_police[80])
{


	FILE *in;
	char buffer[4096],temp;
	int barre,v=0;
	int x,y;
	x=wherex();
	y=wherey();

	cache_souris();

	gettext(1, 1, 80, 25, buffer);

	cadre_plein(23,15,56,17,SIMPLE,WHITE,7,1);      // dessine le cadre
	locatext(25,15," Charger ",0+16*7);

	if ((in = fopen(nom_police, "rb"))== NULL)
	{
		cadre_plein(10,10,51,12,SIMPLE,RED,7,1);      // dessine le cadre
		gotoxy(11,11);color(15,7);cprintf(" Fichier introuvable ou Autre erreur\n");
		getch();
		gotoxy(3,1);
		printf("\n");color(7,0);
		puttext(1, 1, 80, 25, buffer);
		fclose(in);

		return(-1);
	}

	for (int a=0;a<255;a++) {

		if ((barre++)>6) {
			barre=0;
			gotoxy(24+(v++),16);cprintf("∞");
		}

		for (int i=0;i<16;i++)  {
			 tab[a][i]=fgetc(in);
		}
		 changer[a]=fgetc(in);

		 if (changer[a]=='K') { /* Caractere modifier */
			 def(a);
		}
	// Charge les cararcteres de ligne ex-> -A-\n
		 temp=fgetc(in); // '-'
		 temp=fgetc(in); // a
		 temp=fgetc(in); // -
		 temp=fgetc(in); // \n

	}
	puttext(1, 1, 80, 25, buffer);

	fclose(in);
	gotoxy(x,y);

	return(0);
}
int fusionner_table_(char nom_police[80])
{

	FILE *in;
	char tempo[16];
	char buffer[4096],temp;
	int barre,v=0;
	int x,y,precedent=0;
	x=wherex();
	y=wherey();

	cache_souris();

	gettext(1, 1, 80, 25, buffer);

	cadre_plein(23,15,56,17,SIMPLE,WHITE,7,1);      // dessine le cadre
	locatext(25,15," Charger ",0+16*7);

	if ((in = fopen(nom_police, "rb"))== NULL)
	{
		cadre_plein(10,10,51,12,SIMPLE,RED,7,1);      // dessine le cadre
		gotoxy(11,11);color(15,7);cprintf(" Fichier introuvable ou Autre erreur\n");
		getch();
		gotoxy(3,1);
		printf("\n");color(7,0);
		puttext(1, 1, 80, 25, buffer);
		fclose(in);

		return(-1);
	}

	for (int a=0;a<255;a++) {
		if ((barre++)>6) {
			barre=0;
			gotoxy(24+(v++),16);cprintf("∞");
		}

		for (int i=0;i<16;i++)  {
			 //tab[a][i]=fgetc(in);
			   tempo[i]=fgetc(in);
		}
//		 changer[a]=fgetc(in);
		 precedent=fgetc(in);
		 if (changer[a]=='K') { /* Caractere modifier */
			changer[a]=precedent;
			if (changer[a]=='K') { /* Caractere modifier */
				for (int u=0;u<16;u++)  {
					tab[a][u]=tempo[u];
				}
				 def(a);
			}
		}
	// Charge les cararcteres de ligne ex-> -A-\n
		 temp=fgetc(in); // '-'
		 temp=fgetc(in); // a
		 temp=fgetc(in); // -
		 temp=fgetc(in); // \n

	}
	puttext(1, 1, 80, 25, buffer);

	fclose(in);
	gotoxy(x,y);

	return(0);
}

int sauver_table(char nom_police[80])
{
	FILE *out;
	int barre,v=0;
	int x,y;

	char buffer[4096],temp;

	x=wherex();
	y=wherey();

	cache_souris();

	gettext(1, 1, 80, 25, buffer);

	cadre_plein(23,15,56,17,SIMPLE,WHITE,7,1);      // dessine le cadre
	locatext(25,15," Enregistrer ",0+16*7);

	if ((out = fopen(nom_police,"w+b"))== NULL)
	{	fprintf(stderr, "Cannot open output file.\n");
		fclose(out);
	   return 1;
	}

	for (int a=0;a<256;a++)
	{
		if ((barre++)>6) {
			barre=0;
			gotoxy(24+(v++),16);cprintf("∞");
		}
		for (int i=0;i<16;i++) {
			fputc(((int)tab[a][i]),out);
		}
		if (changer[a]=='K')
			fputc('K',out);				//
		if (changer[a]=='D')
			fputc('D',out);				//
		if (changer[a]=='X')
			fputc('X',out);				//

		fputc('-',out);
		fputc(a,out);
		fputc('-',out);
		fputc('\n',out);
	}
	fputs("\n\n",out);
	fputs("1234567890123456 [X|K|D]-C-\n",out);
	fputs("¿> Struct car <Ÿ  ¿ƒ≈ƒŸ ≥ \n",out);
	fputs("  K ou X ou D  ƒƒƒƒƒŸ   ≥ \n",out);
	fputs("Caractäre  ƒƒƒƒƒƒƒƒƒƒƒƒƒŸ \n",out);
	fputs("K pour caractäre modifiÇ \n",out);
	fputs("X pour aucune modification\n",out);
	fputs("D Desactiver pour l'enregitrement\n",out);
	fputs("<< Ales Version 0.1 >>\n",out);
	fputs("Par TSK_ ZeCrusher \n",out);


	fclose(out);

	puttext(1, 1, 80, 25, buffer);
	gotoxy(x,y);
	return (0);
}
void afficher_code_ascii(int numero)
{
	int val=0,ptr=0;
	cache_souris();

	for (int b=0;b<16;b++) {
		color(15,1);gotoxy(14,6+b);
		cprintf(" %3d ",tab[numero][b]);
	}
color(12,1);
		for (int i=0;i<16;i++)	{
		val=tab[numero][i];
		ptr=0;
			gotoxy(5,6+i);
			if ((val-128) >= 0) { cprintf("€");val=val-128;table[ptr][i]=1; ptr++;} else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-64)  >= 0) { cprintf("€");val=val-64;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-32)  >= 0) { cprintf("€");val=val-32;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-16)  >= 0) { cprintf("€");val=val-16;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-8)   >= 0) { cprintf("€");val=val-8 ;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-4)   >= 0) { cprintf("€");val=val-4 ;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-2)   >= 0) { cprintf("€");val=val-2 ;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
			if ((val-1)   >= 0) { cprintf("€");val=val-1 ;table[ptr][i]=1; ptr++; } else { cprintf(" ");table[ptr][i]=0;ptr++; }
		}
	montre_souris();
}
void def(int n)
{
	definition_ascii_(tab[n],n);
}
void init_tab(int num)
{
	for (int l=0;l<16;l++)
		copie[l]=tab[num][l];
	lettre=num;
	for (int g=0;g<16;g++) {
		color(15,1);gotoxy(14,6+g);
		tab[num][g]=0;
		cprintf(" %3d ",tab[num][g]);
	}
	for (int u=0;u<8;u++)
		for (int e=0;e<16;e++)
			table[u][e]=0;
	afficher_code_ascii(num);

}
void menu_copie(int num)
{
	int resultat_menu; // initialise  le resultat de menu_deroulant
	char erreur_ecran[4096];
	gettext(1, 1, 80, 25,erreur_ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
	char *str[]={ " _Annuler","ˇ"," Copier"," _Coller"," _Effacer"};

	cache_souris();
	// 	Parametres de menu_der
	//					 type  cadre<ƒø    coulbar<ø <ø        ⁄coulcadreø     ⁄ƒ texte  ⁄lettre  ⁄ƒ > pointeur du tableau
	resultat_menu=menu_der(13,3,11,6,6,DOUBLE,WHITE,RED,DARKGRAY,LIGHTGRAY,BLACK,LIGHTRED,str);
	bouton=ZERO_BOUTON_APPUYER;

	if ((resultat_menu==1)) {
		if (lettre!=-1) {
			for (int k=0;k<16;k++)  tab[num][k]=copie[k];
			afficher_code_ascii(num);
			def(num);
		}
		  else {
		 lettre=-1;
		}
	}

	if (resultat_menu==3) {
		for (int j=0;j<16;j++)
			identificateur[j]=tab[num][j];
		afficher_code_ascii(num);
		def(num);
		lettre=num;
	}

	if (resultat_menu==5) init_tab(num);


	if (resultat_menu==4) {
		for (int i=0;i<16;i++) {
			 copie[i]=tab[num][i];
			 tab[num][i]=identificateur[i];
		}
		afficher_code_ascii(num);
		def(num);
	}


}
void menu_fichier(void)
{
	int resultat_menu; // initialise  le resultat de menu_deroulant
	int etat=0;
	char fichier[20];
	byte texte_[80]={0};
	char ecran[4096];
	char r[100];
	char *str[]={" _Enregister  "," Enregister _Sous ","ˇ"," _Charger une table","ˇ"," _Fusionner une table","ˇ"," _Compilation .EXE","ˇ"," _Quitter "};

	cache_souris();
	resultat_menu=menu_der(3,3,27,11,11,DOUBLE,WHITE,RED,DARKGRAY,LIGHTGRAY,BLACK,LIGHTRED,str);
	bouton=ZERO_BOUTON_APPUYER;
	delay(200);

	if (resultat_menu==1) {
		cache_souris();
		gettext(1, 1, 80, 25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
		cadre_plein(20,7,70,9,SIMPLE,WHITE,BLUE,1);      // dessine le cadre
		gotoxy(23,8);color(YELLOW,BLUE);
		cprintf("Engeristrement de la table >");
		color(11,BLUE);cprintf(" %s",nom_defaut);
		delay(500);
		sauver_table(nom_defaut);
		puttext(1,1,80,25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
		montre_souris();
	}

	if (resultat_menu==2) {
		gettext(1, 1, 80, 25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
		cadre_plein(20,9,70,11,DOUBLE,WHITE,BLUE,1);      // dessine le cadre
		gotoxy(23,10);color(11,1);
		cprintf("Nom >");
		etat=input(28,10,16,texte_,WHITE+16*1);
		if (etat>0) {
			if (strchr(texte_,'.')==0) {
				strcat(texte_,".als");
			}
			strcpy(nom_defaut,texte_);
		}
		else
		{  if (etat==0) strcpy(nom_defaut,"table.als");
		}

		sauver_table(nom_defaut);
		puttext(1,1,80,25,ecran); 		// Pour ne pas àtre obliger de tout rÇafficher
		montre_souris();
	}

	if (resultat_menu==4) {
		if (found_file(fichier,r,"*.als","Choisir une Police ")==1) {
			charger_table_(fichier);
			strcpy(nom_defaut,fichier);
		}
		afficher_code_ascii(0);
		afficher_liste();
	}

	if (resultat_menu==6) {
		if (found_file(fichier,r,"*.als","Choisir une Police pour la fusion")==1) {
			fusionner_table_(fichier);
			strcpy(nom_defaut,fichier);
		}
		afficher_code_ascii(0);
		afficher_liste();
	}
	if (resultat_menu==8) {
		afficher_code_ascii(0);
		afficher_liste();
	}

	if (resultat_menu==10) {
		color(7,0);clrscr();printf(" ALES par ZeCrusher  \n");
		printf(" Travail en cours sauver sous \terminer.als \n");
		sauver_table("terminer.als");
		exit(0);
	}

}
char afficher_liste(void)
{
	int car=0;

	cache_souris();
/*	window(28,7,68,20);
	color(7,7);
	clrscr();
	window(1,1,80,25);
*/                        //198 199 209 202 197 210 —›ﬁ«……ﬁ
//	locatext(60,20,"",15+16*1);
//						  ZECRUSHER
//	locatext(60,21,"          ",15+16*1);

	for (int y=0;y<13;y++) {
		for (int x=0;x<40;x+=2) {
		if (car>255) return (0);
		if (changer[car]=='K') {
			locatcar(28+x,7+y,car,12+16*7);
		}
		else	{
			if (changer[car]=='D') {
				locatcar(28+x,7+y,car,10+16*7);
			}
			else			{
				locatcar(28+x,7+y,car,0+16*7);
			}
		}
		car++;
		}
	}
	montre_souris();

	return(0);

}
void presentation(void)
{
	cadre_plein(24,7,56,11,0,WHITE,WHITE,1);  // cadre rep
	locatext(24,7,"             A L E S             ",WHITE+16*BLUE);
	locatext(1,24," ALES /charger fichier.als pour charger une police de caractäre                 ",WHITE+16*7);
	locatext(1,25," ALES /modif   fichier.als pour modifier une police de caractäre                  ",WHITE+16*7);

	titre(36,9,YELLOW,1,DARKGRAY,WHITE, " < OK > ",0);
	bouton_xyl(36,9,8); // Gestion du Bouton OK
	titre(36,9,YELLOW,1,DARKGRAY,WHITE, " < OK > ",1);
	cache_souris();
}
int recuperer_police(char *nom_source,char *nom_objet)
{
	FILE *in,*out;
	int i=0;
	char tab[16]; // F1

	if ((in = fopen(nom_source, "rb"))== NULL)	{
		printf("impossible d'ouvrir le fichier %s.\n",nom_source);
	   return 1;
	}
	if ((out = fopen(nom_objet, "wb"))== NULL)	{
		printf("impossible d'ouvrir le fichier %s.\n",nom_objet);
	   return 1;

	}
		for (int x=0;x<16;x++) {
			fputc(0,out);
		}
		fputc('0',out);				//
		fputc('-',out);
		fputc(0,out);
		fputc('-',out);
		fputc('\n',out);

	for (int t=0;t<2992+(16*5);t++)
		fgetc(in);

	for(int k=1;k<255;k++) {
		for (int j=0;j<16;j++) {
			tab[j]=fgetc(in);
		}
		definition_ascii_(tab,k); // LOGO   ”◊Ù !!!

		for (int i=0;i<16;i++) {
			fputc(((int)tab[i]),out);
		}
		fputc('K',out);				//
		fputc('-',out);
		fputc(k,out);
		fputc('-',out);
		fputc('\n',out);
	}
	fclose(in);

 return(0);
}

void creer_ligne(int num)
{
	int choix_menu=0;

	afficher_code_ascii(num);
	gotoxy(valeur_xxreel,valeur_yyreel);
	color(10,1);
	cprintf("€");

	do
	{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();
		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);
		afficher_code_ascii(num);

	}
	while (bouton==BOUTON_DROIT);

}
