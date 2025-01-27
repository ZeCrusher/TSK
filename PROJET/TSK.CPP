/*   FGRAPHTS version 3.00
 Utilitaire en Mode GRAPHIQUE  ( CGA , VGA )
 R‚alis‚ le: __/__/1995
 DŠrniŠre modif: 29/06/95
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
*/
//*/
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "c:\tskÿ\fctÿ\fmouse.cpp"
#include "c:\tskÿ\fctÿ\fmode.cpp"
//*/
#define	OK						0
#define	OK_ON					30
#define	ON						10
#define	OFF                     20
#define	FIN						1
#define	QUITTER					2
#define	AIDE					3
#define VIDEO 					0x10
#define OriginOffset 			0
#define VideoBufferSeg 			0XA000;
#define BMP_SOMBRE				61
#define BMP_CLAIRE				12
#define BMP_NORMAL				0
#define DOUBLE					1
#define SIMPLE					3

void Mode_vga_256(void);
void Mode_vga_16(void);
void debut_traitement(int x,int y);
void fin_traitement(void);
void graphtextxy(int x,int y,int hauteur,int largeur,char texte[],int couleur,int style_caractere,int hori);
void graphtextxy3D(int x,int y,int hauteur,int largeur,char texte[],int ecriture,int fond,int style_caractere,int hori,int decalage);
void graph_cadre(int x,int y,int x1,int y1,int bord,int fond,int style);
void graph_fenetre(int x,int y,int x1,int y1,char texte[100],int bord,int fond,int style);
void graph_bar(int x,int y,int ecriture,char texte[100],int bord,int fond,int style);
void graph_bouton(int x,int y,int ecriture,char texte[100],char c[10],int bord,int fond,int style);
void g_texte(int x,int y,char texte[100],int ecriture,int ecriture_2,int fond);
void g_lettre(int x,int y,char c[5]);
void fbouton(int x,int y,char type);
void charge_bmp(char *nom,int light);
void setclr(char Nr, char R, char G, char B);
void pixelxy256(int ARGx,int ARGy,unsigned char ARGn);
void line(int x1, int y1, int x2, int y2, int n );	/* pour les droites de pente comprise */
void swap(int *pa, int *pb );

void cadre_plein(int x,int y,int x1,int y1,int type_trait,int color,int color_fond,int ombre);      // dessine le cadre
void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25

union REGS r_in,r_out,regs;


//*/
void main(void)
{

 Mode_vga_16();  // sinon init graph ERROR
//	screen
//	graph_cadre(1,1,639,479,1,1,1);
//Mode_vga_256();

//		charge_bmp ne marche que pour des fichiers
//		qui sont au format 320x200x256
// 		plante pour des 640x480x256, ou bien affiche n'importe quoi
//		… l'ecran
//charge_bmp("c:\\10.BMP",BMP_NORMAL);
//ne(0,0,100,100,1);
//montre_souris();
// outtextxy(100,100,"TEST");
//   textcolor(15);    printf("TEST");
//cadre_plein(10,10,20,29,1,15,3,1);      // dessine le cadre
// graph_cadre(10,10,139,179,15,3,1);
 graph_fenetre(1,2,50,50,"12345678901234567890123456789012345678901234567890",GREEN,WHITE,1);
 graph_bar(100,10,BLACK,"TSAKIROPOULOS SERGE TEST DU BOUTON",7,2,1);
 g_lettre(100,100,"Q");

 getch();
 getch();
 getch();
 closegraph();

}
//*/
void cadre_plein(int x,int y,int x1,int y1,int type_trait,int color,int color_fond,int ombre)
{	 graph_cadre((x)*8,y*16,(x1)*8,y1*16,color,color_fond,type_trait);
}
void locatext(char x,char y,char *chaine,char attribut)    // ne fonctionne que pour un mode  80x25
{
	setcolor(attribut);
	bar(x,y,x1,y+20);
	outtextxy((x)*8,y*16,chaine );
}

