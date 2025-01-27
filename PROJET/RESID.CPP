#include <stdio.h>
#include <dos.h>

#define INTR 0x1C
#define ATTR 0x7900

#ifdef __cplusplus
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif
#define COM2       1
#define DATA_READY 0x100


extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512;

union REGS regs;

void locatext(char x,char y,char *chaine,char attribut);
void interrupt ( *oldhandler)(__CPPARGS);
int test_rs(void);
void init_rs(void);
int lire_rs(void);

int test_ligne=0;
int char_lu;
typedef unsigned int (far *s_arrayptr);

void interrupt handler(__CPPARGS)
{
	static x=0;

	test_ligne=test_rs();
	if (test_ligne) {
		char_lu=lire_rs();
		x++;locatext(1+x,25,(char *)char_lu,7);
		if (x==80) x=0;
	}
}

int main(void)
{
	oldhandler = getvect(INTR);
	setvect(INTR, handler);
	keep(0, (_SS + (_SP/16) - _psp));
	return 0;
}

void locatext(char x,char y,char *chaine,char attribut)
{
	char far * ptr_ecran;
	int cpt=0;
	ptr_ecran=(char far *)0xb8000000L;
	do
	{
		*(ptr_ecran+y*160+2*x+cpt)=*chaine++;
		*(ptr_ecran+y*160+2*x+1+cpt)=attribut;
		cpt=cpt+2;
	}
	while(*chaine!=0);
	delay(1);
}
int test_rs(void)
{
	regs.h.ah=3;
	regs.x.dx=1;  // 0 pour com 1 et 1 pour com 2
	int86(0x14,&regs,&regs);

	return(regs.h.ah & 0x01);
}
void init_rs(void)
{
	regs.h.ah=0;
	regs.x.dx=1;  // 0 pour com 1 et 1 pour com 2
	regs.h.al=0xff;
	int86(0x14,&regs,&regs);

}
int lire_rs(void)
{
	regs.h.ah=2;
	regs.x.dx=0;  // 0 pour com 1 et 1 pour com 2
	int86(0x14,&regs,&regs);

	return(regs.h.al);
}
