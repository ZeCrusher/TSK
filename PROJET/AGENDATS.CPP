#include <conio.h>
#include <errno.h>
#include <direct.h>
#include <dir.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#include <io.h>
#include <stdlib.h>
#include <bios.h>

#pragma -O2		// vitesse
#pragma -G		// vitesse du code EXE
#pragma -ml		// Pour les pointeurs - Modele de m‚moire voir Option|Compiler|Code_generation|Large(ù)

// Ces fonctions ne possedent pas d' #include <xxxxxxx.h>
#include "c:\tskÿ\fctÿ\finclud.cpp"
#include "c:\tskÿ\fctÿ\fsaisie.cpp"
#include "c:\tskÿ\fctÿ\fmouse.cpp"
//#include "c:\tskÿ\fctÿ\fmode.cpp"
#include "c:\tskÿ\fctÿ\fcadre.cpp"
#include "c:\tskÿ\fctÿ\fmenu.cpp"
#include "c:\tskÿ\fctÿ\fentete.cpp"
#include "c:\tskÿ\fctÿ\ffichier.cpp"

// definition de constante & autre types
#define VIDEO 					0x10
#define PAUSE   				while(bioskey(1)==0)
#define BEEP					printf("\a");
#define color(x,y)				textcolor(x);textbackground(y)
#define fond_saisie 			textcolor(BLACK);textbackground(LIGHTGRAY);
#define FOND_SAISIE_CHAINE 		textcolor(WHITE);textbackground(RED);
#define FOND_VISU   			textcolor(WHITE);textbackground(GREEN);
#define CLS 					textbackground(BLACK);clrscr();
#define END						exit(EXIT_SUCCESS);
#define LONGUEUR_DU_CADRE 18
#define INIT_BOUTON				0
#define MENU_PRINCIPAL			0  //
#define SAISIR_CHAINE			1  //
#define VISUALISER_CHAINE		2  //
#define QUITTER_AGENDATS		3  //


// Fonction principal
void menu_principal();
void saisir_fiches();
void visualiser();
void quitter_agenda();
void cadre_aide(int num_aide);
void gestion_fichier();

	int	emplacement_menu=0,
		position_fixe=1,      // permet d'‚liminer le sintillement de la barre du menu
		tmp=0,
		nbr_nom=0;

		struct agenda
		{
			char nom[50];
			char prenom[30];
			char adresse[60];
			char ville[50];
			char code_postal[15];
			char telephone[25];
			char contact[80];
		};
			agenda agenda_elec[5];


void main(void)
{
	menu_principal();
}

void menu_principal()
{
		int valeur_de_retour=0;
		CLS;
		init_souris();
//		init_limite_souris();
		entete();  // page de presentation simple
		titre_menu(" Menu Principal "); // place le titre au centre du cadre , partie du haut ÉÍÍ> titre <ÍÍ»
		montre_souris();
		valeur_de_retour=gerer_menu(4,"Saisir de nouveau noms"
									 ,"Visualiser les noms"
									 ,"Gestion des fichiers"
									 ,"  Quitter l'agenda "
									 ,"Gestion des noms , Nouveau, effacer ..."
									 ,"Affichage des noms presents"
									 ,"Gestion de la sauvegarde des fichiers et de leur chargement"
									 ,"Quitte l'agenda et retourne au systeme d'exploitation MS-DOS"
									 ,YELLOW,BLUE,LIGHTGRAY);

		if (valeur_de_retour==1) saisir_fiches();
		if (valeur_de_retour==2) visualiser();
		if (valeur_de_retour==3) gestion_fichier();
		if (valeur_de_retour==4) quitter_agenda();

}

