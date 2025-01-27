 #define __FRS232

#if !defined( __DOS_H )
 #include <dos.h>
 #define __DOS_H
#endif


#define REGISTRE_1   0x00 // Armement int‚ruptions (tout inhib‚)
#define REGISTRE_2   0x00
#define REGISTRE_3   0x03
#define REGISTRE_4   0x00
#define REGISTRE_5_5 0x20
#define REGISTRE_5_0 0x01
#define REGISTRE_6 	 0x00
#define REGISTRE_7 	 0x00
#define REGISTRE_8	 0x0C
#define REGISTRE_9	 0x00

#define COM1       0
#define COM2       1
#define OK         0
#define ERREUR     -1

#define COM1       0
#define COM2       1

#define ADR_COM1 0x3F8
#define ADR_COM2 0x2F8


void init_rs(int com_x,int initialise);
int test_rs(int com_x);
int lire_rs(int com_x);
void ecrire_rs(int com_x,char c);
void version(void);

int recevoir_reponse(char *buffer);
void init_com(int com);
char ecrire_com(int com,unsigned char valeur);
char lire_com(int com);


