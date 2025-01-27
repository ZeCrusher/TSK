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

void cpu();
void interrupt ( *oldhandler)(__CPPARGS);

typedef unsigned int (far *s_arrayptr);

//*
void interrupt handler(__CPPARGS)
{
	cpu();
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

void cpu(void)
{
	delay(10);
}
