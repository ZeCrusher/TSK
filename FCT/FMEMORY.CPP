#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>


struct XMS_block {
	unsigned EMB_Num;
		struct {
			union {
			unsigned long depl;
			char far *adr;
			} depl_ou_ard;
		} source;
		struct {
			unsigned EMB_Num;
			union {
				unsigned long depl;
				char far *adr;
			} depl_ou_ard;
		} dest;
};

int presence_xsm(void);
int _loadds XMS_Access(unsigned func,unsigned *ax,unsigned *bx,unsigned *dx,struct XMS_Bloc far *adr_bloc);


void main (void)
{


}
int presence_xsm(void)
{
	union REGS regs;
	struct SREGS sregs;

	regs.x.ax=0x4300;
	int86(0x2F,&regs,&regs);
	if (regs.h.al != 0x80)	{
		return(-1);
	}
	return(0);
}
int _loadds XMS_Access(unsigned func,unsigned *ax,unsigned *bx,unsigned *dx,struct XMS_Bloc far *adr_bloc)
{
	union REGS regs;
	struct SREGS sregs;
	static void (far *XMS_adr)(void);
	char far *pf;

	if (XMS_adr==NULL)
	{
		regs.x.ax=0x4310;
		int86x(0x2F,&regs,&regs,&sregs);
		XMS_adr=(void(far*)()) MK_FP(sregs.es,regs.x.bx); //MK_FP cr‚e un pointeur long
	}
	*ax=(*ax&0xff)|(func<<8);

	_SI=FP_OFF(adr_bloc);
	_BX=*bx;
	_DX=*dx;
	_AX=*ax;
	XMS_adr();
	*ax=_AX;
	*bx=_BX;
	*dx=_DX;
	return (*ax);
}