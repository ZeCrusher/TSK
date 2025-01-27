#define __FEDITEUR

/*   FEDITEUR  version 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: __/06/1998
 DŠrniŠre modif:   /06/98
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction

*/

#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif

#if !defined( __STDLIB_H )
  #include <stdlib.h>
  #define __STDLIB_H
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


 int edit(char *nom_fichier);
void presentation_editeur(void);
void afficher_page(int x,int y,int nbr_ligne);
