#define __FFICHIER

/*   FFICHIER version 3.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: 20/05/1995
 DŠrniŠre modif: 16/01/96
 Programmation & conception: ZeCrusher
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction

*/
#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif  // Dos.h

#if !defined( __ERRNO_H )
#include <errno.h>
#define __ERRNO_H
#endif

#if !defined( __DIR_H )
#include <dir.h>
#define __DIR_H
#endif

#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif

#if !defined( __STDLIB_H )
 #include <stdlib.h>
 #define __STDLIB_H
#endif



#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif

#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif

#if !defined( __IO_H )
#include <io.h>
#define __IO_H
#endif

#if !defined( __DIRECT_H )
#include <direct.h>
#define __DIRECT_H
#endif

 #define	DOUBLE					1
 #define	FICHIER_INTROUVABLE		0
 #define	INDEFINIE				-1
 #define	ERREUR_DISK				-1
 #define	LECTEUR_COURANT			0 // Pour les infos_ disk
 #define	LECTEUR_A				1  // les num‚ros des lecteurs commencent
 #define	LECTEUR_B				2  // … 1 pour _chrdrive
 #define	LECTEUR_C				3
 #define	LECTEUR_D				4
 #define	LECTEUR_E				5
 #define	Fichier_max				1999
 #define	Repertoire_max			1999
 #define DIRECTO				    0


 #define colorxy(x,y,color,fond) 	gotoxy(x,y);textcolor(color);textbackground(fond)

// Reprend une partie du fichier FMouse . cpp
 #define ZERO_BOUTON_APPUYER	 	0	// definition des bouton de la souris .....
 #define INIT_BOUTON				0
 #define BOUTON_DROIT		    2	// Les boutons de la souris sont ici definie pour une souris
 #define BOUTON_GAUCHE 			1	// donc seulement deux boutons, le DROIT et le GAUCHE, sont actif
 #define BOUTON_GAUCHE_DROIT		3	// pour une souris … trois bouton

typedef unsigned char byte;
typedef unsigned int  word;

	byte tree[Repertoire_max][25];

extern void pause(void);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);
extern void winp(int x,int y,int x1,int y1,int color_texte,int color_fond,int winp_color,char *texte);
extern void space(int x,int y,int l,int color);
extern void montre_souris(void);
extern void init_souris(void);      	//
extern void cache_souris(void);     	//
extern void etat_souris(int *posx,int *posy,int *bouton);
extern void relacher_bsgauche(void);
extern void relacher_bsdroit(void);
extern void titre(int x,int y,int color,int fond,int color2,int fond2,char *titre,int appuyer);
extern int  menu_der(int x,int y,byte largeur,byte hauteur,byte nbr_de_barre,byte type_de_cadre,byte couleur_barre_ecriture,byte couleur_barre_fond,byte couleur_cadre_ecriture,byte couleur_cadre_fond,byte couleur_texte,byte lettre,char *string[40]); // retourne le menu clicker


typedef unsigned char byte;
typedef unsigned int  word;

//long files_=0;
int compteur=0;
int place_r,place_f;
long ficompt;
//long cluster=0;

	byte *menu_file[999];

	byte *disk[26]={" _A:  "," _B:  "," _C:  "," _D:  "," _E:  "," _F:  "," _G:  ",
						" _I:  "," _J:  "," _K:  "," _L:  "," _M:  "," _N:  "," _O:  "
						" _O:  "," _P:  "," _Q:  "," _R:  "," _S:  "," _T:  "," _U:  "
						" _W:  "," _X:  "," _Y:  "," _Z:  " };


