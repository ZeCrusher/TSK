/*   FMODE version 2.00
 R‚alis‚ le: 07/10/1995
 DŠrniŠre modif: __/08/96
 Programmation & conception: Tsakiropoulos Serge
*/

 #include <dos.h>
 #include <conio.h>
 #include <stdio.h>
 #include <ctype.h>
 #include <alloc.h>
 #include <mem.h>

 #include <stdlib.h>

#define VIDEO  0x10

#define PALETTE_MASK         0x3c6
#define PALETTE_REGISTER_RD  0x3c7
#define PALETTE_REGISTER_WR  0x3c8
#define PALETTE_DATA         0x3c9
#define CHAR_WIDTH        	  8
#define CHAR_HEIGHT       	  8
#define SCREEN_WIDTH      	  (unsigned int)320
#define SCREEN_HEIGHT        (unsigned int)200
#define _VRES16COLOR  	  	  MODE_640x480x16	//  640x480 in 16 colors
#define MAX_SPRITE_FRAMES 	  16
#define MAX_X 				  	  50
#define MAX_Y 				  	  50
#define NBR_IMAGE				  10

#define DROITE						1
#define GAUCHE						2
#define BAS   						3
#define HAUT  						0

#define MEMOIRE					0
#define ECRAN 						1

typedef unsigned int word;
typedef unsigned char byte;


// S T R U C T U R E S ///////////////////////////////////////////////////////
union REGS _r_in,_r_out,_regs;

enum modes_ecran { MODE_80x25 = 0x02 ,  MODE_80x43 = 0x25
				  ,MODE_80x30 = 80   ,  MODE_80x60 = 82
				  ,MODE_132x25 = 83  ,  MODE_132x30 = 84
				  ,MODE_132x43 = 89  , MODE_132x60 = 0x5A
				  ,MODE_CGA1= 0x04   ,  MODE_CGA2 = 0x06
				  ,MODE_320x200x256 = 0x13
				  ,MODE_640x480x16  = 0x12
				  ,MODE_640x480x256 = 0x5D
				  };

typedef struct RGB_color_typ  {
		  byte red;    // red   de 0-63
		  byte green;  // green de 0-63
		  byte blue;   // blue  de 0-63
		 } RGB_color, *RGB_color_ptr;

typedef struct PCX_Entete_type {
	char constuct;
	char version;
	char encoding;
	char bits_par_pixel;
	int x,y,width,height;
	int horz_res,vert_res;
	char ega_palette[48];
	char reserved;
	char num_color_planes;
	int bytes_per_line;
	int palette_type;
	char padding[58];
	} pcx_header, *pcx_header_ptr;


typedef struct sprite_type
		{
		  int x,y;
		  int x_old,y_old;
		  int width,height;
		  int anim_clock;
		  int anim_speed;
		  int motion_speed;
		  int motion_clock;
		  char far *frames[MAX_SPRITE_FRAMES];
		  int curr_frame;
		  int num_frames;
		  int state;
		  char far *background;
		  } sprite, *sprite_ptr;

typedef struct PCX_picture_type {
		  pcx_header header;
		  RGB_color palette[256];
		  char far *buffer;
		}  PCX_picture, *pcx_picture_ptr;

void cls256(int PixelValeur);
void screen(int mode); // d‚claration de ma fonction
void line_(int x1, int y1, int x2, int y2, int n );
void swap(int pa, int pb );
int  readpixel(int x,int y);
int  PCX_Load(char *filename,pcx_picture_ptr image,int enable_palette);
void PCX_affiche(char far *pcx);
void palette(int index, RGB_color_ptr color);
void palette(int index, int rd,int gn,int bl);
void get_palette(int index, RGB_color_ptr couleur);
void cls_frag();
void lettre256(int xc,int yc,char c,int color);
void texte256(int x,int y,int couleur, char *chaine);
void affiche_frag_pcx();
void afficher_copier_image(int x,int y,int x1,int y1,int num);
int  copier_image(int x,int y,int x1,int y1,int num);
int  charger_sprite(int x,int y,int x1,int y1,int num);
int  charger_table_sprite(char *fichier_sprite,int hauteur,int largeur,int nbr,int num_sprite);
void afficher_sprite(int x,int y,int num);
void sprite_memoire(int x,int y,int num,char *image);
void atts(void);
void pixel(int x,int y,byte couleur);
void pixel_(int x,int y,byte couleur);
void affiche_cyl_pcx();

	byte far *pcx_data;
	byte far image_sprite[MAX_X][MAX_Y][NBR_IMAGE];
	byte far fond_sauve[MAX_X][MAX_Y][NBR_IMAGE];
	int rouge,vert,bleue;