void locatcar(char x,char y,char chaine,char attribut)
{
	setcolor(attribut);
	gotoxy(x,y);printf("%c",chaine);

}

void charge_bmp(char *nom,int light)
{
	int i,x,y;
	unsigned char car,car2,r,v,b;
	FILE *pfich;
	long int ImaTailX,ImaTailY;//,NbCoulPal;

	pfich=fopen(nom,"rb");

	if (pfich == NULL)	{
		printf("impossible d'ouvrir le fichier pour l'afficher\n");
	}

	fseek(pfich,18,0);
	car=fgetc(pfich);
	car2=fgetc(pfich);
	ImaTailX=(car<<8)+car2;
	fseek(pfich,22,0);
	car=fgetc(pfich);
	car2=fgetc(pfich);
	ImaTailY=(car2<<8)+car;

	fseek(pfich,28,0);
	car=fgetc(pfich);
	printf("%d",car);
	if (car==8)
	{	fseek(pfich,54,0);
		for (i=0;i<=255;i++)	{
			b=fgetc(pfich);
			b=(b/4)+4;//light;//4;
			v=fgetc(pfich);
			v=(v/4)+4;//light;//4;
			r=fgetc(pfich);
			r=(r/4);+4;
			fgetc(pfich);
			setclr(i,r,v,b);
		}
	}
	if (car==4)
	{
		fseek(pfich,54,0);
		for (i=0;i<=15;i++)
		{  	b=fgetc(pfich);
			b=(b/4)+4;//light;
			v=fgetc(pfich);
			v=(v/4)+4;//light;
			r=fgetc(pfich);
			r=(r/4)+4;//light;
			fgetc(pfich);
			setclr(i,r,v,b);
		}
	}

//fseek(pfich,54+3*256,0);

	for (y=(ImaTailY-1);y>=0;y--)
	{
		for (x=0;x<=(ImaTailX-1);x++)
		{	car=fgetc(pfich);
			pixelxy256(x,y,car);
		}
	}
	fclose(pfich); //ferme le fichier

}
void pixelxy256(int ARGx,int ARGy,unsigned char ARGn)
{
// trace un point en mode graphique VGA 256 320*200
	asm mov ax,ARGy;
	asm mov bx,ARGx;

// Calcul de l' adresse … partir des coordon‚es
	asm	xchg	ah,al;
	asm	add		bx,ax;
	asm	shr		ax,1;
	asm	shr		ax,1;
	asm	add		bx,ax;
	asm	add		bx,OriginOffset;
	asm	mov		ax,VideoBufferSeg;
	asm	mov		es,ax;
// fin du Calcul de l' adresse … partir des coordon‚es

	asm mov al,ARGn;
	asm mov es:[bx],al;
}

void setclr(char Nr, char R, char G, char B)
{
	asm mov al,Nr;
	asm mov dx,03c8h;
	asm out dx,al;
	asm mov al,R;
	asm mov dx,03c9h;
	asm out dx,al;
	asm mov al,G;
	asm out dx,al;
	asm mov al,B;
	asm out dx,al;
}

void fbouton(int x,int y,char type)
{
		if (type==OK) 		graph_bouton(x*8,y*16,BLACK,"   OK   ","   O",1,7,1);
		if (type==OK_ON)	graph_bouton(x*8,y*16,BLACK,"   OK   ","   O",7,7,1);
		if (type==FIN) 		graph_bouton(x*8,y*16,BLACK,"   FIN   ","   F",1,7,1);
		if (type==QUITTER) 	graph_bouton(x*8,y*16,BLACK,"   QUITTER  ","   Q",1,7,1);
		if (type==AIDE)		graph_bouton(x*8,y*16,BLACK,"   AIDE   ","   A",1,7,1);
}

