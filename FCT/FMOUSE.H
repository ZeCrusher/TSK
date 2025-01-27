#define __FMOUSE

/*   FMOUSE   version 2.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: __/12/1994
 DŠrniŠre modif: 16/01/96
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction

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


#define MOUSE_PRESENTE			1	// Definition des constantes pour mouse_present();
#define MOUSE_ABSENTE 			-1	//
#define ZERO_BOUTON			 	0	// definition des bouton de la souris ......
#define ZERO_BOUTON_APPUYER	 	0	// definition des bouton de la souris .....
#define INIT_BOUTON				0
#define BOUTON_DROIT		    2	// Les boutons de la souris sont ici definie pour une souris
#define BOUTON_GAUCHE 			1	// donc seulement deux boutons, le DROIT et le GAUCHE, sont actif
#define BOUTON_GAUCHE_DROIT		3	// pour une souris … trois bouton
#define INIT_SOURIS				0
#define MONTRE_SOURIS			1
#define CACHE_SOURIS			2
#define ETAT_SOURIS				3
#define MOUSE					0x33
#define INTERFACE_BUS		   1
#define INTERFACE_SERIE			2
#define INPORT						3
#define PS2							4
#define HP 							5

void mouse(int);
void bouton_xyl(int x,int y,int l);
void init_souris(void);      	//
void montre_souris(void);   	//   GERER LE DEPLACEMENT DE LA SOURIS
void cache_souris(void);     	//
void etat_souris(int *posx,int *posy,int *bouton);      	//
void etat_souris(void);
void init_limite_souris(void);
void limite_souris( int x0, int y0, int x1, int y1);
void relacher_bsgauche(void);
void relacher_bsdroit(void);
void dessiner_souris();
void vitesse_souris( int xspeed, int yspeed );
void souris(void);

int ev_bouton(int XBouton,int YBouton,int longueur,int Numero,int etat);
 int mouse_presente();
 int bouton_type(int x,int y,int l,char lettre,int numero,int precedent);
 int port_souris(void);
char irq_souris(void);


