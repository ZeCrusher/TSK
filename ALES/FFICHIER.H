#define __FFICHIER

/*   FFICHIER version 3.00

	Programmation & conception: Tsakiropoulos Serge

	R‚alis‚ le: 20/05/1995

	DŠrniŠre modif: 25/06/97

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

#define DOUBLE		1
#define	FICHIER_INTROUVABLE		0
#define	INDEFINIE				-1
#define	ERREUR_DISK				-1
#define	LECTEUR_COURANT			0 // Pour les infos_ disk
#define	LECTEUR_A				1  // les num‚roes du lecteur commence
#define	LECTEUR_B				2  // … 1 pour _chrdrive
#define	LECTEUR_C				3
#define	LECTEUR_D				4
#define	LECTEUR_E				5


typedef unsigned char byte;
typedef unsigned int  word;


extern void pause(void);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);

extern byte *menu_recherche_stocker[13];

long taille_fichier(FILE *fichier);
int  recherche_fichier(char chemin_fichier_rechercher[14]);
int  recherche_repertoire(char repertoire[14]);
int  attribut_fichier(char filename[14]);
int  get_file_attrib(char *filename);
long espace_disk_libre(int lecteur_disk);
float espace_disk_libre_pourcent(int lecteur_disk); // retourne l'espace disk en pourcent
 int  recherche_nbr_lecteur(void);
void changement_lecteur(int num_lecteur);
void init_mem_fichier();
void init_mem_repertoire();
 int  scan_dir(char *nom_repert,int niveau);
 int compter_niveau_sup();
 int niveau_final(int niveau,int depart);
 int niveau_depart(int niveau,int depart);
 int dessiner_arbre(int fin);
 int dessiner_arbre(int niv_cour,int depart,int fin);
void arbre(int place_r);
void changement_dir(int numb);
int found_file(char fichier_choisie[13],char repertoire_en_cour[200],char type[14],char texte[50]);
 int cluster_lost(int x,int y,char *nom_repert,int niveau,int cluster,long taille_perdu);

unsigned int taille_cluster(void);

