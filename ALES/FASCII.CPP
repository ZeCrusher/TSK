/*   FASCII ver 1.00
 Utilitaire en Mode texte 80x25
 DŠrniŠre modif: 30/11/96
 Programmation & conception: ZeCrusher

 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
//*/

#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif
#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif
#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif

typedef unsigned char byte;

void definition_ascii(char table[16],byte ascii);
int  charger_table(char nom_police[80]);

void main(void)
{
  charger_table("c:\\temp\\long.als");

}


void definition_ascii(char table[16],byte ascii)
{  //	union REGS regs;
	struct REGPACK regpack; //Structure m‚morisant les valeurs ‚chang‚es avec intr.

	regpack.r_cx=1;
	regpack.r_dx=ascii; //'ð';
	regpack.r_bx=0x1000;
	regpack.r_ax=0x1100;

	regpack.r_es=FP_SEG((char far *) table); // le segment de adresse longue
	regpack.r_bp=FP_OFF((char far *) table); // valeur de d‚placement de adresse longue

	intr(0x10,&regpack); // interface avec les interruptions logicielles du 80x86.

}

int charger_table(char nom_police[80]) // nom du Fichier … t‚l‚charger Exemple "c:\\temp\\long.als"
{

	FILE *in;
	char tab[17];
	byte changer[256];

	if ((in = fopen(nom_police, "rb"))== NULL)
	{
		cprintf(" Police de caractŠres %s introuvable ",nom_police);
		fclose(in);
		return(-1);
	}

	for (int a=0;a<255;a++) {
		for (int i=0;i<16;i++)  {
			 tab[i]=fgetc(in);
		}
		 changer[a]=fgetc(in);
		 if (changer[a]=='K')
			 definition_ascii(tab,a);

		 for (int j=0;j<4;j++)
			 fgetc(in); // Les caractŠres en plus -a-
	}

	fclose(in);

	return(0);
}
