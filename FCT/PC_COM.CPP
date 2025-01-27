#include <bios.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

#define COM1		 0
#define COM2		 1
#define DATA_READY 0x100
#define TRUE       1
#define FALSE      0

//#define SETTINGS ( 0x80 | 0x08 | 0x00 | 0x02)
#define SETTINGS  (_COM_9600 | _COM_ODDPARITY | _COM_STOP1 | _COM_CHR8)

int main(char argc, char **argv)
{
   int in, out, status, DONE = FALSE;
	int com=COM2;
	int x=0,y=0;
	int x1=0,y1=0;
	clrscr();
	if (strcmp(argv[1],"COM1")==0) {
		com=COM1;
	}
	else {
		gotoxy(1,25);
		printf(" Le port s‚rie COM2 est le port de communication par defaut \n");
		com=COM2;
		getch();
	}
	gotoxy(1,1);
	bioscom(0, SETTINGS, com);
	textcolor(15);
	cprintf("Test de communication de Pc … Pc [ ESC pour quitter ]\n\r");
	cprintf("Envoyer Message -------------------------------------------------------------\n\r");
	gotoxy(1,14);
	cprintf("Recevoir Message ------------------------------------------------------------\n\r");

	while (!DONE)
   {
	  status = bioscom(3, 0, com);

	  if (status & DATA_READY)

		 if ((out = bioscom(2, 0, ((com)&0x7F)) != 0))
		 {
			x1++;
			if (x1>80) { x1=0;
				y1++;
				if (y1>9) { y1=0;
					window(1,15,80,25);clrscr();window(1,1,80,25);
				}
			}
			if (out == 'ý')
			{  	window(1,15,80,25);clrscr();window(1,1,80,25);
					x=0;y=0;
			}
			else {
				textcolor(11);
				gotoxy(1+x1,15+y1);
				cprintf("%c",out);
			}
		 }
		 if (kbhit())
		 {
			if ((in = getch()) == '\x1B')
			{
				DONE = TRUE;
			}
			if (in=='\r')
			{   if (y<9) {
					y++;x=0;
				 }
				 if (y==9)  { y=0;
					window(1,3,80,13);clrscr();window(1,1,80,25);
				 }
			}

			if (in == 'ý')
			{		window(1,3,80,13);clrscr();window(1,1,80,25);
					x=0;y=0;
			}
			bioscom(_COM_SEND, in, com);
			textcolor(12);
			gotoxy(1+x,3+y);
			cprintf("%c",in);
			x++;
			if (x>80) { x=0;
				y++;
				if (y>9) { y=0;
					window(1,3,80,13);clrscr();window(1,1,80,25);
				}
			}
	 }
	}
	return (0);
}

