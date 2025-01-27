/*   FASCII ver 1.00
 Utilitaire en Mode texte 80x25
 R‚alis‚ le: 16/03/1996
 DŠrniŠre modif: 16/03/96
 Programmation & conception: Tsakiropoulos Serge

 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
//*/
// Modifier … cause du projet .....
//	enum type_cadre { SIMPLE = 0, DOUBLE = 1, BARRE = 2, ETOILE = 3 };

typedef unsigned char byte;

void definition_ascii(byte table[16],byte ascii);
void init_ascii();
void table_ascii(void);
 int charger_table(char nom_police[80]);
void change_palette_texte(int n,char color);
