#define __FMENU

/*   FMENU    version 5.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: 03/01/1995
 DŠrniŠre modif: 16/01/96
 Programmation & conception: ZeCrusher
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
*/
// pour tester cette fonction il vous faut remetre les #includes
// et le void main void

#if !defined( __TYPE_CADRE)
 #define SIMPLE		0
 #define DOUBLE		1
 #define BARRE 		2
 #define ETOILE		3
 #define __TYPE_CADRE
#endif

#if !defined( __MATH_H )
#include <math.h>
 #define __MATH_H
#endif


#if !defined( __BIOS_H )
#include <bios.h>
 #define __BIOS_H
#endif

#if !defined( __STRING_H )
#include <string.h>
 #define __STRING_H
#endif
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

#if !defined( __DOS_H )
#include <dos.h>
 #define __DOS_H
#endif

#if !defined(__BOUTON)
 #define ZERO_BOUTON_APPUYER   	0
 #define INIT_BOUTON					0
 #define BOUTON_DROIT		    	2
 #define BOUTON_GAUCHE 				1
 #define __BOUTON
#endif

 #define VIDEO 					0x10
 #define BEEP					printf("\a")
 #define PAUSE   				while(bioskey(1)==0)

 #define color(x,y)				textcolor(x);textbackground(y)
 #define LEN_STR					-1
 #define CLS 						textbackground(BLACK);clrscr();
 #define LONGUEUR_DU_CADRE 	18
 #define SPACE(x)					for(tmp=0;tmp<x;tmp++) cprintf(" ")
 #define PAS_DE_CHOIX			-1
 #define DEPLACABLE				1
 #define NONDEPLACABLE			0
 #define RETURN       			13
 #define ECHAP       			27
 #define VITESSE				10

			// vitesse de d‚filement du menu, attention
									// une vitesse trop ‚leve vous fait sauter
typedef unsigned char byte;
typedef unsigned int  word;

struct menu	{
	int x;
	int y;
	unsigned char largeur;
	unsigned char hauteur;
	unsigned char nbr_barres;
	unsigned char type_de_cadre;
	unsigned char couleur_barre_ecriture;
	unsigned char couleur_barre_fond;
	unsigned char couleur_cadre_ecriture;
	unsigned char couleur_cadre_fond;
	unsigned char couleur_texte;
	unsigned char lettre_surbrillance;
	char *string[40];
};
	struct menu base_menu;
									// des barres du menu

extern void locatcar(char x,char y,char chaine,char attribut);
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);      // dessine le cadre
extern void	montre_souris(void);
extern void	cache_souris(void);
extern void	etat_souris(void);
extern void	init_souris(void);
extern int posx,posy,valeur_xxreel,valeur_yyreel,bouton;
extern void space(int x,int y,int l,int color);
extern void space(int l);
extern void relacher_bsgauche(void);
extern void relacher_bsdroit(void);
extern void fcadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre


void decor_fond();
void decor_fond_(int c1,int c2);
 int Menu(struct base_menu);
 int menu_der(int x,int y,byte largeur,byte hauteur,byte nbr_de_barre,byte type_de_cadre,byte couleur_barre_ecriture,byte couleur_barre_fond,byte couleur_cadre_ecriture,byte couleur_cadre_fond,byte couleur_texte,byte lettre,char *string[40]); // retourne le menu clicker
void ascenceur_vertical_menu_der(int x,int y,byte haut,byte larg,byte nbr_barre,byte position_f,byte dec,float deplace,byte coul_cad_ecrit,byte coul_cad_f);
void titre(int x,int y,int color,int fond,int color2,int fond2,char titre[50],int appuyer);
void bar_menu(int x,int y,char color,char fond,int lettre_surligner,char titres[74]);

 int nbr_de_barre=0,x,centrage=0,saut,espace,numeroe_de_la_barre=0;


int Menu(struct menu base_menu)
{
 return(menu_der(base_menu.x,base_menu.y,base_menu.largeur,base_menu.hauteur,base_menu.nbr_barres,base_menu.type_de_cadre,base_menu.couleur_barre_ecriture,base_menu.couleur_barre_fond,base_menu.couleur_cadre_ecriture,base_menu.couleur_cadre_fond,base_menu.couleur_texte,base_menu.lettre_surbrillance,base_menu.string));
}


