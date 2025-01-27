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