long taille_fichier(FILE *fichier);
long espace_disk_libre(int lecteur_disk);
float espace_disk_libre_pourcent(int lecteur_disk); // retourne l'espace disk en pourcent
void changement_lecteur(int num_lecteur);
void init_mem_fichier();
void init_mem_repertoire();
 int  recherche_fichier(char chemin_fichier_rechercher[14]);
 int  recherche_repertoire(char repertoire[14]);
 int  attribut_fichier(char filename[14]);
 int  get_file_attrib(char *filename);
 int  recherche_nbr_lecteur(void);
 int  scan_dir(char *nom_repert,int niveau);
 int compter_niveau_sup();
 int niveau_final(int niveau,int depart);
 int niveau_depart(int niveau,int depart);
 int dessiner_arbre(int fin);
 int dessiner_arbre(int niv_cour,int depart,int fin);
int scan_file(char *nom_repert,int niveau,int l);
void arbre();
void changement_dir(int numb);
int found_file(char fichier_choisie[13],char repertoire_en_cour[200],char type[14],char texte[50]);
void aff_rep();
int scan_repertoire(char repertoire[14]);
void aff_file(void);
char *current_directory(char *path);
void choisir_lecteur(int x,int y);
void ass_vert(int x,int y,int longueur,long nbr,int emplacement,int color);
unsigned int taille_cluster(void);
void classer_nom_fichier(void);
int sort_function( const void *a, const void *b);


	struct liste_repertoire	{
		unsigned char 	repertoire[13];//_MAX_PATH];
		char niveau;
	};
	struct liste_repertoire num_repertoire[Repertoire_max];

	struct liste_fichier	{
		char files[13];	// nom du fichier 13 = 8 char + 1 "." + 3 char extention
		unsigned long	taille;
		char attribut;
	};
	struct	liste_fichier num_fichier[Fichier_max];

	char fichier_default[6];//,nom_fichier_backup[13];
	int	nbr_fichier=0,nbr_repertoire=0;

int recherche_fichier(char chemin_fichier_rechercher[14])
{
	struct find_t ffblk;
   int i=-1;
   int done=0;

	done=_dos_findfirst(chemin_fichier_rechercher,FA_NORMAL+FA_HIDDEN+FA_SYSTEM,&ffblk);

	while (!done)
	{
		i++;
		strcpy(num_fichier[i].files,ffblk.name);
//		strcpy(menu_file[i],num_fichier[i].files);
		num_fichier[i].taille=ffblk.size;
		num_fichier[i].attribut=ffblk.attrib;
		done =_dos_findnext(&ffblk);
		if ((i+1)>Fichier_max) return (i+1);
	}

	return (i+1); // retourne le nombre de fichier
}

int recherche_repertoire(char repertoire[14])
{
	compteur=0;
	init_mem_repertoire();
	space(1,24,80,1+16*1);
	ficompt=0;
	compteur=scan_dir(repertoire,0);
	arbre();
	return(compteur);

}
int scan_repertoire(char repertoire[14])
{
	struct find_t ffblk;
	int i=-1;
	int done;

	done = _dos_findfirst(repertoire,FA_DIREC+FA_HIDDEN+FA_SYSTEM,&ffblk);
	while (!done)
	{
	  if (ffblk.attrib==16)  {
		i++;
		strcpy(num_repertoire[i].repertoire,ffblk.name);
	  }
		done =_dos_findnext(&ffblk);
	}
	return (i+1);
}

void init_mem_fichier()
{
	for (int i=0;i<Fichier_max;i++)	{
		strcpy(num_fichier[i].files," ");
		num_fichier[i].taille=0;
		num_fichier[i].attribut=0;
	}
}
void changement_lecteur(int num_lecteur)
{
	char buffer[4000];
		gettext(1, 1, 80, 25, buffer);
			if (_chdrive(num_lecteur) != 0)  {
				cadre_plein(12,12,47,15,DOUBLE,WHITE,RED,1);// dessine le cadre
				locatext(13,13," Impossible de changer de lecteur ",RED*16+WHITE);
				gotoxy(13,14);
				perror(" ");
				pause();
			}
	puttext(1,1,80,25, buffer);
}
int recherche_nbr_lecteur(void)
{
	int sauvegarde_lecteur, disk;
	int	nbr_lecteur_totaux=0;

		sauvegarde_lecteur = getdisk();    // sauvegarde le lecteur d'origine
		setdisk(sauvegarde_lecteur);    /* Nombre de lecteur logique */
		nbr_lecteur_totaux=0; // initialise les lecteurs

	for (disk = 0;disk < 26;disk++)   {
		setdisk(disk);
			if (disk == getdisk())	  {
				nbr_lecteur_totaux++;
			}
   }
   setdisk(sauvegarde_lecteur);

	return (nbr_lecteur_totaux);
}

