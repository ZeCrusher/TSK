/*
 R‚alis‚ le: 01/02/1995
 DŠrniŠre modif: 05/01/97
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme comme fonction
*/

#if !defined( __BIOS_H )
#include <bios.h>
#define __BIOS_H
#endif
#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif
#if !defined( __DIR_H )
#include <dir.h>
#define __DIR_H
#endif
#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif
#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif
#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif

#define _MAX_PATH 	255

unsigned int taille_cluster(void);
char co_pro(void);
int ram_conv(void);
int scan_dir(char *nom_repert,int niveau);
long taille_fichier(FILE *fichier);
long files_=0;
long cluster=0;
long taille_perdu=0;
int compteur;
int incr=0;


void main(void)
{
	clrscr();
	cluster=taille_cluster();
	textcolor(15);textbackground(0);
	scan_dir("c:\\",0);
	incr++;taille_perdu=0;
	cluster=taille_cluster();
	scan_dir("d:\\",0);
	incr++;taille_perdu=0;
	cluster=taille_cluster();
	scan_dir("e:\\",0);
	incr++;taille_perdu=0;
	cluster=taille_cluster();
	scan_dir("f:\\",0);

}
char co_pro(void)
{
	int equip_check = biosequip();

		if (equip_check&0x0002 )  // 0x0002 => CO_PRO
		{
			return(1); // present
		}
		else
		{
			return(-1);
		}
}
int ram_conv(void)
{
   return( biosmemory() );
}
unsigned int taille_cluster(void)
{
	unsigned int SecteursParCluster;
	unsigned int BytesParSecteur;

	/* Obtient la taille des clusters */
	asm {
		mov ah, 36h
		int 21h
		mov SecteursParCluster, ax
		mov BytesParSecteur, cx
	}

	return(SecteursParCluster* BytesParSecteur);
}

int scan_dir(char *nom_repert,int niveau)
{
	int res;
	int dev_res=0;

	struct ffblk info;
	char nom[_MAX_PATH]={0},repert[_MAX_PATH]={0};

	strcpy(repert,nom_repert);

		if (repert[strlen(repert)-1]!='\\')	strcat(repert,"\\");
		strcpy(nom,repert); strcat(nom,"*.*");

		res=findfirst(nom,&info,0xFF);

		while ( res==0 )
		{
			switch(info.ff_attrib)
			{
				case FA_DIREC	:
					if (strcmp(info.ff_name,".") && strcmp(info.ff_name,".."))
					{
//						textcolor(14);
//						gotoxy(3,2);cprintf("repertoire > %s                                   ",info.ff_name);
						strcpy(nom,repert); strcat(nom,info.ff_name);
						scan_dir(nom,niveau+1);
					}
				break;
				case FA_NORMAL:
				case FA_RDONLY:
				case FA_HIDDEN:
				case FA_ARCH:
					files_+=info.ff_fsize;
//					gotoxy(3,5);textcolor(7);cprintf("taille des fichiers > %ld octect      ",files_);
					compteur++;
///					gotoxy(3,6);textcolor(7);cprintf("Nombre de fichiers > %ld             ",compteur);
					dev_res=(int)(info.ff_fsize/cluster);
					if (dev_res==0)	{
						taille_perdu+=cluster-info.ff_fsize;
//						textcolor(11);
//						cprintf("\n\n\rTaille Perdu en Octet  %ld    oct    ",taille_perdu);
//						cprintf("\n\rTaille Perdu en Ko       %ld    ko     ",taille_perdu/1024);
						gotoxy(1,1+incr);
						cprintf("\n\rTaille Perdu en Mega     %d     Mo       ",(taille_perdu/1024)/1000);

					}
					else {
						taille_perdu+=info.ff_fsize-(dev_res*cluster);
//						textcolor(11);
//						cprintf("\n\n\rTaille Perdu en Octet %ld           ",taille_perdu);
//						cprintf("\n\rTaille Perdu en Ko    %ld           ",taille_perdu/1024);
					}
				break ;
			}
		res=findnext(&info);
	}
	return(compteur);
}

long taille_fichier(FILE *fichier)
{
	long curpos, length;

		curpos = ftell(fichier);
		fseek(fichier, 0L, SEEK_END);
		length = ftell(fichier);
		fseek(fichier, curpos, SEEK_SET);

	return (length);

}
