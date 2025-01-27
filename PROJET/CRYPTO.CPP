/* Programmation & Conception
		Serge Tsakiropoulos
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#define  color(a,b)	textcolor(a);textbackground(b)

#define   NOCOPY   "\nImpossible de dupliquer un fichier sur lui-mˆme.\n"
#define   NOREAD   "\nImpossible d'ouvrir le fichier source."
#define   NOWRITE   "\nImpossible d'ouvrir le fichier cible."

void chaine_min(char *chaine);
void version(void);

long taille_fichier(FILE *fichier);
 int traitement(char **argv_);
 int recherche_param(char argc_, char **argv_,char *chaine);

void main(char argc, char **argv)
{
	version();

	if (argc>4) // v‚rifie la syntaxe
	{
		for (int e=1;e<5;e++)     /* convertit paramŠtres ligne de commande   */
			chaine_min(argv[e]);

		if (! strcmp(argv[1], argv[2]))                     /* source = cible   */
		{
		  fputs(NOCOPY, stderr);
		  exit(2);
		}

		traitement(argv);
	}
	else
	{
	 //color(15,0);
	 cprintf("\n\rErreur : ");
	 //color(7,0);
	 cprintf("ParamŠtre requis manquant \n\r");
	 cprintf("\r\n CRYPTO source.ext objet.ext mot_de_passe CODER|DECODER \n\n");
	 exit(2);
	}

}
void chaine_min(char *chaine)
{
	int p=0;
	p=strlen(chaine);

	for (int i=0;i<p;i++)
	{
		chaine[i]=tolower(chaine[i]);
	}
}
int recherche_param(char argc_, char **argv_,char *chaine)
{

	for (int e=0;e<argc_;e++) {
		if (strcmp(argv_[e],chaine)==0)
		{
			return(e);
		}
	}

	 return(-1);
}
int traitement(char **argv_)
{
	long taille=0,inc=0;
	int divid=0,pas=0;
	int y;
	int long_mot=0;
	int cpt=0;
	int oct_coder=0;

	FILE *infile = stdin;         /* pointeur vers fichier source : initialis‚
		 … 'stdin' pour le cas o— la lecture se fait au clavier.   */
	FILE *outfile = stdout;        // pointeur vers fichier cible : initialis‚

	char oct=0;

	long_mot=strlen(argv_[3]);
	long_mot--;

	if ((infile = fopen(argv_[1], "rt"))== NULL)
	{
			fprintf(stderr, "\nImpossible d'ouvrir le fichier source.\n");
			return 1;
	}

	if ((outfile = fopen(argv_[2], "wt"))== NULL)
	{
		fprintf(stderr, "\nImpossible d'ouvrir le fichier cible.\n");
		return 1;
	}

	y=wherey();
	taille=taille_fichier(infile);
	divid=taille/20;
	printf("\n");
	gotoxy(2,y-1);
	//color(3,0);
	while (!feof(infile))
	{
		oct=fgetc(infile); // Lecture du caractere
		inc++;
		if (inc>divid)
		{
			pas++;gotoxy(1,y);	//color(7,0);
			color(7,0);
			cprintf("Traitement du fichier ");	//color(15,0);
			cprintf("%s",argv_[1]);	//color(7,0);
			cprintf(" en ");			//color(15,0);
			color(15,0);
			cprintf("%s",argv_[2]); //color(14,0);
			cprintf("  <%%%2d>",pas*100/20);
			inc=0;
		}

		if (! strcmp(argv_[4],"coder"))	{
			oct_coder=oct+argv_[3][cpt++];
		}
		if (! strcmp(argv_[4],"decoder"))	{
			oct_coder=oct-argv_[3][cpt++];
		}
			if (oct_coder>255)
				oct_coder=oct_coder-255;
			if (oct_coder<0)
				oct_coder=oct_coder+255;

			if (cpt>long_mot-1) {
				cpt=0;
			}
		fputc((char) oct_coder, outfile);

	}
	fclose(infile);
	fclose(outfile);

	gotoxy(1,y);//color(7,0);
	cprintf("Traitement du fichier ");//color(15,0);
	cprintf("%s",argv_[1]);//color(7,0);
	cprintf(" en ");//color(15,0);
	cprintf("%s",argv_[2]);//color(14,0);
	cprintf("  <% 100> ",pas*100/20);// color(7,0);
	cprintf("\n\r");

	return(0);

}
void version(void)
{
//	color(7,0);
	cprintf("\nUndo  Ver 1  [ TSK 96  ]\n\r\n\r");
	cprintf("Chiffrer un fichier \n\r");
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
