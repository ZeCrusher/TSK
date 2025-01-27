#if !defined( __DOS_H )
 #include <dos.h>
 #define __DOS_H
#endif
#if !defined( __STRING_H )
 #include <string.h>
 #define __STRING_H
#endif

#define REGISTRE_1   0x00 // Armement int‚ruptions (tout inhib‚)
#define REGISTRE_2   0x00
#define REGISTRE_3   0x03
#define REGISTRE_4   0x00
#define REGISTRE_5_5 0x20
#define REGISTRE_5_0 0x01
#define REGISTRE_6 	 0x00
#define REGISTRE_7 	 0x00
#define REGISTRE_8	 0x0C
#define REGISTRE_9	 0x00

#define COM1       0
#define COM2       1
#define OK         0
#define ERREUR     -1

#define COM1       0
#define COM2       1

#define ADR_COM1 0x3F8
#define ADR_COM2 0x2F8

void init_rs(int com_x,int initialise);
int test_rs(int com_x);
int lire_rs(int com_x);
void ecrire_rs(int com_x,char c);
void version(void);

int recevoir_reponse(char *buffer);
void init_com(int com);
char ecrire_com(int com,unsigned char valeur);

union REGS regs;

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

	regs.h.ah=1;
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
void init_com(int com)
{
	//configure le com
	outportb(com+3,REGISTRE_3);
	//D‚finit la vitesse
	//‚criture du poids faible du diviseur
	outportb(com+3,REGISTRE_3+0X80);//bit 7 de LCR pour DLAB=1
	outportb(com+0,REGISTRE_8);
	//‚criture du poids fort du diviseur
	outportb(com+1,REGISTRE_9);
	//Inhibe les int‚ruptions de l'UART
	outportb(com+3,REGISTRE_3);//bit 7 de LCR pour DLAB=0
	outportb(com+4,REGISTRE_4);
	outportb(com+1,REGISTRE_1);
}

char ecrire_com(int com,unsigned char valeur)
{

	if(inportb(com+5)&(REGISTRE_5_5)) // inportb renvoit la valeur lue. <> de NULL
	{
		//ecrire le caractŠre sur le registre 0
		outportb(com+0,valeur);
		return(OK);
	}
	else return(ERREUR);
}
char lire_com(int com)
{
	if (inportb(com+5)&(REGISTRE_5_0))	{		//lecture du com avec le registre 0
		return(inportb(com+0));
	}
	else {
		return(ERREUR);
	}
}

int recevoir_reponse(char *buffer)
{
	char val=0;
	unsigned int i=0,e=0;

	// vide le buffer

	strnset(buffer,0,255);

	val=lire_com(ADR_COM2); // Lit 0x03 , la fin de la trame que j'envoie

	do
	{
		val=lire_com(ADR_COM2);
		if (val!=-1)	{
			buffer[e++]=val;
		}
		i++;
	}
	while((val!='\x03')&&(i<30000)); //10000));



	return(i);

}
