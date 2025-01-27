// Crypt.CPP

// #pragma hdrfile 	 "c:\tsk\tsk.SYM"  // Changement du fichier entˆtes pr‚compil‚s.
 #pragma -O2		// vitesse
 #pragma -G		// vitesse du code EXE
 #pragma -ml		// Pour les pointeurs - ModŠle de m‚moire voir Option|Compiler|Code_generation|Large(ù)

 #pragma warn -par

#if !defined( __CONIO_H )
 #include <conio.h>
 #define __CONIO_H
#endif
#if !defined( __STDIO_H )
 #include <stdio.h>
 #define __STDIO_H
#endif

 #define  color(a,b)	textcolor(a);textbackground(b)
 #define CLS 								textbackground(BLACK);clrscr()
 #define colorxy(x,y,color,fond) 	gotoxy(x,y);textcolor(color);textbackground(fond)

#if !defined( __FCADRE )
 #include "c:\tsk\fct\fcadre.h"
 #define __FCADRE
#endif
#if !defined( __FMOUSE )
 #include "c:\tsk\fct\fmouse.h"
 #define __FMOUSE
#endif

#if !defined( __FMENU )
 #include "c:\tsk\fct\fmenu.h"
 #define __FMENU
#endif
#if !defined( __FASCII )
 #include "c:\tsk\fct\fascii.h"
 #define __FASCII
#endif

// Test de la configuration de la M‚moire … la compilation .....
 #include "c:\tsk\fct\fmem__.cpp" // Verifie les Erreurs du au modele de m‚moire

//////Fonction externe /////////////////////////////

//////////////////////////  FMOUSE

////////////////////////// Dans FASCII.H
extern void table_ascii(void);
extern void init_ascii();  								// Init la cr‚ation des codes ASCII
extern void definition_ascii(char table[16],char ascii);   //

//////////////////////////  FMENU
extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
////////////////////////// FCADRE
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre

 ////////////////////////////////////
 // Fonctions ///////////////////////
 ////////////////////////////////////
 void presentation(void); 	// C'est le premier cadre du debut (c)
 void deco();  // Presentation du fond


void main(void)
{
	CLS; // Effacement de l'ecran
	fond(0);
	deco(); // Presentation du fond de l 'interface
	presentation();
	deco(); // Presentation du fond de l 'interface


}
void presentation(void)
{
	cache_souris();
	cadre_plein(24,7,56,11,0, 7 , 7  ,1);  // cadre rep
	locatext(24,7,"           C R Y P T O           ",15+16*12);
	titre(36,9,YELLOW,1,DARKGRAY,7, "   Ó×ô   ",0);
	bouton_xyl(36,9,9); // Gestion du Bouton OK
	titre(36,9,YELLOW,1,DARKGRAY,7,"   Ó×ô    ",1);

}
void deco()
{
	char police=-1;

	cadre_plein(12,4,68,22,0,15,15,15);  // cadre rep
	locatext(12,4,"                       C R Y P T O                       ",15+16*12);

	gotoxy(1,1);
	table_ascii();		// F1 , Cr‚ation des nouveau char ASCII
	charger_table("long.als");   // Charge la police de caractere ALES
	locatext(16,6,"",0+16*15);

}