int attribut_fichier(char filename[14])
{
   int attrib;

   attrib = get_file_attrib(filename);
	if (attrib == -1)
	{
	  if (errno==ENOENT) return (ENOENT);
	  if (errno==EACCES) return (EACCES);
	  if ((errno!=EACCES)&&(errno!=ENOENT)) printf(" Error number: %d , ERREUR indiqu‚e par FFICHIER.CPP TSK_" , errno);
	}
   else
	  {
		 if (attrib & FA_RDONLY)  return (FA_RDONLY);
		 if (attrib & FA_HIDDEN)  return (FA_HIDDEN);
		 if (attrib & FA_SYSTEM)  return (FA_SYSTEM);
		 if (attrib & FA_LABEL)   return (FA_LABEL);
		 if (attrib & FA_DIREC)   return (FA_DIREC);
		 if (attrib & FA_ARCH)    return (FA_ARCH);
	  }
   return 0;

}
int get_file_attrib(char *filename)
{  // retourne l'attribut du fichier
	return(_chmod(filename, 0));
}

float espace_disk_libre_pourcent(int lecteur_disk) // retourne l'espace disk en pourcent
{
	union REGS regs; // sert … ‚changer des informations avec les fonctions: int86
	regs.h.ah=0x36;  // Numero de la fonction
	regs.h.dl=lecteur_disk; // 0 pour A , 1 pour C
	int86(0x21, &regs,&regs);
	return( (float ) regs.x.bx *100 / regs.x.dx); // Calcul du poucentage
}