void ascenceur_vertical_menu_der(int x,int y,byte haut,byte larg,byte nbr_barre,byte position_f,byte dec,float deplace,byte coul_cad_ecrit,byte coul_cad_f)
{

		if (nbr_barre>haut)		{
			for (int i=0;i<(haut-3);i++)	{
				locatcar(x+larg,y+2+i,'±',coul_cad_ecrit+16*coul_cad_f);
			}
			if ((haut>3)&&(( deplace * position_f )+( deplace * dec ))<haut)	{
				locatcar(x+larg,y+2+((deplace*position_f)+(deplace*dec) ) ,'þ',coul_cad_ecrit+16*coul_cad_f);
			}
		}

}
int menu_der(int x,int y,byte largeur,byte hauteur,byte nbr_de_barre,byte type_de_cadre,byte couleur_barre_ecriture,byte couleur_barre_fond,byte couleur_cadre_ecriture,byte couleur_cadre_fond,byte couleur_texte,byte lettre,char *string[40]) // retourne le menu clicker
{
	int deca=0,val=0,clavier=1,clavier_h=0,taille=0,nbr_lettre_surb=0;
	int choix_menu=0,position_fixe=0; // pointe sur le premier ‚l‚ment
	float deplacement=0;
	char sauve_ecran[4000];
	char lettre_surbrillante[80]={0},texte_sur[80]={0};
	char touchx=0,touchy=0;

	etat_souris();

	touchx=((posx/8)+1 );
	touchy=((posy/8)+1 );

	cache_souris();

	gettext(x,y,x+largeur+2,y+hauteur+1,sauve_ecran);

	for(int pl=0;pl<nbr_de_barre;pl++)
	{
		taille=strlen(string[pl]);
		for(int c=0;c<taille;c++)
		{
			if (string[pl][c]==95) // _ > 95 pour les lettres
			{
				lettre_surbrillante[nbr_lettre_surb]=string[pl][c+1];
				texte_sur[nbr_lettre_surb]=pl;
				nbr_lettre_surb++;
			}
		}
	}

	directvideo=1; // indique de passe directemement par la RAM VIDEO pour cputs

	_setcursortype(_NOCURSOR);

	if (nbr_de_barre>hauteur)	{
		hauteur--;	// V‚rifie si le programmeur ne ce plante pas ....
	}
	if (nbr_de_barre<hauteur)	{
		hauteur=nbr_de_barre;	// V‚rifie si le programmeur ne ce plante pas ....
	}

	// trace le cadre du menu
	if (type_de_cadre>=10) {
		type_de_cadre-=10;
		fcadre_plein(x,y,x+largeur,y+hauteur,type_de_cadre,couleur_cadre_ecriture,couleur_cadre_fond,1);
	}
	else
		cadre_plein(x,y,x+largeur,y+hauteur,type_de_cadre,couleur_cadre_ecriture,couleur_cadre_fond,1);

	if (nbr_de_barre>hauteur)
	{
		for (int i=0;i<(hauteur-1);i++)
		{
			locatcar(x+largeur,y+1+i,'±',couleur_cadre_ecriture+16*couleur_cadre_fond);
		}

		if (hauteur>3)		{
			locatcar(x+largeur,y+2,'þ',couleur_cadre_ecriture+16*couleur_cadre_fond);
		}

		locatcar(x+largeur,y+hauteur-1,'',couleur_cadre_ecriture+16*couleur_cadre_fond);
		locatcar(x+largeur,y+1,'',couleur_cadre_ecriture+16*couleur_cadre_fond);
	}

	for (int p=0;p<hauteur-1;p++)
	{
		if (string[p][0]!='ÿ')
		{ // 			  ' '=255
				bar_menu(x+1,y+1+p,couleur_texte,couleur_cadre_fond,lettre,string[p]);
		}
		else
		{

			if (type_de_cadre==SIMPLE)
			{
				locatcar(x,y+1+p,'Ã',couleur_cadre_ecriture+16*couleur_cadre_fond);
				for (int e=0;e<(largeur-1);e++)
					locatcar(x+e+1,y+1+p,'Ä',couleur_cadre_ecriture+16*couleur_cadre_fond);
				locatcar(x+largeur,y+1+p,'´',couleur_cadre_ecriture+16*couleur_cadre_fond);
			}
			if (type_de_cadre==DOUBLE)
			{
				locatcar(x,y+1+p,'Ì',couleur_cadre_ecriture+16*couleur_cadre_fond);
				for (int e=0;e<(largeur-1);e++)
					locatcar(x+e+1,y+1+p,'Í',couleur_cadre_ecriture+16*couleur_cadre_fond);
				locatcar(x+largeur,y+1+p,'¹',couleur_cadre_ecriture+16*couleur_cadre_fond);

			}
		}
	// 199 Ç Ã
	}

	space(x+1,y+1,largeur-1,couleur_barre_ecriture+16*couleur_barre_fond);
	bar_menu(x+1,y+1,couleur_barre_ecriture,couleur_barre_fond,lettre,string[0]);
	choix_menu=0;

	deplacement=(float) (hauteur-3) / (float) (nbr_de_barre);

///  ****************************************************************
///  ***** c'est ici que commence la boucle de verification ********* 			Tsaki_ (C)
///  ****************************************************************

  do
  {

	montre_souris();
	bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer

	etat_souris();

	valeur_xxreel=((posx/8)+1 );
	valeur_yyreel=((posy/8)+1 );

	if (bioskey(1)!=0)
	{
		clavier=toupper(getch());

		for (int to=0;to<nbr_lettre_surb;to++) {
			if (clavier==lettre_surbrillante[to])
				choix_menu=texte_sur[to]+1;
		}


		if (clavier==RETURN) choix_menu=(clavier_h+deca+1);

		if (clavier==ECHAP)  choix_menu=PAS_DE_CHOIX;

		if (clavier=='\x0') // test une touche HIGHT ' 0 + le code ASCII '
		{	clavier=getch();
			// test des touches fl‚ch‚
			if (clavier==80)     // hauteur -2 correspond … la hauteur - 'Í 'du bas et 'Í" du haut ( Í barre du cadre )
			{
				if (clavier_h<(hauteur-2)) {
					clavier_h++; 	// ici je fais croire que la souris c'est d‚plac‚e
					if ((string[clavier_h][0]=='ÿ')&&(clavier_h<(hauteur-2)) ) clavier_h++;
					position_fixe=val=clavier_h;
				}
				else   	 // empˆche de d‚passer la limite
				{
					if (deca<(nbr_de_barre-hauteur)) deca++;
				}
			}
			if (clavier==72)
			{
				if ((clavier_h>0))
				{
					clavier_h--;
					if (string[clavier_h][0]=='ÿ') clavier_h--;
					position_fixe=val=clavier_h;
				}	// idem ici je fais croire aussi que la souris c'est d‚plac‚e
				else
				{	if (deca>0) deca--;
				}

			}
			if (clavier==77) {
				choix_menu=777;
			}
			if (clavier==75) {
				choix_menu=555;
			}
			// deca pour l'assenceur vertical
			// Contrairement … la souris il faut r‚afficher toute les barres
			// car un saut … la derniere barre par exemple n'est pas possible

		for (int marj=0;marj<(hauteur-1);marj++)			{ // hauteur-1 pour soustraire le cadre du bas si on d‚mare a x+1

			if (string[marj][0]!='ÿ') {
				space(x+1,y+1+marj,largeur-1,couleur_texte+16*couleur_cadre_fond);
				bar_menu(x+1,y+marj+1,couleur_texte,couleur_cadre_fond,lettre,string[marj+deca]);
			}
			else
			{
				if (type_de_cadre==SIMPLE)
				{
					locatcar(x,y+1+marj,'Ã',couleur_cadre_ecriture+16*couleur_cadre_fond);
					for (int e2=0;e2<(largeur-1);e2++)
						locatcar(x+e2+1,y+1+marj,'Ä',couleur_cadre_ecriture+16*couleur_cadre_fond);
					locatcar(x+largeur,y+1+marj,'´',couleur_cadre_ecriture+16*couleur_cadre_fond);
				}
				if (type_de_cadre==DOUBLE)
				{
					locatcar(x,y+1+marj,'Ì',couleur_cadre_ecriture+16*couleur_cadre_fond);
					for (int s=0;s<(largeur-1);s++)
						locatcar(x+s+1,y+1+marj,'Í',couleur_cadre_ecriture+16*couleur_cadre_fond);
						locatcar(x+largeur,y+1+marj,'¹',couleur_cadre_ecriture+16*couleur_cadre_fond);
				}
			}
		}

			space(x+1,y+clavier_h+1,largeur-1,couleur_barre_ecriture+16*couleur_barre_fond);		// SPACE est utilis‚ pour effacer l'enplacement de la derniere barre courante
			bar_menu(x+1,y+clavier_h+1,couleur_barre_ecriture,couleur_barre_fond,lettre,string[clavier_h+deca]);
			ascenceur_vertical_menu_der(x,y,hauteur,largeur,nbr_de_barre,val,deca,deplacement,couleur_cadre_ecriture,couleur_cadre_fond);
		}

	}
	// il faut verifier que le curseur de la souris <=> le curseur clavier
	// cette ligne supprime une erreur

	if (clavier_h!=val) clavier_h=val;

	if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==(y+1))&&(valeur_xxreel==(x+largeur))&&(nbr_de_barre>hauteur))
	{
		if (deca>0) deca--;

		delay(VITESSE);

		for (int s=0;s<hauteur-1;s++)		{ // boucle d'affichage du d‚calement
			space(x+1,y+1+s,largeur-1,couleur_cadre_ecriture+16*couleur_cadre_fond); //
			bar_menu(x+1,y+1+s,couleur_texte,couleur_cadre_fond,lettre,string[s+deca]);
		}
				if ((val>0)&&(deca==0))				{
					val--; 			// ici position_fixe doit ˆtre lui aussi diminu‚e
					position_fixe--;// sinon l'assenceur ne suis pas le curseur donc sinon erreur
					clavier_h=val; //
				}                   // IDEM val++;

		space(x+1,y+1+val,largeur-1,couleur_barre_ecriture+16*couleur_barre_fond);
		bar_menu(x+1,y+1+val,couleur_barre_ecriture,couleur_barre_fond,lettre,string[val+deca]);//s+deca]);
		ascenceur_vertical_menu_der(x,y,hauteur,largeur,nbr_de_barre,val,deca,deplacement,couleur_cadre_ecriture,couleur_cadre_fond);
	}                                                             //   position_fixe, est remplac‚ par val

	if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==(y+hauteur-1))&&(valeur_xxreel==(x+largeur))&&(nbr_de_barre>hauteur))
	{
		if (deca<(nbr_de_barre-hauteur)) { deca++; } // deca pour l'assenceur vertical

		delay(VITESSE);

		for (int s=0;s<hauteur-1;s++) { // boucle d'affichage du d‚calement
			space(x+1,y+1+s,largeur-1,couleur_cadre_ecriture+16*couleur_cadre_fond); //
			bar_menu(x+1,y+1+s,couleur_texte,couleur_cadre_fond,lettre,string[s+deca]);
		}
				if ( (val<hauteur-2) && (deca==(nbr_de_barre-hauteur)) )
				{
					val++; // d‚cale la barre du menu vers le bas apr‚s la but‚e du cadre
					position_fixe++;
					clavier_h=val; // utiliser pour le clavier
				}
			space(x+1,y+1+val,largeur-1,couleur_barre_ecriture+16*couleur_barre_fond); //
			bar_menu(x+1,y+1+val,couleur_barre_ecriture,couleur_barre_fond,lettre,string[val+deca]);//s+deca]);
			ascenceur_vertical_menu_der(x,y,hauteur,largeur,nbr_de_barre,position_fixe,deca,deplacement,couleur_cadre_ecriture,couleur_cadre_fond);
	}

		for (int o=0;o<hauteur-1;o++) // boucle de v‚rification
		{   // v‚rifie l'emplacement actuelle de toute les barres

			if ((position_fixe!=o)&&(valeur_yyreel==(y+o+1))&&(valeur_xxreel<(x+largeur))&&(valeur_xxreel>x)&&(string[o+deca][0]!='ÿ'))
			{	// Replace la couleur de la barre precedente

				cache_souris();	// efface la souris pour eviter le caractere inverser

				space(x+1,y+1+val,largeur-1,couleur_cadre_ecriture+16*couleur_cadre_fond);
				bar_menu(x+1,y+1+val,couleur_texte,couleur_cadre_fond,lettre,string[position_fixe+deca]);
				val=o; // M‚morise l'ancienne position

				position_fixe=o+deca; //stock la position de la barre en cour du menu
				bar_menu(x+1,y+1+o,couleur_cadre_ecriture,couleur_cadre_fond,lettre,string[position_fixe]);

					if ((valeur_yyreel==(y+o+1))&&(valeur_xxreel<(x+largeur))&&(valeur_xxreel>x))
					{
						space(x+1,y+1+o,largeur-1,couleur_barre_ecriture+16*couleur_barre_fond);
						// bar_menu peut ecrire une lettre en surbrillance avec '_'
						bar_menu(x+1,y+1+o,couleur_barre_ecriture,couleur_barre_fond,lettre,string[position_fixe]);
						position_fixe=o;                                             // position_fixe peut ˆtre remplac‚e par val , car val=position_fixe
						ascenceur_vertical_menu_der(x,y,hauteur,largeur,nbr_de_barre,position_fixe,deca,deplacement,couleur_cadre_ecriture,couleur_cadre_fond);
					}
			}
		}
		for (int e=0;e<hauteur-1;e++) 	{	// boucle de v‚rification
			if (((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==(y+e+1))&&(valeur_xxreel<(x+largeur))&&(valeur_xxreel>x))&&(string[valeur_yyreel-y-1][0]!=255)) {
				choix_menu=position_fixe+deca+1; // Le +1 indique qu'il ne peut y avoir de barre nul;
				relacher_bsgauche();
			}
			else {
				if ((bouton==BOUTON_GAUCHE)&&(hauteur==nbr_de_barre)) 	{
					choix_menu=PAS_DE_CHOIX;
				}
			}
		}
	if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==y) && (valeur_xxreel==(x+3)) )
		choix_menu=PAS_DE_CHOIX;
	if ((bouton==BOUTON_DROIT)&&((touchx!=valeur_xxreel)||(touchy!=valeur_yyreel)))
		choix_menu=PAS_DE_CHOIX;
  }
  while(choix_menu==0);
	cache_souris();
	puttext(x, y, x+largeur+2, y+hauteur+1, sauve_ecran);

 return(choix_menu); // Le +1 indique q

}
//*/
void titre(int x,int y,int color,int fond,int color2,int fond2,char titre[50],int appuyer)
{
	char sauve_bouton[100];

	textbackground(fond);textcolor(color);

	cache_souris();

	if (appuyer==0) {

		locatext(x,y,titre,color+16*fond);
		locatcar(x+strlen(titre),y,'Ü',color2+16*fond2);

		for (int i=0;i<(strlen(titre));i++)
			locatcar(x+i+1,y+1,'ß',color2+16*fond2);
	}

	if (appuyer==1) {
		gettext(x, y, x+strlen(titre),y+1,sauve_bouton);
		locatcar(x,y,' ',fond+16*fond2);
		locatext(x+1,y,titre,color+16*fond);
		gotoxy(x+1,y+1);
		textbackground(fond2);
		textcolor(fond2);
		for (int i=0;i<(strlen(titre)+2);i++)	{
			cprintf("Û");
		}
		delay(200);
		puttext(x, y, x+strlen(titre),y+1,sauve_bouton);
	}
	montre_souris();
}
void bar_menu(int x,int y,char color,char fond,int lettre_surligner,char titres[74])
{
	int boucle=0,boucle_texte=0;
	int	longueur_de_chaine;
	longueur_de_chaine=strlen(titres);

	do
	{
		if ((titres[boucle]==95)||(titres[boucle]<16))
		{
			boucle++;
		}
		else
		{
			if ((titres[boucle-1]==95)||(titres[boucle-1]<16))
			{
				if ((titres[boucle-1]==95))
				{
					locatcar(x+boucle_texte,y,titres[boucle],lettre_surligner+16*fond);
				}
				else
				{
					locatcar(x+boucle_texte,y,titres[boucle],((int)titres[boucle-1])+16*fond);
				}
			}
			else
			{
					locatcar(x+boucle_texte,y,titres[boucle],color+16*fond);
			}
			boucle++;
			boucle_texte++;
		}
	}
	while(boucle<longueur_de_chaine);
}
void decor_fond()
{
	CLS;
	_setcursortype(_NOCURSOR);  // supprime le curseur de l'ecran ..
	textcolor(WHITE);textbackground(LIGHTGRAY);
	for(int i1=0;i1<25;i1++) for(int i2=0;i2<5;i2++) { cputs ("²²²²²²²²²²²²²²²²"); }
	textcolor(WHITE);textbackground(BLUE);
	gotoxy(1,24); 	for (int j=0;j<80;j++) cprintf(" ");
	gotoxy(1,1);	for (int i=1;i<81;i++) cprintf(" ");
}
void decor_fond_(int c1,int c2)
{
	CLS;
	_setcursortype(_NOCURSOR);  // supprime le curseur de l'ecran ..
	textcolor(c1);textbackground(c2);
	for(int i1=0;i1<25;i1++) for(int i2=0;i2<5;i2++) { cputs ("ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ"); }
	textcolor(WHITE);textbackground(BLUE);
	gotoxy(1,24); 	for (int j=0;j<80;j++) cprintf(" ");
	gotoxy(1,1);	for (int i=1;i<81;i++) cprintf(" ");
}
