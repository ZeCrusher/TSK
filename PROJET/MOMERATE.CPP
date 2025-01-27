#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "c:\tskÿ\fctÿ\fmode.cpp"
#include "c:\tsk\fct\fgraphts.cpp"
//#include "c:\tskÿ\fctÿ\fmouse.cpp"

#define COPYRIGHT		0
#define EDITEUR_FOND  	1
#define BEEP			printf("\a");
#define CLS_GRPH		cache_souris();setfillstyle(0,0);bar(0,0,640,480);



void presentation(int mode);
void ligne_aide(int reference);
void motif_main(int x,int y);
char cliker_souris(int b1[4],int b2[4],int b3[4],int b4[4]);
void s();

void main(void) //char argc,char **argv)
{
	Mode_vga_16();
	mouse(MONTRE_SOURIS);
	s();
	graph_fenetre(20,20,620,410,"UTILITAIRE DISQUE",BLUE,WHITE,1);
	montre_souris();

	getch();
	getch();
	closegraph();
}

void motif_main(int x,int y)
{
 setcolor(WHITE);
	int poly[100];
	setfillstyle(1,BLACK);

	poly[0]=0+x;	poly[1]=10+y;	poly[2]=0+x;	poly[3]=11+y;
	poly[4]=1+x; 	poly[5]=12+y;	poly[6]=1+x;	poly[7]=13+y;
	poly[8]=3+x;	poly[9]=15+y;	poly[10]=3+x;	poly[11]=16+y;
	poly[12]=7+x;	poly[13]=20+y;	poly[14]=7+x;	poly[15]=21+y;
	poly[16]=15+x;	poly[17]=21+y;	poly[18]=15+x;	poly[19]=18+y;
	poly[20]=16+x;	poly[21]=17+y;	poly[22]=16+x;	poly[23]=15+y;
	poly[24]=17+x;	poly[25]=14+y;	poly[26]=17+x;	poly[27]=4+y;
	poly[28]=16+x;	poly[29]=3+y;	poly[30]=14+x;	poly[31]=3+y;
	poly[32]=14+x;	poly[33]=8+y;	poly[34]=14+x;	poly[35]=2+y;
	poly[36]=13+x;	poly[37]=1+y;	poly[38]=11+x;	poly[39]=1+y;
	poly[40]=11+x;	poly[41]=8+y;	poly[42]=11+x;	poly[43]=1+y;
	poly[44]=10+x;	poly[45]=0+y;	poly[46]=9+x;	poly[47]=0+y;
	poly[48]=8+x;	poly[49]=1+y;	poly[50]=8+x;	poly[51]=8+y;
	poly[52]=8+x;	poly[53]=2+y;	poly[54]=6+x;	poly[55]=2+y;
	poly[56]=5+x;	poly[57]=3+y;	poly[58]=5+x;	poly[59]=12+y;
	poly[60]=5+x;	poly[61]=12+y;	poly[62]=2+x;	poly[63]=9+y;
	poly[64]=1+x;	poly[65]=9+y;	poly[66]=0+x;	poly[67]=10+y;


	fillpoly(33,poly);
	setcolor(DARKGRAY);
	drawpoly(33,poly);

}
void s()
{
	struct SREGS sregs;
	union REGS regs;
		int tab[] = {
						0xFFFF,0xFFFF,0xFFFF,0xFFFF,
						0xFFFF,0xFFFF,0xFFFF,0xFFFF,
						0xFFFF,0xFFFF,0xFFFF,0xFFFF,
						0xFFFF,0xFFFF,0xFFFF,0xFFFF,

						0x8000,0xE000,0xF800,0xFE00,
						0xD800,0x0C00,0x0600,0x0300,
						0x0000,0x0000,0x0000,0x0000,
						0x0000,0x0000,0x0000,0x0000
					};
//	regs.x.ax=0;
//	int86(0x33,&regs,&regs); // Je r‚initilatise la souris
//	getch();
	segread(&sregs); // Lit les registres de segment
	sregs.es=FP_SEG((int far *)tab);
	regs.x.ax=9;
	regs.x.bx=regs.x.cx=0;
	regs.x.dx=FP_OFF((int far *)tab);
	int86x(0x33,&regs,&regs,&sregs); // Je r‚initilatise la souris
//getch();

}
