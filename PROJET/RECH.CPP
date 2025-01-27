#if !defined( __STDIO_H )
 #include <stdio.h>
 #define __STDIO_H
#endif
#if !defined( __CONIO_H )
 #include <conio.h>
 #define __CONIO_H
#endif
#if !defined( __STRING_H )
 #include <string.h>
 #define __STRING_H
#endif

#if !defined( __FCADRE )
 #include "d:\tsk\fct\fcadre.h"
 #define __FCADRE
#endif
#if !defined( __FMOUSE )
 #include "d:\tsk\fct\fmouse.h"
 #define __FMOUSE
#endif
#if !defined( __FMENU  )
 #include "d:\tsk\fct\fmenu.h"
 #define __FMENU
#endif

 #define colorxy(x,y,color,fond) 	gotoxy(x,y);textcolor(color);textbackground(fond)

extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);

// Dans FCADRE.H -----------------------------------------------------------

extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre

void fenetre_recherche(void);
void rechercher_element(void);
long taille_fichier(FILE *fichier);

   extern unsigned _stklen = 50000U;

char *file;

void main(char argc, char **argv)
{
	if ((strcmp(argv[1],"/E")==0)||(strcmp(argv[1],"/e")==0)) {
		rechercher_element();
	}
	getch();
//	do


}
void fenetre_recherche(void)
{
	fond(0);
	cadre_plein(9,6,65,21,0,11,11,1);	// affiche le cadre de presentation
	locatext(9,6,"                       Recherche                         ",1+16*WHITE); // inscrit le nom du fichier en train d'ˆtre visualiser
	locatext(11,8,"Recherche  [..................................]",BLACK+16*11);

	titre(59,8,12,WHITE,DARKGRAY,11, "  ",0);
	titre(16,10,LIGHTRED,WHITE,DARKGRAY,11, "  *  ",0);
	titre(29,10,BLACK,15,DARKGRAY,11, " Init ",0);
	titre(43,10,BLACK,15,DARKGRAY,11, " Valeur * ",0);

	locatext(30,10,"I",4+16*WHITE);
	locatext(44,10,"V",4+16*WHITE);

	locatext(1,25," Esc pour annuler                   ",BLACK+16*LIGHTGRAY);
	locatext(1,25," Esc",12+16*7);
	locatext(18,13,"[ ] Majuscule differente des minuscules.",0+16*11);
	locatext(18,14,"[ ] ChaŒne en Hexad‚cimal.",0+16*11);
	locatext(18,15,"[ ] Ne pas afficher la recherche.",0+16*11);
	locatext(18,16,"[ ] Sauvegarder sur fichier.",0+16*11);
	titre(18,18,BLACK,WHITE,DARKGRAY,11," Lancer ",0);
	titre(48,18,BLACK,WHITE,DARKGRAY,11," Annuler ",0);
	locatext(49,18,"A",4+16*WHITE);
	locatext(19,18,"L",4+16*WHITE);

}
void rechercher_element()
{
		fenetre_recherche();
}
int recherche(char chaine[80],int presence_jocker,int affi_)
{
	FILE *in;
	byte far *ptr_fichier;
	byte choix=0;
	int readend=0;
	long barre_graph=0,barre_graph_affiche=0;

	byte fichier_[129];

	if ((in = fopen(file, "rt"))== NULL)
	{
		fprintf(stderr, "Cannot open input file.\n");
		return 1;
	}



	long taille=0;

	fseek(in,0,SEEK_SET); // Positionne le pointeur du fichier au debut du tableau

	taille=taille_fichier(in);
	taille=((long) taille/50);

	colorxy(10,24,11,1);
	for (int t=0;t<50;t++) cprintf("þ");

	do
	{
		readend=fread(fichier_,1,128L,in);
		if (readend!=128L)	choix=1;

		barre_graph+=readend;

		if (barre_graph>=taille)
		{
			barre_graph=0;	barre_graph_affiche++;
			gotoxy(9+(barre_graph_affiche*100/50)/2,24);
			color(12,1);cprintf("þ");
			gotoxy(2,24);
			color(15,1);
			cprintf("<%% %3d>",barre_graph_affiche*100/50);
		}

	}
	while(choix==0);
	colorxy(12,24,11,1);
		for (int t2=0;t2<50;t2++) cprintf("þ");

	return (0);
}
long taille_fichier(FILE *fichier)
{
	long curpos, length;

		curpos = ftell(fichier);
		fseek(fichier, 0L, SEEK_END);
		length = ftell(fichier);
		fseek(fichier, curpos, SEEK_SET);

	return (length);

}