void g_lettre(int x,int y,char c[5])
{ 	setcolor(12);
	outtextxy(x,y,c);
}
void g_texte(int x,int y,char texte[100],int ecriture,int ecriture_2,int fond)
{
	setcolor(fond);
	setcolor(ecriture_2);
	outtextxy((x*8)+1,(y*16)+1,texte);
	setcolor(ecriture);
	outtextxy(x*8,y*16,texte);
}
void graph_fenetre(int x,int y,int x1,int y1,char texte[100],int bord,int fond,int style)
{   int aux,xx,longueur_texte=0;
	// calcule pour centrer le texte
	x=x*8;y=y*16;x1=x1*8;y1=y1*16;
	longueur_texte=strlen(texte)*8;
	xx=x+((x1-x)/2);
	aux=xx-(longueur_texte/2);

	setfillstyle(style,fond);
	bar(x,y,x1,y1);
	setcolor(bord);
	rectangle(x,y,x1,y1);
	rectangle(x+1,y+1,x1-1,y1-1);
	setfillstyle(style,bord);
	bar(x,y,x1,y+20);
	setcolor(BLACK);
	outtextxy(aux+2,y+8,texte);
	setcolor(WHITE);
	outtextxy(aux,y+6,texte);
}
void graph_bar(int x,int y,int ecriture,char texte[100],int bord,int fond,int style)
{
	int longueur_chaine,resul_long;

	longueur_chaine=strlen(texte)+2;
	resul_long=8*longueur_chaine;
	graph_cadre(x+3,y+3,(resul_long+x)+3,y+20+3,0,0,1);
	graph_cadre(x,y,(resul_long+x),y+20,bord,fond,style);
	setcolor(ecriture);
	outtextxy(x+8,y+7,texte);

}
void graph_bouton(int x,int y,int ecriture,char texte[100],char c[10],int bord,int fond,int style)
{
	int longueur_chaine,resul_long;

	longueur_chaine=strlen(texte)+2;
	resul_long=8*longueur_chaine;

	graph_cadre(x,y,(resul_long+x),y+19,bord,fond,style);


	setcolor(WHITE);
	line(x,y,(resul_long+x),y);
	line(x,y,x,y+19);

	setcolor(DARKGRAY);
	line(x,y+20,(resul_long+x),y+20);
	line(x,y+19,(resul_long+x),y+19);
	line((resul_long+x),y,(resul_long+x),y+19);
	line((resul_long+x)+1,y,(resul_long+x)+1,y+20);
	setcolor(BLACK);
	rectangle(x-1,y-1,(resul_long+x)+2,y+21);
	setcolor(ecriture);
	 outtextxy(x+8,y+6,texte);
	setcolor(RED);
	outtextxy(x+7,y+5,c);
	setcolor(LIGHTRED);
	outtextxy(x+8,y+6,c);

}

void graph_cadre(int x,int y,int x1,int y1,int bord,int fond,int style)
{
	setcolor(bord);
	setfillstyle(style,fond);
	if (style==0)
				{
				rectangle(x,y,x1,y1);
				}
		else
				{
				bar(x,y,x1,y1);
				rectangle(x,y,x1,y1);
				rectangle(x+1,y+1,x1-1,y1-1);
				}
}
void cadre(int x,int y,int x1,int y1,int bord,int fond,int style)
{
	setcolor(bord);
	setfillstyle(style,fond);
	if (style==0)	{
		rectangle(x*8,y*8,x1*8,y1*8);
		rectangle(x*8+1,y*8+1,x1*8+1,y1*8+1);

	}
	else {
		bar(x*8,y*8,x1*8,y1*8);rectangle(x*8,y*8,x1*8,y1*8);
	}
}

