int gerer_menu(int nbr_de_barre,char texte_1[30], char texte_2[30], char texte_3[30], char texte_4[30], char aide_texte_1[80], char aide_texte_2[80], char aide_texte_3[80], char aide_texte_4[80], char couleur_texte, char couleur_fond, char couleur_ombre_fond)
{
	// ici gerer_menu utilise une autre fonction menu(nbr_de_barre,texte_1,texte_2,texte_3,texte_4)
	// emplacement_menu , qui s'appelle position_fixe dans la veille version
	// … pour but de d'‚viter de redessiner la barre du menu en cour
	// et ainsi empecher le clignotement .....

	int val_y[4]={0},fin_de_boucle=0,emplacement_menu=0;
	int valeur_de_retour=0;
	menu(nbr_de_barre,texte_1,texte_2,texte_3,texte_4,couleur_texte,couleur_fond,couleur_ombre_fond);
	for(int k=0;k<3;k++)	val_y[k]=-1; // initialisation de la variable VAL_Y
	// position des differentes barres stocker dans la variable val_y[ù]
	// Valeur pr‚calcul‚
	if (nbr_de_barre==1) { val_y[1]=11-1; }
	if (nbr_de_barre==2) { val_y[1]=7-1;val_y[2]=14-1; }
	if (nbr_de_barre==3) { val_y[1]=6-1;val_y[2]=11-1;val_y[3]=16-1; }
	if (nbr_de_barre==4) { val_y[1]=5-1;val_y[2]=9-1;val_y[3]=13-1;val_y[4]=17-1; }
	init_souris();
	do
	{
		montre_souris();
		bouton = ZERO_BOUTON_APPUYER ; // indique qu'aucun bouton n'est appuyer
		etat_souris();
		//gotoxy(1,1);printf("%d - %d - %d ",(posx/8+1),(posy/8+1),bouton);
		//gotoxy(2,2);printf("empl <%d> -val_y[1] <%d> -val_y[0] <%d> ",emplacement_menu,val_y[1],val_y[0]);

		valeur_xxreel=((posx/8)+1);
		valeur_yyreel=((posy/8)+1);


		if ((val_y[1]!=-1)&&(emplacement_menu!=1)&&( valeur_yyreel<(val_y[1]+4)) && (valeur_yyreel>(val_y[1])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)) )
		{
			cache_souris();
			menu(nbr_de_barre,texte_1,texte_2,texte_3,texte_4,couleur_texte,couleur_fond,couleur_ombre_fond);
			menu_sous_mouse(nbr_de_barre,1,texte_1,aide_texte_1,couleur_ombre_fond);
			emplacement_menu=1;
		}
		if ((bouton==1) && (emplacement_menu==1) && (valeur_yyreel<(val_y[1]+4)) && (valeur_yyreel>(val_y[1])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)))
		{	valeur_de_retour=1;fin_de_boucle=1;
		}

		if ((emplacement_menu!=2)&&( valeur_yyreel<(val_y[2]+4)) && (valeur_yyreel>(val_y[2])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)) )
		{
			cache_souris();
			menu(nbr_de_barre,texte_1,texte_2,texte_3,texte_4,couleur_texte,couleur_fond, couleur_ombre_fond);
			menu_sous_mouse(nbr_de_barre,2,texte_2,aide_texte_2,couleur_ombre_fond);
			emplacement_menu=2;
		}
		if ((bouton==1) && (emplacement_menu==2) && (valeur_yyreel<(val_y[2]+4)) && (valeur_yyreel>(val_y[2])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)))
		{	valeur_de_retour=2;fin_de_boucle=1;
		}
		if ((nbr_de_barre>2)&&(emplacement_menu!=3)&&( valeur_yyreel<(val_y[3]+4)) && (valeur_yyreel>(val_y[3])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)) )
		{ cache_souris();
			menu(nbr_de_barre,texte_1,texte_2,texte_3,texte_4,couleur_texte,couleur_fond,couleur_ombre_fond);
			menu_sous_mouse(nbr_de_barre,3,texte_3,aide_texte_3,couleur_ombre_fond);
			emplacement_menu=3;
		}
		if ((bouton==1) && (emplacement_menu==3) && (valeur_yyreel<(val_y[3]+4)) && (valeur_yyreel>(val_y[3])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)))
		{	valeur_de_retour=3;fin_de_boucle=1;
		}
		if ((nbr_de_barre==4)&&(emplacement_menu!=4)&&(valeur_yyreel<(val_y[4]+4)) && (valeur_yyreel>(val_y[4])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)) )
		{
			cache_souris();
			menu(nbr_de_barre,texte_1,texte_2,texte_3,texte_4,couleur_texte,couleur_fond,couleur_ombre_fond);
			menu_sous_mouse(nbr_de_barre,4,texte_4,aide_texte_4,couleur_ombre_fond);
			emplacement_menu=4;
		}

		if ((bouton==1) && (emplacement_menu==4) && (valeur_yyreel<(val_y[4]+4)) && (valeur_yyreel>(val_y[4])) && ((valeur_xxreel<59)&&(valeur_xxreel>21)))   {
			valeur_de_retour=4;fin_de_boucle=1;
		}

	//	if (bouton==2) cadre_aide(0); // aide sur le maniment du programme

	}
	while(fin_de_boucle!=1);
			return (valeur_de_retour);
}
void menu(int nbr_de_barre,char texte_1[],char texte_2[],char texte_3[],char texte_4[],char couleur_texte,char couleur_fond,char couleur_ombre_fond)
{
	espace=ceil((LONGUEUR_DU_CADRE-(3*nbr_de_barre))/(nbr_de_barre+1));
	x=espace; // calcul de l'espace entre les differents cadres + Centrage du menu pour barre < 2

	if (nbr_de_barre==2)	{
		centrage=-1;  // permet de centrer le MENU si il n'y a
	}                 // deux barres dans le menu ....
	else              // centrage a pour seul effet de monter la
	{                 // barre d'une ligne vers le Haut
		centrage=0;
	}
		 for (int i=1;i<(nbr_de_barre+1);i++)
		 {
			textbackground(1);textcolor(YELLOW);
			window(22,4+x+centrage,58,6+x+centrage);
			clrscr();
			textbackground(LIGHTGRAY);textcolor(DARKGRAY);
			window(1,1,80,25);
			gotoxy(30,5+x+centrage);
			if (i==1) { textbackground(couleur_fond);textcolor(couleur_texte);cprintf("%s",texte_1); }//puts(texte_1); // Remarque :
			if (i==2) { textbackground(couleur_fond);textcolor(couleur_texte);cprintf("%s",texte_2); }//puts(texte_2); //
			if (i==3) { textbackground(couleur_fond);textcolor(couleur_texte);cprintf("%s",texte_3); }//puts(texte_3); //
			if (i==4) { textbackground(couleur_fond);textcolor(couleur_texte);cprintf("%s",texte_4); }//puts(texte_4); //
			textbackground(couleur_ombre_fond);textcolor(DARKGRAY);
			gotoxy(23,x+7+centrage);cprintf("ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß");
			gotoxy(59,x+6+centrage);cprintf("Û");
			gotoxy(59,x+5+centrage);cprintf("Û");
			gotoxy(59,x+4+centrage);cprintf("Ü");
			// incr‚ment
			x=x+(espace+3);
			window(1,1,80,25);
			}
}
void menu_sous_mouse(int nbr_de_barre,int numeroe_de_la_barre,char phrase_1[30],char aide[80],char couleur_ombre_fond)
{
	// calcul de l'espace entre les differents cadres + Centrage du menu pour barre < 2
	espace=ceil((LONGUEUR_DU_CADRE-(3*nbr_de_barre))/(nbr_de_barre+1));
	x=espace;
	if (nbr_de_barre==2)	{
		centrage=-1;  // permet de centrer le MENU si il n'y a
	}                 // deux barres dans le menu ....
	else              // centrage a pour seul effet de monter la
	{                 // barre d'une ligne vers le Haut
		centrage=0;
	}

	for (int i=1;i<(nbr_de_barre+1);i++)		 {
		if (i==numeroe_de_la_barre)
		{
			textbackground(RED);textcolor(WHITE);
			window(22,4+x+centrage,58,6+x+centrage);
			clrscr();
			window(1,1,80,25);
			gotoxy(30,5+x+centrage);
			textbackground(RED);textcolor(WHITE);cprintf("%s",phrase_1);
			textbackground(couleur_ombre_fond);textcolor(DARKGRAY);
			gotoxy(23,x+7+centrage);cprintf("ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß");
			gotoxy(59,x+6+centrage);cprintf("Û"); // dessin de l'ombre ASCII 223 220
			gotoxy(59,x+5+centrage);cprintf("Û");
			gotoxy(59,x+4+centrage);cprintf("Ü");
			window(1,1,80,25);
		}
			// incr‚ment
			x=x+(espace+3);
		 }
	gotoxy(1,24);
	for(int j=0;j<20;j++)
	{
	cprintf("    ");
	}
	gotoxy(1,24);cprintf("%s",aide);
}

