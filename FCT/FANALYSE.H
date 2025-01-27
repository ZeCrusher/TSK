#include <stdio.h>

	struct Msdosys {
		char win_commande[32];
		char commentaire[128];
		char type_donnee[32];
		char min[10];
		char max[10];
	};
	struct Msdosys option[50];
	struct Msdosys path[50];

int analyse_table(void)
