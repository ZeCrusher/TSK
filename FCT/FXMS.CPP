#include <stdio.h>
#include <dos.h>
#include <conio.h>

#define PILOTE_XMS_INSTALLE 	0x80

#define PILOTE_XMS_NON_INSTALLE -1

int xms_presente();
int xms_quantite();

void main(void)
{
	printf(" %d ",xms_presente());
	printf(" %d ",xms_quantite());

}
int xms_presente()
{
	union REGS regs;

	regs.x.ax=0x4300;

	int86(0x2F,&regs,&regs);
	if ( regs.h.al ==PILOTE_XMS_INSTALLE)
	{
		return( PILOTE_XMS_INSTALLE );
	}
	else
	{
		return( PILOTE_XMS_NON_INSTALLE );
	}
}
int xms_quantite()
{
	union REGS regs;

	regs.x.ax=0x4300;
	regs.h.ah=0x8;

	int86(0x2F,&regs,&regs);

	return (regs.x.bx);

}
