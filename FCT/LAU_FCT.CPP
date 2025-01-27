/* Fonctions utiles */
/* Ecrit par: Laurent MATHEIS */
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <bios.h>

void attente_touche(int x,int y);
void print_xy_c(char texte[],int x,int y,int color);
void cadre_vide(int x,int y,int x1,int y1,int type_trait,int color,int color_fond);      // dessine le cadre
void supcur(void);
void remcur(void);
void atts(void);
void input(int x,int y,char nb_car,char *dest);
void maj(char *dest);

void attente_touche(int x,int y)
{
	if (x<0) x=0;
	if (x>79-26) x=79-26;
	if (y<0) x=0;
	if (y<24) x=24;
	gotoxy(x,y);
	printf("Appuyez sur une touche...");
	getch();
}

void print_xy_c(char texte[],int x,int y,int color)
{
	if (x<0) x=0;
	if (x>79-strlen(texte)) x=79-(strlen(texte));
	if (y<0) x=0;
	if (y>23) x=23;
	gotoxy(x,y);
	textcolor(color);
	cprintf("%s",texte);
}

void cadre_vide(int x,int y,int x1,int y1,int type_trait,int color,int color_fond)      // dessine le cadre
{
	int chg,chd,cbd,cbg;   // caractäre d'angle               ex: €¿»
	int bord_hor_bas,bord_hor_hau; // caractäre horyzontal    ex:Õ ƒ ﬂ
	int bord_v_droite,bord_v_gauche;  // caractäre vertical   ex:›ﬁ ∫ ≥
	int aux;  				// variable auxiliaire

	if (type_trait==0)
	{  //  cadre 0 du Type ¿ƒƒŸ
		bord_v_gauche=179;bord_v_droite=179;bord_hor_hau=196;bord_hor_bas=196;chg=218;chd=191;cbd=217;cbg=192;
	}
	if (type_trait==1)
	{  // cadre 1 du Type »ÕÕº
		bord_v_gauche=186;bord_v_droite=186;bord_hor_hau=205;bord_hor_bas=205;chg=201;chd=187;cbd=188;cbg=200;
	}
	if (type_trait==2)
	{  // cadre 2 du type €ﬂﬂ€
		bord_v_gauche=221;bord_v_droite=222;bord_hor_hau=223;bord_hor_bas=220;chg=219;chd=219;cbd=219;cbg=219;
	}
	if (type_trait==3)
	{   // cadre 3 du type ****
		bord_v_gauche=42;bord_v_droite=42;bord_hor_hau=42;bord_hor_bas=42;chg=42;chd=42;cbd=42;cbg=42;
	}
	// verification des coordonnÇes dans cadre_vide(x,y,x1,y1,color_texte,color_fond);
	if (x<1) x=1;
	if (x>80) x=80;
	if (x1<1) x1=1;
	if (x1>80) x1=80;
	if (y<1) y=1;
	if (y>24) y=24;
	if (y1<1) y1=1;
	if (y1>24) y1=24;
	if (x>x1)
	{
		aux=x1;
		x1=x;
		x=aux;
	}
	if (y>y1)
	{
		aux=y1;
		y1=y;
		y=aux;
	}
if ((x1-x>=2) && (y1-y>=2))
 {
	textbackground(color_fond);
	textcolor(color);
	for (int i=x;i<=x1;i++)
	{
		gotoxy(i,y1);
		cprintf("%c",bord_hor_bas);
		gotoxy(i,y);
		cprintf("%c",bord_hor_hau);
	}
	for (int j=y;j<=y1;j++)
	{
		gotoxy(x,j);
		cprintf("%c",bord_v_gauche);
		gotoxy(x1,j);
		cprintf("%c",bord_v_droite);
	}
	gotoxy(x,y); cprintf("%c",chg);
	gotoxy(x1,y); cprintf("%c",chd);
	gotoxy(x,y1); cprintf("%c",cbg);
	gotoxy(x1,y1); cprintf("%c",cbd);
 }
}

void supcur(void)
{
	_setcursortype(_NOCURSOR);
}

void remcur(void)
{
	_setcursortype(_NORMALCURSOR);
}

void atts(void)
{
	asm	 mov dx,0x3Da
	deb1:
	asm	 in al,dx
	asm	 test al,8
	asm	 jne deb1
	deb2:
	asm	 in al,dx
	asm	 test al,8
	asm	 je deb2
}

void input(int x,int y,char nb_car,char *dest)
{
	char a,ch[250];
	int nb_c=0;
	if (x>78) x=1;
	if (y>24) y=1;
	if (nb_car>78-x) nb_car=78-x;
	remcur();
	gotoxy(x,y);
	cprintf(" "); //pour faire apparaitre le curseur
	do
	{
		gotoxy(x,y);
		a=getch();
		if (a==8)
		while(a==8)
		{
			if (nb_c>0)
			{
				nb_c--;
				x--;
				gotoxy(x,y);
				cprintf(" ");
			}
			gotoxy(x,y);
			a=getch();
		}
		if (nb_c!=nb_car)
		{
			cprintf(&a);
			ch[nb_c]=a;
			nb_c++;
			x++;
		}
	}while(a!=13 & a!=27);
	if (a==13) nb_c--;
	ch[nb_c]='\0';
	if (a==27) strcpy(dest,"\0");

	else strncpy(dest,ch,nb_c+1);
}

void maj(char *dest)
{
	for (int i=1;i<=strlen(dest);i++)
	{
		dest[i-1]=toupper(dest[i-1]);
	}
}