/* OutWin version 2.00 Hocken
*/

#include <stdio.h>
#include <stdlib.h>

 #define  color(a,b)				textcolor(a);textbackground(b)
 #define CLS						textbackground(BLACK);clrscr()
 #define colorxy(x,y,color,fond) 	gotoxy(x,y);textcolor(color);textbackground(fond)

#if !defined( __FINCLUDE )
 #include "d:\tsk\fct\finclude.h"
 #define __FINCLUDE
#endif
#if !defined( __FCADRE )
 #include "d:\tsk\fct\fcadre.h"
 #define __FCADRE
#endif
#if !defined( __FMOUSE )
 #include "d:\tsk\fct\fmouse.h"
 #define __FMOUSE
#endif
#if !defined( __FMENU )
 #include "d:\tsk\fct\fmenu.h"
 #define __FMENU
#endif
#if !defined( __FMESSERR )
 #include "d:\tsk\fct\fmesserr.h"
 #define __FMESSERR
#endif
#if !defined( __FASCII )
 #include "d:\tsk\fct\fascii.h"
 #define __FASCII
#endif


 #define PAS_DE_SOURIS      2  // Pour le message d'erreur quand il n'y a pas de souris
 #define MODE_RAPIDE		1
 #define MODE_APPROFONDIE   2
 #define QUITTER			0

////////////////////////// Dans FASCII.H /////////////////////////////////////
extern void table_ascii(void);
extern void init_ascii();  								// Init la cr�ation des codes ASCII

//////////////////////////// Dans Fmouse //////////////////////////////////////////
extern void relacher_bsgauche(void);


// interface
int  menu_der(void);  // menu de demarrage , c est le premier menu .
 int menu_rapide(void);
 int menu_approf(void);
void afficher_path(int depart);
void afficher_option(int depart); // fonction qui affiche dans l'interface approfondie les commandes options
void interface(void); // presentation du menu principal approfondie .
void interface_rapide(void); // Affiche le menu Rapide
void interface_approf(void); // affiche le menu approfondie

// fichier
 int initialiser_struct(char *fichier_table);
 int lire_msdos(char *fichier_dos);
int compter_option(void); // Compte le nombre de ligne dans le fichier Table.Out , Mais une fois que la scruture est initialis�.
int compter_path(void);

// struct
 int analyser_ligne(char ligne[128],char commande[32],char type[32],char min[10],char max[10],char commentaire[128]);

	struct Msdosys {   // Structure qui permet de stocker les parametre du fichier MSDOS.sys
		char win_commande[32];
		char commentaire[128];
		char type_donnee[32];
		char min[10];
		char max[10];
		char valeur_fichier[80];
	};
	struct Msdosys Msdos95[50];
	struct Msdosys Table95[50];

	struct Msdosys Mrapide[50];
	struct Msdosys MApprof[50];

	int nbr_commande=0;
	int emplacement_option[50]; // memorise les emplacements des options dans la structure MSDOS95
	int emplacement_path[50];   // Idem mais avec Path