void saisir_fiches()
{   char touche=0,choix_menu=0;
		CLS;
		cache_souris();
		decor_fond();
		//fenetre(5,3,75,19,LIGHTGRAY);
		textbackground(BLUE);
		gotoxy(5,3);SPACE(70);
		gotoxy(12,3);textcolor(WHITE);
		cprintf(" Nombre de Saisie effectu‚e %d ",nbr_nom);
		textcolor(BLACK);textbackground(LIGHTGRAY);
		gotoxy(7,5);cprintf("Nom :");
		gotoxy(7,7);cprintf("Prenom :");
		gotoxy(7,9);cprintf("Ville & adresse :");
		gotoxy(7,11);cprintf("Code postale de la ville :");
		gotoxy(7,13);cprintf("Telephone : ");
		gotoxy(7,15);cprintf("Contact :");
		textcolor(WHITE);textbackground(RED);
		gotoxy(10,18);cprintf(" Saisir noms ");
		gotoxy(52,18);cprintf(" Retour MENU ");
		do
		{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();
		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==18)&&(valeur_xxreel<23)&&(valeur_xxreel>9))   choix_menu=1;
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==18)&&(valeur_xxreel<65)&&(valeur_xxreel>51))  menu_principal();
		if  (bouton==BOUTON_DROIT) cadre_aide(SAISIR_CHAINE); // aide sur le maniment du programme

		}
		while(choix_menu==0);

			if (choix_menu==1)	{
					cache_souris();
					_setcursortype(_SOLIDCURSOR);
						do
						{
						// efface les anciens affichages .....
						textbackground(BLUE);gotoxy(5,3);SPACE(71);
						gotoxy(12,3);textcolor(WHITE);cprintf(" Nombre de Saisie effectu‚e %d ",nbr_nom);
						fond_saisie;gotoxy(7,18);SPACE(60);
						for(int i=0;i<12;i=i+2) 	{	gotoxy(7,6+i); SPACE(65); }
						// saisie des noms
						fond_saisie;saisie(9,6,50,agenda_elec[nbr_nom].nom);
						fond_saisie;saisie(9,8,50,agenda_elec[nbr_nom].prenom);
						fond_saisie;saisie(9,10,50,agenda_elec[nbr_nom].adresse);
						fond_saisie;saisie(9,12,50,agenda_elec[nbr_nom].code_postal);
						fond_saisie;saisie(9,14,50,agenda_elec[nbr_nom].telephone);
						fond_saisie;saisie(9,16,50,agenda_elec[nbr_nom].contact); // si contact = rien alors faire =PAS DE CONTACT
						textcolor(12);gotoxy(8,18);cprintf("C");textcolor(BLACK);cprintf("ontinuer la saisie - Autre touche pour finir");
						touche=toupper(getch());
						// increment de la variable POUR LES NOMS SUIVANTS
						nbr_nom++; //
						}
						while(touche=='C');
				}
					menu_principal();
}
void visualiser()
{
	char trouver[100],recherche[100]={0};
	int valeur_de_retour=0;
	int nbr_trouve=0,aux=0,l=0,choix_menu;
	cache_souris();
	//	decor_fond();	entete();  // page de presentation simple
	cadre_menu();
	titre_menu(" Visualisation "); // place le titre au centre du cadre , partie du haut ÉÍÍ> titre <ÍÍ»
	valeur_de_retour=0;

	valeur_de_retour=gerer_menu(4,"Recherche un nom","Recherche une Ville","Recherche un code postal","Retour Menu","Vous recherchez par le nom","Vous recherchez par la ville","Vous recherchez par le code postal de la ville","Vous retournez au menu precedent "
								,YELLOW,BLUE,LIGHTGRAY);

	cache_souris();
	for(int m=0;m<100;m++) recherche[m]=0;
	l=0; // initialise la variable l, cause probleme dans la m‚moire, … caus‚ parfois des reboots (?????)
	if (valeur_de_retour==4) menu_principal();
	cadre_plein(10,3,70,22,1,BLUE,LIGHTGRAY,1);
	titre(15,5,YELLOW,BLUE,LIGHTGRAY,"Recherche d'un ‚l‚ment");
//	fond_saisie;
	locatext(18,7,"Cette  boŒte  de saisie permet de recherche un",31);
	locatext(14,8,"‚lement, comme par exemple un nom, pr‚nom, une ville",31);
	locatext(14,9,"Le principe  de  la  recherche  consiste …  comparer",31);
	locatext(14,10,"votre ‚lement … celui stock‚ en m‚moire, que se soit",31);
	locatext(14,11,"un nom, pr‚nom ou autre. Si votre ‚lement n'est  pas",31);
	locatext(14,12,"trouv‚, un boite de dialogue  vous demandera si vous",31);
	locatext(14,13,"souhaitez continuer .",31);



	if (valeur_de_retour==1)	{
		textcolor(LIGHTRED);
		titre(15,16,WHITE,RED,LIGHTGRAY,"Nom >                                         ");
		FOND_SAISIE_CHAINE;
		saisie(21,16,39,recherche);
		nbr_trouve=0;
			  for(int i=0;i<100;i++) {
					if (strcmp(recherche,agenda_elec[i].nom)==0) {
						trouver[nbr_trouve]=i;nbr_trouve++;
					}
			  }
	}

	if (valeur_de_retour==2)	{
		cache_souris();
		titre(15,16,WHITE,RED,LIGHTGRAY,"Ville >                                        ");
		FOND_SAISIE_CHAINE;saisie(23,16,39,recherche);nbr_trouve=0;
			  for(int i=0;i<100;i++) {
					if (strcmp(recherche,agenda_elec[i].ville)==0) {
					  trouver[nbr_trouve]=i;nbr_trouve++;
					}
			  }
	}
	if (valeur_de_retour==3)	{
		cache_souris();
		titre(15,16,WHITE,RED,LIGHTGRAY,"Code >                                        ");
		FOND_SAISIE_CHAINE;saisie(22,16,39,recherche);nbr_trouve=0;
			  for(int i=0;i<100;i++) {
					if (strcmp(recherche,agenda_elec[i].code_postal)==0) {
					  trouver[nbr_trouve]=i;nbr_trouve++;
					}
			  }
	}
	if (nbr_trouve==0)	valeur_de_retour=4;
	cadre_plein(10,3,70,22,2,BLUE,LIGHTGRAY,1);
	while(l<nbr_trouve)		{	//	for (int l=0;l<nbr_trouve;l++)
		aux=trouver[l];
		textcolor(BLACK);
		titre(12,5,YELLOW,GREEN,LIGHTGRAY, "Nom >                                                 ");		FOND_VISU;gotoxy(18,5);cprintf("%s",agenda_elec[aux].nom);
		titre(12,7,YELLOW,GREEN,LIGHTGRAY, "Prenom >                                              ");		FOND_VISU;gotoxy(21,7);cprintf("%s",agenda_elec[aux].prenom);
		titre(12,9,YELLOW,GREEN,LIGHTGRAY, "ville  >                                              ");		FOND_VISU;gotoxy(21,9);cprintf("%s",agenda_elec[aux].adresse);
		titre(12,11,YELLOW,GREEN,LIGHTGRAY,"code >                                                ");		FOND_VISU;gotoxy(19,11);cprintf("%s",agenda_elec[aux].code_postal);
		titre(12,13,YELLOW,GREEN,LIGHTGRAY,"telephone >                                           ");		FOND_VISU;gotoxy(24,13);cprintf("%s",agenda_elec[aux].telephone);
		titre(12,15,YELLOW,GREEN,LIGHTGRAY,"contact >                                             ");		FOND_VISU;gotoxy(22,15);cprintf("%s",agenda_elec[aux].contact);
		titre(18,19,WHITE,RED,LIGHTGRAY,"Vers le haut");
		titre(46,19,WHITE,RED,LIGHTGRAY,"Vers le bas");
		choix_menu=0;
		do
		{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();
		gotoxy(1,1);cprintf("%d - %d - %d ",(posx/8+1),(posy/8+1),bouton);
		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==19)&&(valeur_xxreel<31)&&(valeur_xxreel>18)) choix_menu=1;
		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel==19)&&(valeur_xxreel<58)&&(valeur_xxreel>46)) choix_menu=2;
		if  (bouton==BOUTON_DROIT) menu_principal(); // aide sur le maniment du programme
		}
		while(choix_menu==0);
		if (choix_menu==1) {
			if (l<100) l++;
		}
		if (choix_menu==2) {
			if (l>0) l--;
		}

