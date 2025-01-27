// Programmation TSK_  Serge
// 26-12-96
// test de la communication d un port

#if !defined( __DOS_H )
 #include <dos.h>
 #define __DOS_H
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "c:\tskÿ\fctÿ\fcadre.cpp"


#define ADR_COM1 0x3F8
#define ADR_COM2 0x2F8

#define REG_1 0x00 // Armement int‚ruptions (tout inhib‚)
#define REG_2 0x00 // je l'ai mis mais il ne sert … rien. (utile qu'en Lecture).
#define REG_3 0x03 // transmition 8 bits; 1 Bit d'arret; Parit‚e 000b; etc...(il y a aussi DLAB)
#define REG_4 0x00 // Controle du Modem et bit 2 pour g‚n‚rer l'int‚ruption.
#define REG_5_5 0x20 // Etat des lignes et bit 5 pour possibilit‚ de placer ou pas un caractŠre
#define REG_5_0 0x01 // Etat des lignes et bit 0 pour savoir si on a recu un carac
#define REG_6 0x00 // Etat Modem (… blanc ici!)
#define REG_7 0x00 // … Blanc ici.
#define REG_8 0x0C // poids faible du diviseur de vitesse (=12=$0C)(pour 9600 Bauds)
#define REG_9 0x00 // poids fort du diviseur de vitesse (=0=$00)(pour 9600 Bauds)
#define COM1       0
#define COM2       1
#define color(x,y)	textcolor(x);textbackground(y)

void init_rs(int com_x,int initialise);
int test_rs(int com_x);
int lire_rs(int com_x);
void ecrire_rs(int com_x,char c);

int lire_com(int com);
void ecrire_com(int com,unsigned char valeur);
void init_com(int com);


void version(void);

	union REGS regs;

//*
void main(char argc,char **argv)
{
	int t=0,i=65,c=0,l=0,f=0;
	int le=0,ce=0;
	int  val_recue=0;
	int com=COM2,cpt=0;
	char touche=0;

	if (argc<2)	{
		clrscr();
			textcolor(15);
			cprintf("\n\rParamŠtre requis manquant\n\r");
			textcolor(7);
			cprintf(" \n\rNULMODEM [COM2 25 broches]\n\r\n\r");
			cprintf(" Brochage : 25 Broches     \n\r\n\r");
			cprintf("   2 ÄÄÄÄÄÄ<3ÄÄÄÄÄ¿/ÄÄÄÄ3>ÄÄÄÄÄÄÄ 2  ³ 2 et 3 Crois‚e \n\r");
			cprintf("   3 ÄÄÄÄÄÄ<2ÄÄÄÄ/ÀÄÄÄÄÄ2>ÄÄÄÄÄÄÄ 3  ³\n\r");
			cprintf("   4 ÄÄ¿                      ÚÄÄ 4  ³\n\r");
			cprintf("   5 ÄÄÙ                      ÀÄÄ 5  ³\n\r");
			cprintf("   7 ÄÄÄÄÄÄÄÄÄÄÄÄ<7>ÄÄÄÄÄÄÄÄÄÄÄÄÄ 7  ³\n\r");
			cprintf("   6 ÄÄ¿                      ÚÄÄ 6  ³\n\r");
			cprintf("   8 ÄÄ´                      ÃÄÄ 8  ³\n\r");
			cprintf("  20 ÄÄÙ                      ÀÄÄ 20 ³\n\r");
			locatext(66,1,"   TSK_ 97   ",14+16*4);
			textcolor(7);
			exit(0);
	}
	version();



	if (strcmp(argv[1],"COM1")==0) {
		com=ADR_COM1; // COM1;
		locatext(32,25,"Connexion sur le port s‚rie <COM1>",8+16*0);
	}
	else {
		com=ADR_COM2;//COM2;
		locatext(32,25,"Connexion sur le port s‚rie <COM2>",8+16*0);
	}
	if (strcmp(argv[1],"com1")==0) {
		com=ADR_COM1; // COM1;
		locatext(32,25,"Connexion sur le port s‚rie <COM1>",8+16*0);
	}
	else {
		com=ADR_COM2;//COM2;
		locatext(32,25,"Connexion sur le port s‚rie <COM2>",8+16*0);
	}
	locatext(32,25,"Connexion sur le port s‚rie <COM2>",8+16*0);

	locatext(1,25,"   TSK_ 97   ",15+16*12);
	init_com(com);
	_setcursortype(_SOLIDCURSOR);

	do
	{
		gotoxy(6+ce,2+le);

		if (kbhit())		{
			touche=getch();
			ecrire_com(com,touche);
			if (touche==13) { le++;ce=0;}
			if (touche==8) {
				if (ce>0)
					ce--;
				touche=13;
			}
			if (ce>67) {
				le++;ce=0;
			}
			if (le>7) {
				le=0;
				cadre_plein(4,1,75,10,0,15,8,1);  // cadre rep
				locatext(8,1," Envoie de messages ",14+16*1);
				locatext(6,1," \7",14+16*1);
			}
			if (touche!=13) {
				_setcursortype(_SOLIDCURSOR);
				locatcar(6+(ce++),2+le,(char)touche,11+16*8);

			}
		}

		t=lire_com(com);
		if (t!=777) {
			if (t==13) {
				l++;c=0;
			}
			if (t==8) {
				if (c>0)
					c--;
			}
			if (c>67) { l++;c=0; }
			if (l>9) {
				cadre_plein(4,12,75,22,0,8,8,1);  // cadre rep
				locatext(4,12,"    Reception messages                                                  ",15+16*12);
				locatext(6,12,"\7",14+16*12);
				l=0;
			}
			if (t!=13) locatcar(6+(c++),13+l,(char)t,15+16*8);
		}
	val_recue=0;
	}
	while (touche!=27);
	color(7,0);
	fond(1);
	clrscr();

}
//*/