void main(void)
{
	char choix_user=0;
	char *buffer;


	if ((buffer = (char *) malloc(4096)) == NULL)	{
		printf("\a");
	}

	gettext(1, 1, 80, 25, buffer); // gettext sauvegarde dans une m�moire tampon du texte provenant de l'�cran en mode texte

//	lire_msdos("C:\\MSDOS.SYS");

	nbr_commande=initialiser_struct("c:\\tsk\\table.out"); // lit le fichier table.out qui contien les differentes stucture

	choix_user=menu_der();

	 if (choix_user==MODE_RAPIDE) 		{ // Charge le menu de configuration rapide
		menu_rapide();
		puttext(1, 1, 80, 25, buffer); // puttext recopie le texte d'une m�moire tampon vers l'�cran en mode texte
	 }
	 if (choix_user==MODE_APPROFONDIE)  { // Charge le menu niveau expert
		menu_approf();
//		puttext(1, 1, 80, 25, buffer); // puttext recopie le texte d'une m�moire tampon vers l'�cran en mode texte
	 }
	 if (choix_user==QUITTER) {
		exit(0);
	}

}
int initialiser_struct(char *fichier_table)
{

	FILE *in;

	char msg[120]={0}; // Pour stocker la ligne que je suis en train de lire

	int cpt=0, // S'incremente lors d une nouvelle commande
		val=0; // si cette ligne est une ligne avec une commande

	char type_com[32]={0}; // Stocke temporairement le type de la commande
	char commande[64];  // commande cr�e par le User .
	char comment[128]; // Pour les commentaires de l utilisateur � propos de la commande .
	char min[10]={0}, // si il y a un type decimal_option ou decimal_path
		 max[10]={0};


	if ((in=fopen(fichier_table,"rt"))== NULL)	{
	   fclose(in);
	   return 1;
	}

	do
	{
		fgets(msg,128,in); // Lire une ligne du fichier TABLE.OUT
		val=analyser_ligne(msg,commande,type_com,min,max,comment);

		if (val!=1) {
			strcpy(Table95[cpt].win_commande,commande);
			strcpy(Table95[cpt].type_donnee,type_com);
			strcpy(Table95[cpt].min,min);
			strcpy(Table95[cpt].max,max);
			strcpy(Table95[cpt].commentaire,comment);
			cpt++; // incrementation du compteur pour la structure.
		}

	}
	while(!feof(in));

	 fclose(in);

	 return (cpt);

}
int menu_der(void)
{
	int choix_menu=0; // utiliser pour la boucle principale do while


	 _setcursortype(_NOCURSOR); // � _NOCURSOR     (Pas de curseur)

	fond(0);
	table_ascii();						   // Cr�ation des nouveau char ASCII
	charger_table("c:\\dos\\long.als");   // Charge la police de caractere ALES

	cadre_plein(15,7,66,18,BARRE,7,15,1);
	locatext(15,6,"                     H O C K E N                    ",15+16*7);
	titre(17,9,14,1,DARKGRAY,15, "    Mode Rapide   ",0);locatext(40,9,"Parametres de base pour",0+16*15);locatext(40,10,"configurer windows.",0+16*15);
	titre(17,12,14,1,DARKGRAY,15," Mode Approfondie ",0);locatext(40,12,"Utilisation de tous les",0+16*15);locatext(40,13,"parametres.",0+16*15);
	titre(17,15,14,12,DARKGRAY,15,"  Quitter Hocken  ",0);locatext(40,15,"Retour au syst�me.",0+16*15);

	init_souris();
	do
	{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();

		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==9)&&(valeur_xxreel<35)&&(valeur_xxreel>16))	{
			titre(17,9,14,1,DARKGRAY,15, "    Mode Rapide   ",1);
			return(MODE_RAPIDE);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==12)&&(valeur_xxreel<35)&&(valeur_xxreel>16))	{
			titre(17,12,14,1,DARKGRAY,15," Mode Approfondie ",1);
			return(MODE_APPROFONDIE);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==15)&&(valeur_xxreel<35)&&(valeur_xxreel>16))	{
			titre(17,15,14,12,DARKGRAY,15,"  Quitter Hocken  ",1);
			return(QUITTER);
		}
	 }
	while(choix_menu==0);

	cache_souris();

	return(0);

}
void interface(void)
{


}

int menu_rapide(void)
{
	interface_rapide(); // Affiche le menu rapide

	return(0);

}
int menu_approf(void)
{
	int path=0,    // Permet de gerer la liste des commandes path
		option=0;  // et ici les options
	char choix=0; // Est utiliser pour gerer la boucle principal Do While

	unsigned Position_Path=0; // indique le Haut du menu
	unsigned Position_Option=0; // dans les deux menus , soit Path et Option
	unsigned nbr_option=0;		// Memorise le nombre de ligne option , donc le d'option dans le fichier table.out
	unsigned nbr_path=0;		// idem mais pour path

	cache_souris(); // cache la souris avant l affichage

	interface_approf(); // affiche le menu approfondie

	nbr_option=compter_option();
	nbr_path=compter_path();

	afficher_path(0);   // affiche les commandes de PATH
	afficher_option(0); //et Affiche les commandes de options


	init_souris();

	do
	{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();

		valeur_xxreel=((posx/8)+1); // Ici il ne faut pas 640 x 480 d'ou / 8)+1
		valeur_yyreel=((posy/8)+1);

		// Affichage des coordonn�es
		gotoxy(30,1);cprintf(" X %d , Y %d ",valeur_xxreel,valeur_yyreel);

		if (bouton==BOUTON_GAUCHE_DROIT) {
			choix=1; // Permet de sortir de la boucle
		}
/////////////// Sequence Path //////////////////////////
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==5)&&(valeur_xxreel==25))	{
			if (Position_Path>=1)	{
				Position_Path--;
			}
				afficher_path(Position_Path);
				delay(100);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==8)&&(valeur_xxreel==25))	{
			if (Position_Path<(nbr_path-5))	{
				Position_Path++;
			}
				afficher_path(Position_Path);
				delay(100);
		}

