#define __FMENU
/*   FMENU version 5.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: 03/01/1995
 DŠrniŠre modif: 23/08/95
 Programmation & conception: Tsakiropoulos Serge
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


#if !defined( __CTYPE_H )
#include <ctype.h>
#define __CTYPE_H
#endif

#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif

#if !defined(__BOUTON)
#define ZERO_BOUTON_APPUYER	 	0
#define INIT_BOUTON				0
#define BOUTON_DROIT		    2
#define BOUTON_GAUCHE 			1
#define __BOUTON
#endif

typedef unsigned char byte;


#define SPACE(x)				for(tmp=0;tmp<x;tmp++) cprintf(" ")
#define VIDEO 					0x10
#define BEEP					printf("\a")
#define PAUSE   				while(bioskey(1)==0)


 #define color(x,y)			textcolor(x);textbackground(y)
 #define LEN_STR				-1
// #define CLS 					textbackground(BLACK);clrscr()
 #define LONGUEUR_DU_CADRE 	18
 #define SPACE(x)				for(tmp=0;tmp<x;tmp++) cprintf(" ")
 #define PAS_DE_CHOIX		-1
 #define DEPLACABLE			1
 #define NONDEPLACABLE		0
 #define RETURN       		13
 #define ECHAP       		27
 #define VITESSE				10 	// vitesse de d‚filement du menu, attention
									// une vitesse trop ‚leve vous fait sauter
									// des barres du menu

extern void locatcar(char x,char y,char chaine,char attribut);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);
extern void	montre_souris(void);
extern void	cache_souris(void);
extern void	etat_souris(void);
extern void	init_souris(void);
extern  int posx,posy,valeur_xxreel,valeur_yyreel,bouton;

int menu_der(int x,int y,byte largeur,byte hauteur,byte nbr_de_barre,byte type_de_cadre,byte couleur_barre_ecriture,byte couleur_barre_fond,byte couleur_cadre_ecriture,byte couleur_cadre_fond,byte couleur_texte,byte lettre,char *string[40]); // retourne le menu clicker
void ascenceur_vertical_menu_der(int x,int y,int haut,int larg,int nbr_barre,int position_f,int dec,float deplace,int coul_cad_ecrit,int coul_cad_f);
void menu(int nbr_de_barre,char texte_1[30],char texte_2[30],char texte_3[30],char texte_4[30],char couleur_texte,char couleur_fond,char couleur_ombre_fond);
int gerer_menu(int nbr_de_barre,char texte_1[30], char texte_2[30], char texte_3[30], char texte_4[30], char aide_texte_1[80], char aide_texte_2[80], char aide_texte_3[80], char aide_texte_4[80], char couleur_texte, char couleur_fond, char couleur_ombre_fond);
void titre_menu(char titre[30]);
void titre(int x,int y,int color,int fond,int color2,int fond2,char titre[50],int appuyer);
void bar_menu(int x,int y,char color,char fond,int lettre_surligner,char titre[74]);
 int boite_a_bouton(int x,int y,int haut,int larg,int c1,int c2);
 int menu_barre();
void decor_fond();
void decor_fond_(int c1,int c2);

//int nbr_de_barre=0,x,centrage=0,saut,espace,numeroe_de_la_barre=0;

