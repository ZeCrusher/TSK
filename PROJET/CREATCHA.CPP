#include <dos.h>
#include <bios.h>
#include <stdio.h>
#include <conio.h>


void main(void)
{
	union REGS regs;
	struct REGPACK regpack;
	char buf[130],o,a,u;     //  €‹›
	unsigned char table[16]={0,255,128,128+32+8+2+1,128+32+8+2,128+32+16+8+2,128+32+8+2,128+32+8+2+1,128,128+32+8+2+1,128,128,128+32+8+2+1,128,255,0};
   unsigned char table2[16]={0,255,0,0,128,128,128,0,0,255,0,0,255,0,255,0};
   unsigned char table3[16]={0,255,1,1,1,1,1,1,1,1,1,1,1,1,255,0};

	regpack.r_cx=1;
	regpack.r_dx='€';
	regpack.r_bx=0x1000;regpack.r_ax=0x1100;
	regpack.r_es=FP_SEG((char far *) table);
	regpack.r_bp=FP_OFF((char far *) table);
	intr(0x10,&regpack);

	regpack.r_cx=1;
	regpack.r_dx='‹';
	regpack.r_bx=0x1000;
	regpack.r_ax=0x1100;
	regpack.r_es=FP_SEG((char far *) table2);
	regpack.r_bp=FP_OFF((char far *) table2);
	intr(0x10,&regpack);
	regpack.r_cx=1;
	regpack.r_dx='›';
	regpack.r_bx=0x1000;
	regpack.r_ax=0x1100;
	regpack.r_es=FP_SEG((char far *) table3);
	regpack.r_bp=FP_OFF((char far *) table3);
	intr(0x10,&regpack);
	printf("—”");

}