////////////// Sequence Option ///////////////////////////
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==14)&&(valeur_xxreel==25))	{
			if (Position_Option>=1)	{
				Position_Option--;
			}
				afficher_option(Position_Option);
				delay(100);
		}
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==23)&&(valeur_xxreel==25))	{
			if (Position_Option<(nbr_option-11))	{
				Position_Option++;
			}
				afficher_option(Position_Option);
				delay(100);
		}

	}
	while (choix==0);

	init_souris();

	 return(0);
}
int analyser_ligne(char ligne[128],char commande[32],char type[32],char min[10],char max[10],char commentaire[128])
{
	int taille=0,pvirgule=0,espace=0;
	char format[12]={'[',']','=',44,'(','-',')',44,'"','"',';'};
	char save[128]={0};
	// [commande]=Texte,

	strcpy(save,ligne); // sauvegarde la ligne pour le type decimal_??????(x-y);
	strcpy(commande,"");
	strcpy(commentaire,"");
	strcpy(type,"");
	strcpy(min,"");
	strcpy(max,"");

	int emplacement[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	if ((taille=strlen(ligne))>128) taille=128;

	for (int i=0;i<taille-1;i++)	{ /////////////// for //////////////////////////////////////////////
		if (ligne[i]==';') pvirgule=1;
		if (ligne[i]==' ') espace++;
		if ((ligne[i]=='/')&&(ligne[i+1]=='/')) { // commentaire trouv�
			if ((espace!=i)&&(pvirgule!=1)) {	  // Il y a t-il des chars autre que ' ' (0x20) devant et pas de ; devant
				return(0);						  // Erreur
			}
				return(1);                        // OK la ligne est un commentaire
		}
	}
	for (int j=0;j<taille;j++) 	{
		for (int a=0;a<10;a++) 		{ // Nombre de caractere , [ ] = ( ) , " " ;
			if (ligne[j]==format[a]) {
				emplacement[a]=j; // incra s increment dans l'ordre de format
			}
		}
	}
	// 0 [ ,1 ] ,2 =,3 44,4 ( , 5 - , 6 ) , 7 44, 8 ", 9 ", 10 ;
	if (emplacement[0]==-1)	return(1); 	//ici il y a une erreur car pas de [ trouver dans la ligne du fichier

	strdecoupe(ligne,commande,emplacement[0]+1,emplacement[1]);

	strdecoupe(ligne,type,emplacement[2]+1,emplacement[3]);

	if (type[0]=='d') { // le type est il un decimal_option ou un decimal_path
		strnset(type,0,19); // initialise la cha�ne a \x0
		strdecoupe(save,type,emplacement[2]+1,emplacement[4]);
	}
	else {
		strdecoupe(ligne,type,emplacement[2]+1,emplacement[3]);
	}
	if (emplacement[4]!=-1) {
		strdecoupe(save,min,emplacement[4]+1,emplacement[5]);
	}
	if (emplacement[6]!=-1) {
		strdecoupe(save,max,emplacement[5]+1,emplacement[6]);
	}
	if (emplacement[7]!=-1) {                // +2 car ,"
		strdecoupe(save,commentaire,emplacement[7]+2,emplacement[8]);
	}
	return(0);
}
void interface_rapide(void)
{

	cache_souris();

	cadre_plein(15,7,66,20,BARRE,3,15,1);
	locatext(15,6,"            Mode de configuration rapide            ",1+16*3);

	locatext(28,9,"D�marrer sous Msdos 7.xx",0+16*15);
	locatext(28,11,"Afficher le logo Windows 95",0+16*15);
	locatext(28,13,"D�marrer en mode sans Echec",0+16*15);
	locatext(28,15,"Afficher le menu de demarage",0+16*15);

	for(int i=0;i<8;i+=2)
		locatext(22,9+i,"( )",8+16*15);

	titre(18,18,14,12,DARKGRAY,15, " Annuler ",0);
	titre(30,18,14,1,DARKGRAY,15, " Sauver ",0);
	titre(41,18,14,1,DARKGRAY,15, " Quitter ",0);
	titre(53,18,0,14,DARKGRAY,15, " Rebooter ",0);

	getch(); // Tapez sur une touche

}
void interface_approf(void)
{
	cache_souris();
	cadre_plein(1,1,80,26,1, 9 , 9 ,9);  // cadre rep
	locatext(1,1,"                                              							         ",LIGHTRED+16*WHITE);
	bar_menu(3,1,BLACK,WHITE,RED," _Fichier  _Edit                                                          _Aide  ");
	gotoxy(1,1);
	locatext(1,25,"                                                                             ���",12+16*15);
	titre(2,3,14,1,DARKGRAY,9, " Enregister ",0);
	titre(16,3,12,15,DARKGRAY,9, "                 Section Path               ",0);
	titre(16,10,12,15,DARKGRAY,9, "                Section Option              ",0);
	cadre_plein(35,12,77,23,BARRE,15,1,0);
	locatext(35,12,"  Signification de                         ",12+16*15);
	locatext(3,12,"Commandes               Valeur",15+16*9);
	locatext(25,6,"�",14+16*9);
	locatext(25,7,"�",14+16*9);
	for (int i=0;i<8;i++) locatext(25,15+i,"�",14+16*9);
	locatext(25,5,"\30",14+16*1);
	locatext(25,8,"\31",14+16*1);
	locatext(25,14,"\30",14+16*1);
	locatext(25,23,"\31",14+16*1);

}
/*
   Fonction qui affiche les paths
	(int depart)
		est l element de depart de la liste , c est le premier qui
		sera afficher .
*/
void afficher_path(int depart)
{
	// ce cadre permet d 'effacer la liste , avec windows() il fallait faire une reservation de memoire .
	cadre_plein(1,5,24,8,0, 9  , 9   ,9);  // cadre rep

	for(int i=0;i<4;i++) {
		if ((emplacement_path[i+depart]!=0)||(depart==0)) {
			locatext(3,5+i,Table95[emplacement_path[i+depart]].win_commande,14+16*9);
		}
	}

}
void afficher_option(int depart)
{
	// ce cadre permet d 'effacer la liste , avec windows() il fallait faire une reservation de memoire .
	cadre_plein(1,13,24,24,0, 9  , 9   ,9);  // cadre rep

	for(int i=0;i<10;i++) {
		if (emplacement_option[i+depart]!=0) {
			locatext(3,14+i,Table95[emplacement_option[i+depart]].win_commande,14+16*9);
		}
	}

}
int compter_option(void)
{
	int cpt=0;
	int i=0;
	do
	{
		if (Table95[i++].type_donnee[8]=='o') { // il sagit d'une commande
			emplacement_option[cpt++]=i-1; //		cpt++;  incremente le compteur qui compte le nbr de commandes en tous
		}
	}
	while (i<nbr_commande);

	return (cpt+1); // ici pour avoir le bon nombre de commandes il faut +1 , a cause de la boucle do
}
int compter_path(void)
{
	int cpt=0;
	int i=0;
	do
	{
		if (Table95[i++].type_donnee[8]=='p') { // il sagit d'une commande
			emplacement_path[cpt++]=i-1; //		cpt++;  incremente le compteur
		}
	}
	while (i<nbr_commande);

	return (cpt+1);
}

/*************************************************************************
	Fonction int lire_msdos(char *fichier_dos);
	recupere les donn�es de chaque commandes contenue dans le fichier
	msdos.sys
	entrer : le nom du fichier *.sys , qui est un fichier texte
	sortis : -1 en cas d erreur
			  0 en cas de succes
**************************************************************************/
int lire_msdos(char *fichier_dos)
{

	FILE *in;

	if (_dos_setfileattr(fichier_dos,0) != 0)	{ // supprime les attributs du fichier msdos.sys
	   exit(1);
	}
	if ((in = fopen(fichier_dos,"rt"))== NULL)	{
	   exit(1);
	}

	fclose(in);

	exit(0);

}
/*************************************************************************
	Fonction int sauve_msdos(...);
	sauve les donnees du fichier msdos.sys une fois que le fichier a �t�
	recupere avec la fonction lire_msdos
	msdos.sys
	entrer : pas encore d�finie
	sortis :
**************************************************************************/
int sauve_msdos(int cpt)
{
	FILE *out;

	if ((out = fopen("C:\\test.sys","wt"))== NULL)	{
	   fprintf(stderr, "Impossible de cr�er le fichier MSDOS.SYS\n");
	   exit(1);
	}


}
/*************************************************************************
	Fonction int erreur_fichier
	indique que l'operation sur un fichier n a pu �tre reussi
**************************************************************************/
void erreur_fichier(void)
{
	cache_souris();
	cadre_plein(24,7,56,11,0, 7  , 7   ,1);  // cadre rep
	locatext(24,7,"  Erreur sur fichier             ",RED+16*WHITE);
	titre(36,9,YELLOW,1,DARKGRAY,7, " Quitter ",0);
	montre_souris();
	bouton_xyl(36,9,9); // Gestion du Bouton OK
	titre(36,9,YELLOW,1,DARKGRAY,7," Quitter ",1);
	cache_souris();
}
