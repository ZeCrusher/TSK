// TSAKIROPOULOS SERGE

#define CLS textbackground(BLACK);clrscr();

void entete();
//void decor_fond();
void decor_simple();
void cadre_menu();


void entete()
{
	decor_fond();
	cadre_plein(10,3,70,22,1,WHITE,LIGHTGRAY,1);
}
void cadre_menu()
{
	cadre_plein(10,3,70,22,1,WHITE,LIGHTGRAY,1);
}

void decor_fond_()
{
	clrscr();
	_setcursortype(_NOCURSOR);  // supprime le curseur de l'ecran ..
	textcolor(WHITE);textbackground(LIGHTGRAY);
	for(int i1=0;i1<25;i1++) for(int i2=0;i2<5;i2++) cputs ("께께께께께께께께");
	textcolor(WHITE);textbackground(BLUE);
	gotoxy(1,25); 	for (int j=0;j<80;j++) cprintf(" ");
	gotoxy(1,1);	for (int i=1;i<81;i++) cprintf(" ");
}



