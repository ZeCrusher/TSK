#include <stdio.h>
#include <conio.h>
#include <bios.h>

//


void clavier(int touche_haut,int touche_bas,int touche_gauche,int touche_droite,int variable_de_controle, int borne_haut,int borne_bas);

void main(void)
{
	 int tmp;

	 clavier(72,80,0,0,tmp,0,100);


}
void clavier(int haut,int bas,int gauche,int droite,int variable_de_controle)
{
	static int touche_clavier=0,clavier_h=0;

	if (bioskey(1)!=0)
	{
		touche_clavier=toupper(getch());
	if (touche_clavier==RETURN) choix_menu=(clavier_h+deca+1);
	if (touche_clavier==ECHAP)  choix_menu=PAS_DE_CHOIX;

		if (clavier=='\x0') // test une touche HIGHT ' 0 + le code ASCII '
		{	clavier=getch();
			// test des touches fl‚che
			if (clavier==80)     // hauteur -2 correspond … la hauteur - 'Í 'du bas et 'Í" du haut ( Í barre du cadre )
			{   if (clavier_h<(hauteur-2)) {
				clavier_h++;
				// ici je fais croire que la souris c'est d‚plac‚e
				position_fixe=val=clavier_h;
				}
				else   	 // empˆche de d‚passer la limite
				{	if (deca<(nbr_de_barre-hauteur))
					{	deca++;
					}
				}
			}
			if (clavier==72)
			{  if ((clavier_h>0))
			   { clavier_h--;
				position_fixe=val=clavier_h;
			   }	// idem ici je fais croire aussi que la souris c'est d‚plac‚e
			   else
			   {	if (deca>0) deca--;
			   }

			}     // ==

			// deca pour l'assenceur vertical
			// Contrairement … la souris il faut r‚afficher toute les barres
			// car un saut … la derniere barre par exemple n'est pas possible
		for (int marj=0;marj<(hauteur-1);marj++) // hauteur-1 pour soustraire le cadre du bas si on d‚mare a x+1
		{	color(couleur_texte,couleur_cadre_fond);
			gotoxy(x+1,y+1+marj);	SPACE(largeur-1);
			bar_menu(x+1,y+marj+1,couleur_texte,couleur_cadre_fond,lettre,string[marj+deca]);
		}
		color(couleur_barre_ecriture,couleur_barre_fond);
		gotoxy(x+1,y+clavier_h+1);	SPACE(largeur-1); // SPACE est utilis‚ pour effacer l'enplacement de la derniere barre courante
		bar_menu(x+1,y+clavier_h+1,couleur_barre_ecriture,couleur_barre_fond,lettre,string[clavier_h+deca]);
		assenceur_vertical_menu_der(x,y,hauteur,largeur,nbr_de_barre,val,deca,deplacement,couleur_cadre_ecriture,couleur_cadre_fond);
		}

	}



}
