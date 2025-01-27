#include <dos.h>

#define INTR 0x1C
#define ATTR 0x7900
#ifdef __cplusplus
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif


extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512;

void color_dos();
void interrupt ( *oldhandler)(__CPPARGS);

typedef unsigned int (far *s_arrayptr);

//*
void interrupt handler(__CPPARGS)
{
	color_dos();
	oldhandler();
}
//*/
int main(void)
{

	oldhandler = getvect(INTR);
	setvect(INTR, handler);
	keep(0, (_SS + (_SP/16) - _psp));
	return 0;
}

void color_dos(void)
{
	char far * ptr_ecran;
	register int x=0,y=0;
	int touche,color;
	ptr_ecran=(char far *) 0xB8000000L;
	do
	{
		touche = *(ptr_ecran+y*160+2*x);
		color  = *(ptr_ecran+y*160+2*x+1);
		if ((color==30)&&(touche>64)&&(touche<91))			{ *(ptr_ecran+y*160+2*x+1)=26; }
		if ((color==26)&&(touche==35))						{ *(ptr_ecran+y*160+2*x+1)=18; }
		if ((color==31)&&(touche==123)||(touche==125))		{ *(ptr_ecran+y*160+2*x+1)=28; }
		if ((color==31)&&(touche==40))						{ *(ptr_ecran+y*160+2*x+1)=21; }
		if ((color==31)&&(touche==41))						{ *(ptr_ecran+y*160+2*x+1)=21; }
		if ((color==7)&&(touche>64)&&(touche<91))		 	{ *(ptr_ecran+y*160+2*x+1)=15; }
		if ((color==7)&&(touche>96)&&(touche<123))			{ *(ptr_ecran+y*160+2*x+1)=14; }
		if ((color==7)&&(touche>47)&&(touche<58)) 			{ *(ptr_ecran+y*160+2*x+1)=3;  }
		if ((color==7)&&(touche>130)&&(touche<154))			{ *(ptr_ecran+y*160+2*x+1)=14; }
		if ((color==15)&&(touche>64)&&(touche<91))		 	{ *(ptr_ecran+y*160+2*x+1)=15; }
		if ((color==15)&&(touche>96)&&(touche<123))			{ *(ptr_ecran+y*160+2*x+1)=14; }
		if ((color==15)&&(touche>47)&&(touche<58)) 			{ *(ptr_ecran+y*160+2*x+1)=3;  }
		if ((color==15)&&(touche>130)&&(touche<154))			{ *(ptr_ecran+y*160+2*x+1)=14; }
		x++;
		if (x>160)		{
			y++; x=0;
		}
	}
	while(y<26);

}