void graphtextxy(int x,int y,int hauteur,int largeur,char texte[],int couleur,int style_caractere,int hori)
{
	 settextstyle(style_caractere, hori, 4);
	 setcolor(couleur);
	 setusercharsize(hauteur,1,largeur,1);
	 outtextxy(x,y,texte);
}
void graphtextxy3D(int x,int y,int hauteur,int largeur,char texte[],int ecriture,int fond,int style_caractere,int hori,int decalage)
{
	 settextstyle(style_caractere, hori, 4);
	 setcolor(ecriture);
	 setusercharsize(hauteur,1,largeur,1);
	 outtextxy(x,y,texte);
	 setcolor(fond);
	 outtextxy(x+decalage,y+decalage,texte);

}
void Mode_vga_16(void)
{   textbackground(BLACK);clrscr();
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "C:\\borlandc\\BGI");
	/* read result of initialization */
	errorcode = graphresult();
	/* an error occurred */
	if (errorcode != grOk)
	{
		printf("Erreur graphics  %s\n", grapherrormsg(errorcode));
		printf("\n\nAide : \n Vous ne possedez pas de carte Graphique ou Erreur");
		printf("\t\n\aTapez sur une touche pour terminer");
		getch();
		exit(1);
	 closegraph();

	}
}
void Mode_vga_256(void)
{
	r_in.h.ah=0x00;  	//
	r_in.h.al=0x13;   	//13
	int86(VIDEO,&r_in,&r_out);

}
void line(int x1, int y1, int x2, int y2, int n )	/* pour les droites de pente comprise */
{
	int	d,dx,dy,i;
	int	Aincr,Bincr,yincr,xincr;
	int	x,y;

	dx = abs(x2-x1);	/* initialiser les constantes */
	dy = abs(y2-y1);
	if (dx==0)
		i=1;
	else
		i=dy/dx;

	if (i<=0)
	{
		if (x1 > x2)	/* forcer x1 < x2 */
		{
		  swap( &x1, &x2 );
		  swap( &y1, &y2 );
		}

		if (y2 > y1)	/* d‚terminer l'increment pour y */
		  yincr = 1;
		else
		  yincr = -1;

		dx = x2 - x1;	/* initialiser les constantes */
		dy = abs( y2-y1 );
		d = 2 * dy - dx;

		Aincr = 2 * (dy - dx);
		Bincr = 2 * dy;

		x = x1;	/* valeurs initiales de x et y */
		y = y1;

		pixelxy256( x, y, n );	/* ‚crire pixel en (x1,y1) */

		for (x=x1+1; x<=x2; x++)	/* … faire de x1+1 … x2 */
		{
			if (d >= 0)
			{
				y += yincr;	/* ‚crire pixel A */
				d += Aincr;
			}
			else		/* ‚crire pixel B */
				d += Bincr;
			pixelxy256( x, y, n );
		}
	}
	else
	{
		if (y1 > y2)	/* forcer x1 < x2 */
		{
		  swap( &x1, &x2 );
		  swap( &y1, &y2 );
		}
		if (x2 > x1)	/* d‚terminer l'increment pour y */
		  xincr = 1;
		else
		  xincr = -1;

		dx = abs(x2-x1);	/* initialiser les constantes */
		dy = y2-y1;

		d = 2 * dx - dy;

		Aincr = 2 * (dx - dy);
		Bincr = 2 * dx;

		x = x1;	/* valeurs initiales de x et y */
		y = y1;

		pixelxy256( x, y, n );	/* ‚crire pixel en (x1,y1) */

		for (y=y1+1; y<=y2; y++)	/* … faire de x1+1 … x2 */
		{
			if (d >= 0)
			{
				x += xincr;	/* ‚crire pixel A */
				d += Aincr;
			}
			else		/* ‚crire pixel B */
				d += Bincr;
			pixelxy256( x, y, n );
		}
	}
}
void swap(int *pa, int *pb )
{
	int	t;

	t = *pa;
	*pa = *pb;
	*pb = t;
}
void debut_traitement(int x,int y)
{
}
void fin_traitement(void)
{
}
