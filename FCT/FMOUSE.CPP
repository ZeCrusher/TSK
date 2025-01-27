#define __FMOUSE

/* Programmation & conception: ZeCrusher

	FMOUSE   version 2.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: 01/12/1994
 DŠrniŠre modif: 27/08/98


*/

#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif
#if !defined( __CONIO_H )  // Pour kbhit
#include <conio.h>
#define __CONIO_H
#endif
#if !defined( __CTYPE_H )  // Pour kbhit
#include <ctype.h>
#define __CTYPE_H
#endif

#include <stdio.h>



#define MOUSE_PRESENTE			1	// Definition des constantes pour mouse_present();
#define MOUSE_ABSENTE 			-1	//
#define ZERO_BOUTON			 	0	// definition des bouton de la souris ......
#define ZERO_BOUTON_APPUYER	 	0	// definition des bouton de la souris .....
#define INIT_BOUTON				0
#define BOUTON_DROIT		    2	// Les boutons de la souris sont ici definie pour une souris
#define BOUTON_GAUCHE 			1	// donc seulement deux boutons, le DROIT et le GAUCHE, sont actif
#define BOUTON_GAUCHE_DROIT		3	// pour une souris … trois bouton
#define	INIT_SOURIS				0
#define	MONTRE_SOURIS			1
#define	CACHE_SOURIS			2
#define	ETAT_SOURIS				3
#define MOUSE					0x33

#define INTERFACE_BUS		   1
#define INTERFACE_SERIE		   2
#define INPORT				   3
#define PS2					   4
#define HP 					   5

#define SOFTWARE			   0
#define HARDWARE			   1


void souris(void);
void mouse(int);
void bouton_xyl(int x,int y,int l);
void init_souris(void);      	//
void montre_souris(void);   	//   GERER LE DEPLACEMENT DE LA SOURIS
void cache_souris(void);     	//
void etat_souris(int *posx,int *posy,int *bouton);
void etat_souris(void);
void init_limite_souris(void);
void limite_souris( int x0, int y0, int x1, int y1);
void relacher_bsgauche(void);
void relacher_bsdroit(void);
void dessiner_souris();
void deplacer_en_pixel(void);
void vitesse_souris( int xspeed, int yspeed );
 int type_driver_souris(void);
char irq_souris(void);
 int ev_bouton(int XBouton,int YBouton,int longueur,int Numero,int etat);
 int mouse_presente();
 int bouton_type(int x,int y,int l,char lettre,int numero,int precedent);
 int port_souris(void);

 typedef unsigned char byte;

		// position de la souris sur l'ecran multiple de 8
int	posx,posy,bouton,
	ScrMaxX=0,ScrMaxY=0,
	x0=0,y0=0,x1=80,y1=25,
	valeur_xxreel=0,      // coordonner de la sortie qui est ‚gale a (posx/8)+1   1 a 25
	valeur_yyreel=0;
/*
void main(void)
{
	deplacer_en_pixel();

	int choix=0;

	do
	{
		montre_souris();
		deplacer_en_pixel();

	}
	while(choix==0);

}
//*/
int type_driver_souris(void)
{
	union REGS regs;
	regs.x.ax = 0x0024;

	int86(MOUSE, &regs, &regs);

	if (regs.x.ax == 0xffff)
	{
		return(-1); // Erreur
	}
	else
	{
		printf("\nregs.h.ch >%d",regs.h.ch);
		printf("\nregs.h.cl >%d",regs.h.cl);

	}
		return(0);

}
int bouton_type(int x,int y,int l,char lettre,int numero,int precedent)
{
	char touche=0;

		montre_souris();
		bouton=ZERO_BOUTON_APPUYER; // indique qu'aucun bouton n'est appuyer
		etat_souris();              // Recupere les X et Y + le Bouton
		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);

		if (kbhit())
		{	touche=toupper(getch());
			if (touche==lettre) {
				return(numero);
			}
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==y)&&(valeur_xxreel>x-1)&&(valeur_xxreel<x+l))	{
			return(numero);
		}
		return(precedent);
}

int ev_bouton(int XBouton,int YBouton,int longueur,int Numero,int etat)
{

		if (etat!=0) return (etat);
		montre_souris();
		bouton=ZERO_BOUTON_APPUYER; // indique qu'aucun bouton n'est appuyer
		etat_souris();              // Recupere les X et Y + l'etat du Bouton
		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);

/*		if (kbhit())		{	touche=toupper(getch());			if (touche=='\r') {				choix=1;			}		}
*/
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==YBouton)&&(valeur_xxreel>XBouton-1)&&(valeur_xxreel<(XBouton+longueur)))	{
			return(Numero);
		}
	return(0);

}