void main (void)
{
	PCX_picture town;

	screen(MODE_320x200x256);
	cls256(0);
	PCX_Load("c:\\tsk\\sprites\\action1.pcx",(pcx_picture_ptr)&town,1);
	cls_frag();
	charger_sprite(10,10,20,20,1);
	afficher_sprite(10,10,1);
	getch();
	affiche_cyl_pcx();
	cls_frag();
	screen(MODE_80x25);

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

void PCX_affiche(char far *pcx)
{
	char *ptr;
	ptr=(char far *) 0xA0000000L; // Adresse ecran, force le pointeur far
	// Copie un bloc de 64000 octets de pcx vers ptr .
	memcpy(ptr,pcx, 64000L);

}
void _setvideomode(int mode) //  640x480 in 16 colors
{
	screen(mode);
}
void screen(int mode)
{
	_r_in.h.ah=0x00;
	_r_in.h.al=mode;
	int86(VIDEO,&_r_in,&_r_out); 	// Execution de l'interuption logiciel VIDEO
}
void pixel(int x,int y,byte couleur)
{
	char *ptr;
	ptr=(char far *) 0xA0000000L; // Adresse ecran, force le pointeur far

	*(ptr+((y<<8)+(y<<6)+x))=couleur;

}
int readpixel(int x,int y)
{
	char *ptr;
	int color=0;
	ptr=(char far *) 0xA0000000L; // Adresse ecran, force un pointeur far

	color=*(ptr+((y<<8)+(y<<6)+x));

	return(color);
}
void cls256(int PixelValeur)
{
	asm mov	di,0xA000;
	asm mov	es,di;
	asm xor	di,di;
	asm mov	ax,PixelValeur;
	asm mov bx,100;
fmo:
	asm mov	cx,640;
	asm rep	stosw;
	asm dec	bx;
	asm jnz	fmo;

}
void line_(int x1, int y1, int x2, int y2, int n )	/* pour les droites de pente comprise */
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

	if (i<=0)	{
		if (x1 > x2)	/* forcer x1 < x2 */
		{
		  swap( x1, x2 );
		  swap( y1, y2 );
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

		pixel(x,y,n);	/* ‚crire pixel en (x1,y1) */

		for (x=x1+1; x<=x2; x++)	/* … faire de x1+1 … x2 */
		{
			if (d >= 0)	{
				y += yincr;	/* ‚crire pixel A */
				d += Aincr;
			}
			else		/* ‚crire pixel B */
				d += Bincr;
			pixel( x, y, n );
		}
	}
	else
	{
		if (y1 > y2)	/* forcer x1 < x2 */
		{
		  swap( x1, x2 );
		  swap( y1, y2 );
		}
		if (x2 > x1)	/* d‚terminer l'increment pour y */
		  xincr = 1;
		else
		  xincr=-1;

		dx=abs(x2-x1);	/* initialiser les constantes */
		dy=y2-y1;
		d=2*dx-dy;
		Aincr=2*(dx-dy);
		Bincr=2*dx;

		x=x1;	/* valeurs initiales de x et y */
		y=y1;
		pixel(x,y,n);	/* ‚crire pixel en (x1,y1) */

		for (y=y1+1; y<=y2; y++)	/* … faire de x1+1 … x2 */
		{
			if (d >= 0)		{
				x+=xincr;	/* ‚crire pixel A */
				d+=Aincr;
			}
			else		/* ‚crire pixel B */
				d += Bincr;
			pixel( x, y, n );
		}
	}
}
void swap(int pa, int pb )
{
	asm {
		mov AX,pa
		mov BX,pb
		mov pb,AX
		mov pa,BX
	}
}
int PCX_Load(char *filename,pcx_picture_ptr image,int enable_palette)
{
	FILE *fp;
	char far *temp_buffer;
	byte donnee=0;
	int bytes=0;
	long compteur=0;

	// Allocation du tableau pour y stocker l'image

	pcx_data=(byte far *)farmalloc(64000L);
	if (pcx_data==NULL) {
		printf("ERREUR 64 ko non disponible ");
		exit(1);
	}

	if ((fp = fopen(filename, "rb"))== NULL) return (-1);
// Je charge d'abord la palette

	fseek(fp,-768L,SEEK_END); // Emplacement de la palette dans une fichier PCX
	for (int ix=0; ix<256; ix++)	{
		image->palette[ix].red  =(getc(fp)>>2);
		image->palette[ix].green=(getc(fp)>>2);
		image->palette[ix].blue =(getc(fp)>>2);
	}

	if (enable_palette)	{
		for (int index=0; index<256; index++)		{
			palette(index,(RGB_color_ptr)&image->palette[index]);
		}
	}

	fseek(fp,0L,SEEK_SET); // position au d‚but du fichier

	temp_buffer=(char far *)image;
	for (int i=0;i<128;i++) {
		temp_buffer[i] = getc(fp); // Lit les donn‚es sur le fichier PCX
	}

	// Partie de la d‚compression
	do
	{
		donnee=getc(fp);
		if ((donnee>=192)&&(donnee<=255)) {		// Codage RLE ??
			bytes = donnee-192;
			donnee=getc(fp);
			while((bytes--)>0) {
				pcx_data[compteur++]=donnee;
			}
		}
		else	{
				pcx_data[compteur++]=donnee;
		}
	}
	while (compteur<64000);

	return (0);
}

void palette(int index, RGB_color_ptr color)
{
	outp(PALETTE_MASK,0xff);
	outp(PALETTE_REGISTER_WR, index);
	outp(PALETTE_DATA,color->red);
	outp(PALETTE_DATA,color->green);
	outp(PALETTE_DATA,color->blue);

}
void get_palette(int index,RGB_color_ptr couleur)
{
	outp(PALETTE_MASK,0xff);
	outp(PALETTE_REGISTER_RD, index);
	rouge=couleur->red=inp(PALETTE_DATA);
	vert=couleur->green=inp(PALETTE_DATA);
	bleue=couleur->blue=inp(PALETTE_DATA);

}
void palette(int index, int rd,int gn,int bl)
{
	outp(PALETTE_MASK,0xff);
	outp(PALETTE_REGISTER_WR, index);
	outp(PALETTE_DATA,rd);
	outp(PALETTE_DATA,gn);
	outp(PALETTE_DATA,bl);
}
void cls_frag()
{
	palette(0,0,0,0); // Noir c'est Noir !!!!

	for (long index=0; index<=300000L; index++) {
		pixel(rand()%320, rand()%200, 0);
	}
	cls256(0);
}
void affiche_frag_pcx()
{
	// La palette … du ˆtre charger auparavant par PCX_load
	int x,y;

	for (long index=0; index<=330000L;index++)
	{
		y=rand()%200;
		x=rand()%320;
		pixel(x,y,pcx_data[(y<<8)+(y<<6)+x]);
	}


}
void affiche_cyl_pcx()
{
	// La palette … du ˆtre charger auparavant par PCX_load
//int r=0;
	int pas=20,rx=0,ry=0,i=0;

	for (int index=0;index<175;index++) {
		pas=20;
		for (int y=index;y<index+20;y++) {
			for (int x=0;x<320;x++) {	 // affiche une ligne x++
				i=((pas+index+5)<<8)+((pas+index+5)<<6)+x;
				pixel(x,y,pcx_data[i]);
			}
			pas--;
		}
		for (rx=0;rx<320;rx++)	pixel(rx,ry,pcx_data[(ry<<8)+(ry<<6)+rx]);
		ry++;
		delay(2);
	}
	PCX_affiche(pcx_data);
}

void lettre256(int xc,int yc,char c,int color)
{
	int offset,x,y;
	char far *work_char;
	byte bit_mask = 0x80;
	byte far *rom_char_set = (char far *)0xF000FA6EL; // characteres en rom 8x8
	byte far *video_buffer = (char far *)0xA0000000L;


	work_char = rom_char_set + c * CHAR_HEIGHT;
	offset=(yc<<8)+(yc<<6)+xc;

	for (y=0; y<CHAR_HEIGHT; y++)	 {
		bit_mask = 0x80;
		for (x=0; x<CHAR_WIDTH; x++)	{
		  if ((*work_char & bit_mask)) 	video_buffer[offset+x] = color;
		  bit_mask = (bit_mask>>1);
		}
		offset+=SCREEN_WIDTH;
		work_char++;
	}
}
void texte256(int x,int y,int couleur, char *chaine)
{
	for (int i=0; chaine[i]!=0; i++)     {
		lettre256(x+(i<<3),y,chaine[i],couleur);
	  }
}
int copier_image(int x,int y,int x1,int y1,int num)
{
	if (((x1-x)>MAX_X)&&((y1-y)>MAX_Y)) return (-1);

	for (int i=0;i<(x1-x);i++) {
		for (int a=0;a<(y1-y);a++) {
			fond_sauve[i][a][num]=readpixel(i+x,y+a);
		}
	}
	return(0);
}

void afficher_copier_image(int x,int y,int x1,int y1,int num)
{

	for (int i=0;i<(x1-x);i++) {
		for (int a=0;a<(y1-y);a++) {
			pixel(i+x,y+a,(int) fond_sauve[i][a][num]);
		}
	}
}
int charger_sprite(int x,int y,int x1,int y1,int num)
{
	if (((x1-x)>MAX_X)&&((y1-y)>MAX_Y)) {
		return (-1);
	}

	for (int i=0;i<(x1-x);i++) {
		for (int a=0;a<(y1-y);a++) {
			image_sprite[i][a][num]=pcx_data[((y+a)<<8)+((y+a)<<6)+(x+i)];
		}
	}
	return(0);

}
void afficher_sprite(int x,int y,int num)
{

	for (int i=0;i<MAX_X;i++) {
		for (int a=0;a<MAX_Y;a++) {
			if (image_sprite[i][a][num]!=0)
				pixel(x+i,y+a,(int) image_sprite[i][a][num]);
		}
	}

}
int charger_table_sprite(char *fichier_sprite,int hauteur,int largeur,int nbr,int num_sprite)
{
	PCX_picture table_sprite;
	int c=0;

	PCX_Load(fichier_sprite,(pcx_picture_ptr)&table_sprite,0);
	for (int e=0;e<num_sprite;e++)	{
		c+=25;
	}
	for (int s=0;s<nbr;s++) {
		charger_sprite(c+1,1,c+largeur,hauteur,s+num_sprite);
 //		afficher_sprite(1,1,s+num_sprite);
		c+=25;
	}

	return(0);

}
void pixel_(int x,int y,byte couleur)
{
// trace un point en mode graphique VGA 256 320*200
	asm mov ax,y;
	asm mov bx,x;

// Calcul de l' adresse … partir des coordon‚es
	asm	xchg	ah,al;
	asm	add		bx,ax;
	asm	shr		ax,1;
	asm	shr		ax,1;
	asm	add		bx,ax;
	asm	add		bx,0; // D‚part
	asm	mov		ax,0xA000;
	asm	mov		es,ax;

// fin du Calcul de l' adresse … partir des coordon‚es

	asm mov al,couleur;
	asm mov es:[bx],al;
}

void sprite_memoire(int x,int y,int num,char *image)
{



}