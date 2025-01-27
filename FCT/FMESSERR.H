/*   FMESSERR   version 2.00
 Utilitaire en Mode texte 80x25
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
#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif

typedef unsigned char byte;

extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
extern void cache_souris();
extern void montre_souris();
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern int ev_bouton(int XBouton,int YBouton,int longueur,int Numero,int etat);
extern void bouton_xyl(int x,int y,int l);

int  message_err(int type);
