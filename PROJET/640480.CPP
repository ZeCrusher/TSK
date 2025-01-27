#include <dos.h>
#include <bios.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define VIDEO  0x10


int charge(char *nom); // Retourne 0 si il y a une erreur
void screen(int mode);
union REGS _r_in,_r_out,_regs;

void main(void)
{
	screen(0x5D);
	charge("d:\\3DS3\\IMAGES\\CHEVY.bmp");
	getch();
}

int charge(char *nom)
{
	REGS in_r,out_r;//reg
	SREGS rs;// registres de segment
	FILE *fichier_bmp;
	int i,t,a;
	char * ptr;
	ptr=(char far *) 0xA0000000L; // Adresse ecran, force le pointeur far
	if ((fichier_bmp= fopen(nom, "rb"))== NULL) {
		cprintf("Le fichier n'existe pas ");
		return(0);
	}
//	fseek(fichier_bmp,1078,0);

	for (a=0;a<=95;a++) {
	 t=a*640;
		for (i=0;i<=639;i++) {
			*(ptr+i+t)=(int)(fgetc(fichier_bmp));// /4);
		}
	}

/*
	in_r.h.ah=0x4f;
	in_r.h.al=0x05; // Numeroe de la fonction du BIOS VESA
	in_r.h.bl=0x0; //
	in_r.h.bh=0x0;
	in_r.x.dx=1;   // Granularit‚
	int86x(0x10,&in_r,&out_r,&rs);
	t=0;
	for (a=0;a<=(95);a++) {
	 t=a*640;
		for (i=0;i<640;i++) {
			*(ptr+i+t)=fgetc(fichier_bmp);
		}
	}

/*
	in_r.h.ah=0x4f;
	in_r.h.al=0x05; // Numeroe de la fonction du BIOS VESA
	in_r.h.bl=0x1; //
	in_r.h.bh=0x01;
	in_r.x.dx=0x0;   // Granularit‚
	int86x(0x10,&in_r,&out_r,&rs);

	for (a=0;a<=(95);a++) {
	 t=a*640;
		for (i=0;i<640;i++) {
			*(ptr+i+t)=fgetc(fichier_bmp);
		}
	}

// }
*/
return (0);
}
void screen(int mode)
{
	_r_in.h.ah=0x00;
	_r_in.h.al=mode;	// Execution de l'interuption logiciel VIDEO
	int86(VIDEO,&_r_in,&_r_out);
}
