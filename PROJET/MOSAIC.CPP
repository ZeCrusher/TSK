#include <dos.h>
#include <stdlib.h>
#include <conio.h>

#define INTR 0x1C
#define ATTR 0x7900

#ifdef __cplusplus
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif

extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512;


void interrupt ( *oldhandler)(__CPPARGS);

typedef unsigned int (far *s_arrayptr);

void interrupt handler(__CPPARGS)
{
	static int count;
	static int x0=0,y0=0,x1=0,y1=0;
	static	char b[22],b1[22];
	count++;
	  if (count % 300 == 0)
	  {
		x0=random (80);
		y0=random (25);
		gettext(x0,y0,x0+8,y0+4,b);
		x1=random (80);
		y1=random (25);
		gettext(x1,y1,x1+8,y1+4,b1);
		puttext(x0,y0,x0+8,y0+4,b1);
		puttext(x1,y1,x1+8,y1+4,b);
	   count=0;
	  }

	oldhandler();
}

int main(void)
{

	oldhandler = getvect(INTR);
	setvect(INTR, handler);
	keep(0, (_SS + (_SP/16) - _psp));
	return 0;
}

