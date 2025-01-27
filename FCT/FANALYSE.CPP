#include <stdio.h>
#include <stdlib.h> // pour : exit


 #define ON			1

#if !defined( __FCADRE )
 #include "c:\tsk\fct\fcadre.h"
 #define __FCADRE
#endif

////////////////////////// FCADRE  /////////////////////////////////////
extern void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
extern void locatcar(char x,char y,char chaine,char attribut);
extern void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
extern void modif_fond(char x,char y,int longueur,char attribut,char type);
extern int strdecoupe(byte  *texte_source ,byte  *texte_objet,int debut,int fin); // prend une partie de la chaŒne source et la copie dans objet

int analyser_ligne(char ligne[128],char commande[32],char type[20],char min[10],char max[10],char commentaire[128]);

	struct Msdosys {
		char win_commande[32];
		char commentaire[128];
		char type_donnee[32];
		char min[10];
		char max[10];
	};
	extern struct Msdosys option[50];
	extern struct Msdosys path[50];

	int cpt_option=0,cpt_path=0;

int analyse_table(void)
{
	FILE *in;
	char msg[129];
	char buffer[310]; //  = ( 68 - 23 ) * ( 17 - 15 ) * 2 Voir CADRE_PLEIN ci-dessous
	char commande[64];  // commande cr‚e par le User .
	char comment[128]; // Pour les commentaires de l utilisateur … propos de la commande .
	char min[10]={0},max[10]={0}; // si il y a un type decimal_option ou decimal_path

	char type_com[20]={0};

	int nbr_commentaire=0;
	int errors=0,val=0;

	gettext(23,15, 60,18, buffer); // Sauvegarde de l'ecran Outwin

//	cadre_plein(23,15,58,17,SIMPLE,15,7,1);      // dessine le cadre
//	locatext(25,15," Analyse du fichier Table.out ",0+16*7);

	if ((in = fopen("c:\\TSK\\table.out", "rt"))== NULL)
	{
	   fclose(in);
	   return 1;
	}

	do
	{
		fgets(msg,128,in);
		val=analyser_ligne(msg,commande,type_com,min,max,comment);
		if (val!=1) {
			if ((strcmpi(type_com,"decimal_option")==0)||(strcmpi(type_com,"lecteur_option")==0)||(strcmpi(type_com,"fichier_option")==0)||(strcmpi(type_com,"Texte_Option")==0)||(strcmpi(type_com,"binaire_Option")==0)) {
				strcpy(option[cpt_option].win_commande,commande);
				strcpy(option[cpt_option].type_donnee,type_com);
				strcpy(option[cpt_option].min,min);
				strcpy(option[cpt_option].max,max);
				strcpy(option[cpt_option].commentaire,comment);
				cpt_option++; // incrementation du compteur pour la structure.
			}
			if ((strcmpi(type_com,"decimal_path")==0)||(strcmpi(type_com,"lecteur_path")==0)||(strcmpi(type_com,"fichier_path")==0)||(strcmpi(type_com,"Texte_path")==0)||(strcmpi(type_com,"binaire_path")==0)) {
				strcpy(path[cpt_path].win_commande,commande);
				strcpy(path[cpt_path].type_donnee,type_com);
				strcpy(path[cpt_path].min,min);
				strcpy(path[cpt_path].max,max);
				strcpy(path[cpt_path].commentaire,comment);
				cpt_path++;// idem que Option
			}
		}
	}
	while(!feof(in));


	puttext(23, 15, 60, 18, buffer); // Sauvegarde de l'ecran Outwin
//  exit(0);

  return(0);

}
//int analyser_ligne(char ligne[128],char *commande[32],char *type,char *min[10],char *max[10])
int analyser_ligne(char ligne[128],char commande[32],char type[20],char min[10],char max[10],char commentaire[128])
{
	int taille=0,pvirgule=0,espace=0;
	char format[11]={'[',']','=',44,'(','-',')','"','"',';'};
	// [commande]=Texte,

	strcpy(commande,0);

	int emplacement[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	if ((taille=strlen(ligne))>128) taille=128;

	for (int i=0;i<taille-1;i++)	{ /////////////// for //////////////////////////////////////////////
		if (ligne[i]==';') pvirgule=1;
		if (ligne[i]==' ') espace++;
		if ((ligne[i]=='/')&&(ligne[i+1]=='/')) { // commentaire trouv‚
			if ((espace!=i)&&(pvirgule!=1)) {	  // Il y a t-il des chars autre que ' ' (0x20) devant et pas de ; devant
				return(0);						  // Erreur
			}
				return(1);                        // OK la ligne est un commentaire
		}
	}
	for (int j=0;j<taille;j++) 	{
		for (int a=0;a<10;a++) 		{ // Nombre de caractere , [ ] = ( ) , " " ;
			if (ligne[j]==format[a]) {
				emplacement[a]=j;
			}
		}
	}
	//0 ='[',1=']',2='=',3=44 , 4 ='(','-',')','"','"',';'};
	delay(10);
	if (emplacement[0]==-1)	return(1); 	//ici il y a une erreur car pas de [ trouver dans la ligne du fichier
	strdecoupe(ligne,commande,emplacement[0]+1,emplacement[1]);
	strdecoupe(ligne,type,emplacement[2]+1,emplacement[3]);
	if (type[0]=='d')
		strdecoupe(ligne,type,emplacement[2]+1,emplacement[4]);
	if (emplacement[4]!=-1)
		strdecoupe(ligne,min,emplacement[4]+1,emplacement[5]);
	if (emplacement[6]!=-1)
		strdecoupe(ligne,max,emplacement[5]+1,emplacement[6]);
	if (emplacement[7]!=-1)
		strdecoupe(ligne,max,emplacement[7]+1,emplacement[8]);
	return(0);
}