long espace_disk_libre(int lecteur_disk) // retourne l'espace disk
{
	struct dfree espace;

	getdfree(lecteur_disk, &espace);

	if (espace.df_sclus == 0xFFFF)   {
		return (ERREUR_DISK);
	}
	else   {
		return((long) espace.df_avail*(long) espace.df_bsec * (long) espace.df_sclus);
	}
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
void arbre()
{
	int depart=0;
	int fin=0;
	int niveau_max=0;

	niveau_max=compter_niveau_sup();
	depart=niveau_depart(0,place_r);
	fin=niveau_final(0,depart);

	dessiner_arbre(fin); // Dessine l arbre a partir du niveau 0 seulement

	fin=depart=0; // Init

	for (int i=1;i<niveau_max+1;i++) // Boucle niveau >0
	{
		fin=depart=place_r; // Base 0

		do
		{
			depart=niveau_depart(i,place_r+fin+1); // recherche le premier niveau 1 , 2 , 3 etc ...
			fin=niveau_final(i,depart); // rechercher le prochaine niveau -1
			if (depart!=-7) // Plus de niveau ou erreur
				dessiner_arbre(i,depart,fin); // redessine l arbre , <> de la fonction niveau 0
		}
		while (depart!=-7); // Until the End !

	}

}
int scan_dir(char *nom_repert,int niveau)
{
	int res;

	struct ffblk info;
	char nom[_MAX_PATH]={0},repert[_MAX_PATH]={0};

	strcpy(repert,nom_repert);

		if (repert[strlen(repert)-1]!='\\')
			strcat(repert,"\\");
		strcpy(nom,repert); strcat(nom,"*.*");

		res=findfirst(nom,&info,0xFF);

		textcolor(14);gotoxy(2,24);textbackground(1);
		cprintf("Nombre de repertoire > ");
		textcolor(12);

		while ( res==0 )
		{
			switch(info.ff_attrib)
			{
			case FA_RDONLY :
			case FA_HIDDEN :
			case FA_SYSTEM :
			case FA_LABEL  :
			case FA_ARCH   : ficompt++;
							 colorxy(50,24,14,1);
							 cprintf(" Nombre de fichier ");
							 textcolor(12);
							 cprintf("<%ld>",ficompt);
			 break;

				case FA_DIREC	:

					if (strcmp(info.ff_name,".") && strcmp(info.ff_name,".."))
					{
						strcpy(num_repertoire[compteur].repertoire,info.ff_name);
						num_repertoire[compteur].niveau=niveau;
						compteur++;
						strcpy(nom,repert); strcat(nom,info.ff_name);
						colorxy(25,24,12,1);cprintf("%d",compteur);
						scan_dir(nom,niveau+1);
					}

				break ;
		}
		res=findnext(&info);
	}
	return(compteur);
}

int niveau_depart(int niveau,int depart)
{

	for (int es=depart;es<Repertoire_max;es++)	{
			if (num_repertoire[place_r+es].niveau==niveau)
				return( es );
	}
		return( -7 );

}
int niveau_final(int niveau,int depart)
{
	int retour=0;

	for (int es=depart;es<Repertoire_max;es++)
	{
		if (num_repertoire[place_r+es].niveau==niveau)
			retour=es;
		if (num_repertoire[place_r+es+1].niveau<niveau)		{
			return( retour );
		}
		if (num_repertoire[place_r+es].niveau==255)
			return( retour );
	}

	return (retour);
}

void init_mem_repertoire()
{
	for (int i=0;i<Repertoire_max;i++)	{
		strcpy(num_repertoire[i].repertoire," ");
		num_repertoire[i].niveau=255;
		strcpy(tree[i],"\x0\x0\x0\x0");
	}
}
int compter_niveau_sup()
{
	int sup_=0;


	for (int i=0;i<Repertoire_max;i++)	{
		if ((num_repertoire[i].niveau>sup_)&&(num_repertoire[i].niveau!=255))
			sup_=num_repertoire[i].niveau;
	}
	return(sup_);


}
int dessiner_arbre(int fin)
{
	int niveau_=0;

	for (int j=0;j<Repertoire_max;j++)
	{
		niveau_=num_repertoire[place_r+j].niveau;

		if ((niveau_==0)&&((place_r+j)<fin))
		{
			strcpy(tree[j],"ÃÄ");
		}
		else
		{
			if ((niveau_==0)&&((place_r+j)==fin))	{
					strcpy(tree[j],"ÀÄ");
			}
			if ((niveau_>0)&&((place_r+j)<fin))		{
				strcpy(tree[j],"³ ");
			}
			if ((niveau_>0)&&((place_r+j)>fin))  	{
					strcpy(tree[j],"  ");
			}

		}
	}

	return(0);

}
int dessiner_arbre(int niv_cour,int depart,int fin)
{

	int niveau_=0;

	for (int j=depart;j<=fin;j++)
	{
		niveau_=num_repertoire[j].niveau;

		if ((niveau_==niv_cour)&&((place_r+j)==fin))
		{
			if (((strlen(tree[j])/2) <niv_cour))
			{
				for (int e=(strlen(tree[j])/2);e<niv_cour;e++) {
						strcat(tree[j],"  ");
				}
			}
			strcat(tree[j],"ÀÄ");

		}
		if ((niveau_==niv_cour)&&((place_r+j)<fin))
		{
			if (((strlen(tree[j])/2)<niv_cour))
			{
				for (int e=(strlen(tree[j])/2);e<niv_cour;e++)	{
						strcat(tree[j],"  ");
				}
			}
			strcat(tree[j],"ÃÄ");
		}
		else
		{
			if ((niveau_!=niv_cour)&&((place_r+j)<fin))
			{
				if (((strlen(tree[j])/2)<niv_cour))
				{
					for (int e=(strlen(tree[j])/2);e<niv_cour;e++) {
							strcat(tree[j],"  ");
					}
				}
				strcat(tree[j],"³ ");
			}
		}

	}

	return(0);

}
void changement_dir(int numb)
{
	int niveau=0,var=0,indice=numb;
	int chemin[300]={0};
	char compteur=1;

	for (int e=0;e<300;e++) 	chemin[e]=-1;

	chemin[0]=numb;
	do
	{
		niveau=num_repertoire[numb-var].niveau;
		var++;
		if (num_repertoire[indice].niveau>num_repertoire[numb-var].niveau)	{
			indice=numb-var;
			chemin[compteur++]=indice;
		}
	}
	while (niveau!=0);

	chdir("\\"); // Racine
	for (int i=0;i<compteur+1;i++)	{
		chdir(num_repertoire[chemin[compteur-i]].repertoire);
	}

}

int found_file(char fichier_choisie[13],char repertoire_en_cour[200],char type[14],char texte[50])
{
 //	char repertoire[14];
	char choix_menu=0;
	int bouton=0,x,y;
	long nbr_fichier=0,nbr_repertoire=0;
	char path[MAXPATH],rep_cour[MAXPATH];
	char buffer[4000];
	int indice;

	cache_souris();
	gettext(1, 1, 80, 25, buffer);
	winp(15,3,65,23,15,5,15,texte);
	locatext(17,5,"Fichier             >",7+16*15);
	locatext(17,6,"Repertoire en cours >",7+16*15);

	// Cadre pour les fichiers et des repertoires
	cadre_plein(18,8,36,18,DOUBLE,8,15,0);// dessine le cadre fichier
	cadre_plein(39,8,62,20,DOUBLE,8,15,0);// dessine le cadre repertoire
	locatext(41,8," Fichier ",0+16*7);
	locatext(20,8," R‚pertoire ",0+16*7);
	init_mem_repertoire();
	nbr_repertoire=scan_repertoire("*.*");
	nbr_fichier=recherche_fichier(type);
	titre(20,20,15,7,DARKGRAY,15,"   Lecteur   ",0);
	titre(26,22,YELLOW,1,DARKGRAY,15,"  OK  ",0);
	titre(46,22,YELLOW,1,DARKGRAY,15," Annuler ",0);

	ass_vert(62,9,9,nbr_fichier,1,16*15);
	ass_vert(36,9,7,nbr_repertoire,1,16*15);
	colorxy(50,8,15,7);cprintf(" %4d ",nbr_fichier);

	aff_rep();
	aff_file();

	init_souris();

	do
	{
		montre_souris();

		bouton = ZERO_BOUTON_APPUYER; // indique qu'aucun bouton n'est appuyer
		etat_souris(&x,&y,&bouton);

		x=((x/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		y=((y/8)+1);
//		 gotoxy(1,1);printf("%d  %d",x,y);

		if ((bouton==BOUTON_GAUCHE)&&(x==62)&&(y==9))
		{
			if (place_f>0)  {
				delay(10);
				place_f--;	aff_file();
			}
			//void ass_vert(int x,int y,int longueur,int nbr,int emplacement,int color)
			ass_vert(62,9,9,nbr_fichier,place_f,0+16*15);
			delay(20);
		}
		if ((bouton==BOUTON_GAUCHE)&&(y==22)&&(x>45)&&(x<55))
		{
			cache_souris();
			relacher_bsgauche();
			titre(46,22,YELLOW,1,DARKGRAY,15," Annuler ",1);
			puttext(1, 1, 80, 25, buffer);
			return(-1);

		}
		if ((bouton==BOUTON_GAUCHE)&&(y==22)&&(x>25)&&(x<32))
		{
			cache_souris();
			relacher_bsgauche();
			cache_souris();
			titre(26,22,YELLOW,1,DARKGRAY,15,"  OK  ",1);
			if (strlen(fichier_choisie)==0) {
				puttext(1, 1, 80, 25, buffer);
				return(0);
			}
			else {
				strcpy(repertoire_en_cour,current_directory(path));
				puttext(1, 1, 80, 25, buffer);
				return(1);
			}
		}
		if ((bouton==BOUTON_GAUCHE)&&(y==20)&&(x>19)&&(x<33))
		{
			cache_souris();
			relacher_bsgauche();
			titre(20,20,15,7,DARKGRAY,15,"   Lecteur   ",1);
			choisir_lecteur(20,10);
			init_mem_fichier();init_mem_repertoire();
			nbr_repertoire=scan_repertoire("*.*");nbr_fichier=recherche_fichier(type);
			place_r=place_f=0;aff_file();aff_rep();
			colorxy(50,8,15,7);cprintf(" %4d ",nbr_fichier);
			ass_vert(62,9,9,nbr_fichier,1,0+16*15);
		}
		if ((bouton==BOUTON_GAUCHE)&&(y>8)&&(y<20)&&(x>39)&&(x<62)&&(strcmp(num_fichier[place_f+(y-9)].files," ")!=0))
		{
			cache_souris();
			indice=place_f+(y-9);
			fichier_choisie[0]=0;
			strcpy(fichier_choisie,num_fichier[indice].files);
			space(40,y,22,17);
			locatext(41,y,num_fichier[indice].files,15+16*1);
			delay(200);
			space(40,y,22,15+16*15);
			locatext(41,y,num_fichier[indice].files,1+16*15);
			space(40,5,25,15+16*15);
			locatext(40,5,num_fichier[indice].files,9+16*15);
			relacher_bsgauche();
			montre_souris();
		}
		//////////////////////////////////////////////////////////////////
		if ((bouton==BOUTON_GAUCHE)&&(y>8)&&(y<18)&&(x>18)&&(x<36)&&(strcmp(num_repertoire[place_r+(y-9)].repertoire," ")!=0))
		{
			cache_souris();
			space(40,5,25,15+16*15);
			space(40,6,25,15+16*15);
			space(19,y,17,17);
			locatext(20,y,num_repertoire[place_r+(y-9)].repertoire,15+16*1);
			delay(200);
			space(19,y,17,15+16*15);
			locatext(20,y,num_repertoire[place_r+(y-9)].repertoire,1+16*15);
			strcpy(rep_cour,current_directory(path));
			chdir(num_repertoire[(y-9)+place_r].repertoire);
			if (strlen(path)>15)
				locatext(40,6,num_repertoire[(y-9)+place_r].repertoire,9+16*15);
			else
				locatext(40,6,current_directory(path),9+16*15);
			place_r=place_f=0;
			init_mem_fichier();init_mem_repertoire();
			nbr_repertoire=scan_repertoire("*.*");
			nbr_fichier=recherche_fichier(type);
			aff_file();aff_rep();
			colorxy(50,8,15,7);cprintf(" %4d ",nbr_fichier);
			relacher_bsgauche();strcpy(rep_cour,"");
			montre_souris();
			ass_vert(36,9,7,nbr_repertoire,1,16*15);
			ass_vert(62,9,9,nbr_fichier,1,16*15);

		}

		if ((bouton==BOUTON_GAUCHE)&&(x==62)&&(y==19))
		{
			if (place_f<(nbr_fichier-11)) {
				delay(10);
				place_f++;	aff_file();
			}
			ass_vert(62,9,9,nbr_fichier,place_f,0+16*15);
			delay(20);

		}
		if ((bouton==BOUTON_GAUCHE)&&(x==36)&&(y==17))
		{   delay(20);
			if (place_r<(nbr_repertoire-9)) {	place_r++;
				aff_rep();
			}
		ass_vert(36,9,7,nbr_repertoire,place_r,0+16*15);

		}
		if ((bouton==BOUTON_GAUCHE)&&(x==36)&&(y==9))
		{   delay(20);
			if (place_r>0) {
				place_r--;
				aff_rep();
			}
		ass_vert(36,9,7,nbr_repertoire,place_r,0+16*15);

		}

		if  (bouton==BOUTON_GAUCHE_DROIT) {
			choix_menu=1;
		}

	}	//****************  fin de la grande boucle debut ligne -> 543
	while(choix_menu==0);
	cache_souris();
	puttext(1, 1, 80, 25, buffer);
	strcpy(repertoire_en_cour,current_directory(path));
	return (0);

}

void aff_rep(void)
{
	for (int i=0;i<9;i++)
		space(19,9+i,17,15+16*15);

	for (int es=0;es<9;es++)	{
		locatext(20,9+es,num_repertoire[place_r+es].repertoire,1+16*15);
	}

}
void aff_file(void)
{
	for (int i=0;i<11;i++)
		space(40,9+i,22,15+16*15);

	for (int es=0;es<11;es++)	{
		locatext(41,9+es,num_fichier[place_f+es].files,1+16*15);
	}

}
char *current_directory(char *path)
{
   strcpy(path, "X:\\");
   path[0] = 'A' + getdisk();
   getcurdir(0, path+3);
   return(path);
}
void choisir_lecteur(int x,int y)
{
	int resultat_menu;
	int nbr_lecteur=0;
	int taille=0;


	nbr_lecteur=recherche_nbr_lecteur();

	 if (nbr_lecteur>10) taille=10; else taille=nbr_lecteur;


	resultat_menu=menu_der(x,y,9,taille+1,nbr_lecteur+1,0,WHITE,LIGHTRED,DARKGRAY,11,BLACK,BLUE,disk);

	if (resultat_menu!=-1)
	{	place_r=place_f=0;
		changement_lecteur(resultat_menu);
	}

}
/* 10/07/97 *****************************************************************
  parametre :
	  longueur = nbr de ligne
	  nbr = nbr d'element dans tableau
	  emplacement = emplacement dans nbr
  return :
	Neant
****************************************************************************/
void ass_vert(int x,int y,int longueur,long nbr,int emplacement,int color)
{
	int position=0; // Position du caractere '\x8'

	for(int i=0;i<longueur;i++)
		locatext(x,y+i+1,"°",color);

	nbr=nbr-longueur;

	if (emplacement==1) {
		position=0;
	}
	else
	{
		if (nbr==0) nbr=1;
		position=(int)((longueur*emplacement)/nbr);

	if (emplacement==nbr-2)
		position=longueur-1;
	}
	locatext(x,y+1+position,"\x8",color);

	locatext(x,y,"",1+16*3);
	locatext(x,y+i+1,"",1+16*3);


}
/* 30/09/97 *****************************************************************
  parametre :
	Neant
  return :
	La taille d'un cluster du disque en cours , Unsigned INT
****************************************************************************/
unsigned int taille_cluster(void)
{
	unsigned int SecteursParCluster;
	unsigned int BytesParSecteur;

	/* Obtient la taille des clusters */
	asm {
		mov ah, 0x36
		int 0x21
		mov SecteursParCluster, ax
		mov BytesParSecteur, cx
	}
	return(SecteursParCluster* BytesParSecteur);
}
/* 30/09/97 *****************************************************************

  Classe les Noms des fichiers lue sur le disque

  parametre :
	Neant
  return :
****************************************************************************/
void classer_nom_fichier(void)
{
   qsort((void *) num_fichier,Fichier_max,13, sort_function);

}
int sort_function( const void *a, const void *b)
{
   return( strcmp((char *)a,(char *)b) );
}