void bouton_xyl(int x,int y,int l)
{    int choix=0;
	char touche=0;
	do
	{
		montre_souris();
		bouton=ZERO_BOUTON_APPUYER; // indique qu'aucun bouton n'est appuyer
		etat_souris();              // Recupere les X et Y + le Bouton
		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);

		if (kbhit())
		{	touche=toupper(getch());
			if (touche=='\r') {
				choix=1;
			}
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==y)&&(valeur_xxreel>x-1)&&(valeur_xxreel<x+l))	{
			choix=1;
		}

	}
	while (choix==0);
}

void mouse(int mode)
{
	if (mode==0) init_souris();
	if (mode==1) montre_souris();
	if (mode==2) cache_souris();
	if (mode==3) etat_souris();
}

int mouse_presente(void)
{
	union REGS regs;
	regs.x.ax = 0x0000;
	int86(MOUSE, &regs, &regs);
	if (regs.x.ax == 0xffff)
	{  return(MOUSE_PRESENTE); // La souris est presente
	}
	else
	{   return(MOUSE_ABSENTE);
	}
}
void montre_souris(void)
{
	struct REGPACK reg;

	reg.r_ax=0x01;

	intr(0x33,&reg);

}
void cache_souris(void)
{
		struct REGPACK reg;
		reg.r_ax=0x02;
		intr(0x33,&reg);
}

void etat_souris(void)
{
		union REGS reg,reg_out;
		reg.x.ax=0x03;
		int86(0x33,&reg,&reg_out);
		posx=reg_out.x.cx;
		posy=reg_out.x.dx;
		bouton=reg_out.x.bx;
}
void init_souris(void)
{
		struct REGPACK reg;
		reg.r_ax=0x00;
		intr(0x33,&reg);
}
char irq_souris(void)
{
	union REGS regs;
	regs.x.ax = 0x24;
	int86(0x33, &regs, &regs);
	return(regs.h.cl);
}

int port_souris(void)
{
	union REGS regs;

	regs.x.ax = 0x24;
	int86(0x33, &regs, &regs);
	// 1 -> bus
	// 2 -> Serial
	// 3 -> INport
	// 4 -> PS/2
	// 5 -> HP
	return(regs.h.ch);

}

void limite_souris( int x0, int y0, int x1, int y1)
{
   union REGS regs;
   regs.x.ax = 0x0007;
   regs.x.cx = (unsigned) x0;
   regs.x.dx = (unsigned) x1;
   int86(0x33, &regs, &regs);
   regs.x.ax = 0x0008;
   regs.x.cx = (unsigned) y0;
   regs.x.dx = (unsigned) y1;
   int86(0x33, &regs, &regs);
}
void relacher_bsgauche(void)
{
	 do	 {
		 etat_souris();
	 }
	 while (bouton==BOUTON_GAUCHE);

}
void relacher_bsdroit(void)
{
	 do	 {
		 etat_souris();
	 }
	 while (bouton==BOUTON_DROIT);

}
void dessiner_souris()
{
	union REGS regs;

	regs.x.ax = 0x0A;
	regs.x.bx = SOFTWARE;
	regs.x.cx = 0x77FF;
	regs.x.dx = 0x7700;

	int86(0x33, &regs, &regs);

}
void vitesse_souris( int xspeed, int yspeed )
{
 union REGS regs;/* Registres du processeur pour l'appel d'interrupt. */

	regs.x.ax = 0x000f;          /* Nø fct. "Set mickeys to pixel ratio" */

	regs.x.cx = xspeed;
	regs.x.dx = yspeed;

	int86(0x33,&regs,&regs);                /* Appeler le driver de la souris */
}
void souris(void)
{
 union REGS regs;/* Registres du processeur pour l'appel d'interrupt. */

	regs.x.ax = 0x000a;         /* Nø fct pour "Set text pointer type" */
	regs.x.bx = 0;                           /* Fixer curseur logiciel */
	regs.x.cx = 8;               /* Le mot faible est le masque AND */
	regs.x.dx = 8 >> 16;           /* Le mot fort est le masque XOR */

	int86(0x33,&regs,&regs);                /* Appeler le driver de la souris */

}
void etat_souris(int *posx,int *posy,int *bouton)
{
		union REGS reg,reg_out;
		reg.x.ax=0x03;
		int86(0x33,&reg,&reg_out);
		*posx=reg_out.x.cx;
		*posy=reg_out.x.dx;
		*bouton=reg_out.x.bx;
}
void deplacer_en_pixel(void)
{
		union REGS reg;

		reg.x.ax = 0x07;
		reg.x.cx = 0x00;
		reg.x.dx = 640*8-1;

		int86(0x33,&reg,&reg);

		reg.x.ax = 0x08;
		reg.x.cx = 0x00;
		reg.x.dx = 400*8-1;

		int86(0x33,&reg,&reg);


}