int test_rs(int com_x)
{
	union REGS regs;
	regs.h.ah=3;
	regs.x.dx=com_x;  // 0 pour com 1 et 1 pour com 2
	int86(0x14,&regs,&regs);

	return(regs.h.ah & 0x01);
}
void ecrire_rs(int com_x,char c)
{
	union REGS regs;

	regs.h.ah=0x01;
	regs.h.al=c;
	regs.x.dx=com_x;
	int86(0x14,&regs,&regs);

}

void init_rs(int com_x,int initialise)
{
	union REGS regs;

	regs.h.ah=0;
	regs.x.dx=com_x;  // 0 pour com 1 et 1 pour com 2
	regs.h.al=initialise;
	int86(0x14,&regs,&regs);

}
int lire_rs(int com_x)
{
	union REGS regs;

	regs.h.ah=2;
	regs.x.dx=com_x;  // 0 pour com 1 et 1 pour com 2
	int86(0x14,&regs,&regs);

	return(regs.h.al);
}
void version(void)
{
	fond(0);
	cadre_plein(4,1,75,10,0,15,8,1);  // cadre rep
	locatext(8,1," Envoie de messages ",14+16*1);
	locatext(6,1," \7",14+16*1);

	cadre_plein(4,12,75,22,0,8,8,1);  // cadre rep
	locatext(4,12,"    Reception messages                                                  ",15+16*12);
	locatext(6,12,"\7",14+16*12);

}
void init_com(int com)
{
	//configure le com
	outportb(com+3,REG_3);
	//D‚finit la vitesse
	//‚criture du poids faible du diviseur
	outportb(com+3,REG_3+0X80);//bit 7 de LCR pour DLAB=1
	outportb(com+0,REG_8);
	//‚criture du poids fort du diviseur
	outportb(com+1,REG_9);
	//Inhibe les int‚ruptions de l'UART
	outportb(com+3,REG_3);//bit 7 de LCR pour DLAB=0
	outportb(com+4,REG_4);
	outportb(com+1,REG_1);
}

void ecrire_com(int com,unsigned char valeur)
{
	int v;
	//teste le bit 5 du registre 5 pour voir s'il y la place d'envoyer un caractŠre
	v=inportb(com+5)&(REG_5_5);
	if (v!=0)	{
		//ecrire le caractŠre sur le registre 0
		outportb(com+0,valeur);
	}
}

int lire_com(int com)
{
	int v;
	//teste le bit 5 du registre 5 pour voir s'il y la place d'envoyer un caractŠre
	v=inportb(com+5)&(REG_5_0);

	if (v!=0)	{	//lecture du com avec le registre 0
		return(inportb(com+0));
	}
	else return(777);
}