//		pause();
	}
	menu_principal();
}


// Partie aide simple pour l'utilisation et REMARQUE ...
void cadre_aide(int num_aide)
{   char sauve_ecran1[4096];
	char texte_aide[10][80];

	cache_souris();
	gettext(1,1,80,25,sauve_ecran1);
	cadre_plein(4,4,74,18,1,WHITE,BLUE,1);
	textcolor(YELLOW);
	gotoxy(10,4);
	cprintf(" Aide sur les principales commandes ");
	textcolor (WHITE);
	gotoxy(6,5);
	cprintf("-------------------------------------------------------------------");
	textcolor(LIGHTGRAY);
	if (num_aide==MENU_PRINCIPAL) 	{ // texte pour le menu principal
					strcpy(texte_aide[1],"    Vous vous trouvez dans le MENU PRINCIPAL de l'agenda");
					strcpy(texte_aide[2],"‚lectronique, cliquez … l'aide de la souris sur l'une des barres");
					strcpy(texte_aide[3],"d‚sir‚es avec le bouton gauche.");
					strcpy(texte_aide[4],"");
					strcpy(texte_aide[5],"        Remarque : le programme AGENDATM a ‚t‚ ecrit pour ne ");
					strcpy(texte_aide[6],"fonctionner qu'avec des souris … deux boutons ou comme dans ");
					strcpy(texte_aide[7],"dans la plupart des cas sur une souris 3 boutons fonctionnant");
					strcpy(texte_aide[8],"en MODE 2 boutons. Un interrupteur souvent plac‚ en dessous");
					strcpy(texte_aide[9],"doit se trouver sur le MODE 2 [   (2)<<<-  >>>3   ]");
	}
	if (num_aide==SAISIR_CHAINE) 	{// texte pour le menu principal
					strcpy(texte_aide[1]," La Saisie vous permet de stocker des noms,prenoms,adresses...");
					strcpy(texte_aide[2],"Mais la saisie est limit‚ par une longueur pr‚-definie, ce qui");
					strcpy(texte_aide[3],"correspond par exemple … 50 lettres pour le nom. Une fois la");
					strcpy(texte_aide[4],"saisie termin‚e, l'agenda vous demandera si vous souhaitez");
					strcpy(texte_aide[5]," entrer un autre nouveau nom ,pour cela pressez au clavier");
					strcpy(texte_aide[6],"la lettre (  C  ) ");
					strcpy(texte_aide[7],"Remarque : les num‚ros de t‚l‚phone peuvent contenir ( ) et - ");
					strcpy(texte_aide[8],"comme par exemple > (179)-42-12-34-56 (longeur 25 caracteres)");
					strcpy(texte_aide[9],"");
	}
		for (int i=0;i<10;i++)	{ gotoxy(9,6+i);cprintf("%s",texte_aide[i]); }
	getch();
	puttext(1,1,80,25,sauve_ecran1);
}
void gestion_fichier()
{
	int nbr_fichier,nbr_repertoire;
	int choix_menu;
	int place_r,place_f;

	cache_souris();
	decor_fond();
	color(BLACK,CYAN);gotoxy(1,2);SPACE(80);
	color(BLACK,BROWN);gotoxy(1,3);SPACE(80);
	bar_menu(1,2,YELLOW,CYAN,RED,"   _Sauvegarder   _Charger   _Option   _Quitter");

	debut_traitement(10,10);

//	getcwd(buffer_path, MAXPATH);		strcpy(rep_courant,buffer_path);		printf("The current directory is: %s\n",rep_courant);		PAUSE;
			nbr_fichier=recherche_fichier("*.*");
			nbr_repertoire=recherche_repertoire("*.*");
	fin_traitement();

	cadre_plein(2,5,20,22,0,LIGHTGRAY,BLUE,1);
	cadre_plein(23,5,78,22,0,LIGHTGRAY,BLUE,1);

	locatext(3,3," A: ",31);locatext(8,3," B: ",31);locatext(13,3," C: ",31);
	color(WHITE,BROWN);gotoxy(32,3);

		if (nbr_repertoire>1)
			 cprintf("%d Repertoires ",nbr_repertoire);
			else
			 cprintf("%d Repertoire ",nbr_repertoire);
	gotoxy(52,3);
		if (nbr_fichier>1)
			cprintf("%d Fichiers",nbr_fichier);
		   else
			cprintf("%d Fichier ",nbr_fichier);

	for(int t=0;t<16;t++)
	{	locatext(4,6+t,num_repertoire[t].repertoire,31);
	}
	for(int m=0;m<16;m++)
	{		locatext(26,6+m,num_fichier[m].files,31);
			if (num_fichier[m].taille>0)
			{
				gotoxy(50,6+m);color(YELLOW,BLUE);cprintf("%u",num_fichier[m].taille);
				if (num_fichier[m].attribut==32)	locatext(65,6+m,"A.",31);
				if (num_fichier[m].attribut==1)		locatext(65,6+m,".R",31);
				if (num_fichier[m].attribut==33)	locatext(65,6+m,"AR",31);
			}
	}
// initialisation des variables
		choix_menu=0;
		place_r=0;
		place_f=0;
		do
		{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();

		gotoxy(1,1);cprintf("%d - %d - %d ",(posx/8+1),(posy/8+1),bouton);

		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel>5)&&(valeur_yyreel<22)&&(valeur_xxreel<20)&&(valeur_xxreel>2))
		{       cache_souris();
					for(int e=0;e<16;e++)
					{
						locatext(4,6+e,num_repertoire[place_r+e].repertoire,31);
					}
					locatext(4,valeur_yyreel,num_repertoire[place_r+(valeur_yyreel-6)].repertoire,79);
				montre_souris();
		}

		if ((bouton==BOUTON_GAUCHE)&&(valeur_yyreel>5)&&(valeur_yyreel<22)&&(valeur_xxreel<78)&&(valeur_xxreel>23))
		{
			cache_souris();
				for(int h=0;h<16;h++)
					{
						locatext(26,6+h,num_fichier[place_f+h].files,31);
					}
			locatext(26,valeur_yyreel,num_fichier[place_f+(valeur_yyreel-6)].files,79);
			montre_souris();

		}
		if  (bouton==BOUTON_DROIT) menu_principal(); // aide sur le maniment du programme
		}
		while(choix_menu==0);

//        NOTE  : MET LES BOUTONS POUR place_r et place_f et fin du cliniotement
//
	BEEP;
	PAUSE;
	END;

}
void quitter_agenda()
{       int valeur_de_retour=0;
		init_souris();
		cadre_menu();
		titre_menu(" QUITTE L'AGENDA "); // place le titre au centre du cadre , partie du haut ÉÍÍ> titre <ÍÍ»
		montre_souris();
		valeur_de_retour=gerer_menu(2,
									"Retour au MENU Principal",
									"     QUITTER ..!!!! ",
									"",
									"",
									" Vous retournez au menu principal ..... ",
									" Vous QUITTEZ l'agenda pour retourner au systeme d'exploitation MS-DOS",
									"",
									"",
									YELLOW,BLUE,LIGHTGRAY
									);

		if (valeur_de_retour==1) menu_principal();
		if (valeur_de_retour==2) { cache_souris();CLS;exit(EXIT_SUCCESS); }
}