/*   FASCII ver 1.00
 Utilitaire en Mode texte 80x25
 DŠrniŠre modif: 30/11/2003
 Programmation & conception: ZeCrusher
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
#define color(x,y)	textcolor(x);textbackground(y)

typedef unsigned char byte;



void definition_ascii(char table[16],byte ascii);
void init_ascii();
void table_ascii(void);
int  charger_table(char nom_police[80]);
void acces_police(void);
 int recuperer_police(char *nom_source,char *nom_objet);
void change_palette_texte(int n,char color);

/*
void main(void)
{
  charger_table("c:\\temp\\squawk.als");

}
 */
void change_palette_texte(int n,char color)
{

	char palette[17]={0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0};
	struct REGPACK regpack; //Structure m‚morisant les valeurs ‚chang‚es avec intr.

	palette[n]=color;

	regpack.r_ax=0x1002;
	regpack.r_es=FP_SEG((char far *) palette); // le segment de adresse longue
	regpack.r_dx=FP_OFF((char far *) palette); // valeur de d‚placement de adresse longue

	intr(0x10,&regpack); // interface avec les interruptions logicielles du 80x86.

}

int recuperer_police(char *nom_source,char *nom_objet)
{
	FILE *in,*out;
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
		definition_ascii(tab,k); // LOGO   Ó×ô !!!

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
	fclose(out);

	return(0);
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
void init_ascii()
{
	union REGS regs;
	char table[16];
	struct REGPACK regpack; //Structure m‚morisant les valeurs ‚chang‚es avec intr.

	regpack.r_cx=1;
	regpack.r_dx='ÿ'; //'ð';
	regpack.r_bx=0x1000;
	regpack.r_ax=0x1100;
	regpack.r_es=FP_SEG((char far *) table); // le segment de adresse longue
	regpack.r_bp=FP_OFF((char far *) table); // valeur de d‚placement de adresse longue
	intr(0x10,&regpack); // interface avec les interruptions logicielles du 80x86.
	regs.h.ah=0;
	regs.h.al=0;
	int86(0x10,&regs,&regs);
}


void table_ascii(void)
{
	char table[16]="\0ø€€ð€€€\x4\xC\x4\x4\x4\xE\0\0"; // F1
	char table1[16]={0,64+32+16+15,64,64,64,64,64,64,64,64,64,127,127,127,127,0};
	char table2[16]={0,255,32+4,32+4,32+4,32+4+16+8,0,16+8,32+4+16+8,16+8,0,0,0,0,255,0};
	char table3[16]={0,128+32+64+16+8+4+2,2,2,2,2,2,2,2,2,2,2,2,2,128+32+64+16+8+4+2,0};
	char table4[16]={0,255,128,128+32+16+8+4+2,128,128+16+8+2,128,128+16+32+8+1,128,128+32+1+2,128,128+16+8+4,128,128,255,0};
	char table5[16]={0,255,1,1,1,1+128+64+32+8,1,1+4+8+16,1,1+64+32+16+8,1,1+16+8+128,1,1,255,0};
	char table6[16]={0,255,128,128,255,128,128,128,128,128,128,128,128,128,255,0};
	char table7[16]={0,255,1,1,255,1,1,1,1,1,1,1,1,1,255,0};
	char table8[16]={0,255,128,128+32+8+2+1,128+32+8+2,128+32+16+8+2,128+32+8+2,128+32+8+2+1,128,128+32+8+2+1,128,128,128+32+8+2+1,128,255,0};
	char table9[16]={0,255,0,0,128,128,128,0,0,255,0,0,255,0,255,0};
	char table10[16]={0,255,1,1,1,1,1,1,1,1,1,1,1,1,255,0};
	char table16[16]={0,16+8+4+2+1+128,16+1+128,16+1+128,128+64+32+16+1,0,16+8+4+2+1+128,16+1+128,16+1+128,128+64+32+16+1,0,128+64+32+1,16+1+128,16+1+128,128+16+1+2+4+8,0};

	char tableVg[16]={224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224};
	char tableVd[16]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

	char tableBgh[16]={255,255,224,224,224,224,224,224,224,224,224,224,224,224,224,224};
	char tableBdh[16]={255,255,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

	char tableThh[16]={255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char tableThb[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255};

	char tableBgb[16]={224,224,224,224,224,224,224,224,224,224,224,224,224,224,255,255};
	char tableBdb[16]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,255,255};

	char T[16]={0,0,15,255,249,1,3,3,3,3,7,7,6,0,0,0};
	char S[16]={0,63,254,224,0,30,126,96,56,14,6,6,6,198,252,248};
	char K[16]={0,217,0,2,198,204,216,240,248,236,230,227,195,129,128,0};

	char fond[16]={255,255,255,255,254,249,230,25,102,153,102,153,103,159,127,255};

	definition_ascii(T,211); // LOGO   Ó×ô !!!
	definition_ascii(S,215); // Ñ
	definition_ascii(K,244); // Ò

	definition_ascii(table,240); // Le code 240 est REDESSINER !!!
	definition_ascii(table1,209); // Ñ
	definition_ascii(table2,210); // Ò
	definition_ascii(table3,250); // ú
	definition_ascii(table4,212); // Ô Logo fichier
	definition_ascii(table5,253); // ý
	definition_ascii(table6,214); // Ö Logo Executable
	definition_ascii(table7,252); // ü

	definition_ascii(table8,207); //  Ï	 ÏÐµ
	definition_ascii(table9,208); //   Ð
	definition_ascii(table10,181); //  µ
	definition_ascii(table16,255); //  ÿ

	definition_ascii(tableVg,221);
	definition_ascii(tableVd,222);

	definition_ascii(tableBgh,206);
	definition_ascii(tableBdh,197);

//	´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎ ÏÐ ÑÒú Ôý Öü µÙÚÛÜÝÞß

	definition_ascii(tableThh,198);
	definition_ascii(tableThb,199);

	definition_ascii(tableBgb,204);
	definition_ascii(tableBdb,202);
								// ÕÕÕ
	definition_ascii(fond,213); // ÕÕÕ
								// ÕÕÕ
	// ÎÆÆÅ    206 198 197
	// Ý  Þ    221     222
	// ÌÇÇÊ    204 199 202
}
//ÏÐµ  ¿À·¸¹º»´¼ÆÆÍ
int charger_table(char nom_police[80])
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

void acces_police(void)
{
	outport(0x3C4,0x0100);
	outport(0x3C4,0x0402);
	outport(0x3C4,0x0704);
	outport(0x3C4,0x0300);
	outport(0x3CE,0x0204);
	outport(0x3CE,0x0005);
	outport(0x3CE,0x0406);
}


