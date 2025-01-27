/*   FLED version 1.00 (c)   TSAKI_
 Utilitaire
 R‚alis‚ le: 		20/05/1995
 DŠrniŠre modif: 	29/06/95
 Programmation : 	Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme
 comme fonction
*/
#include <dos.h>

#ifndef MK_FP  // MK_FP est-il d‚fini ?
#define MK_FP(seg, ofs)  ((void far *) ((unsigned long) (seg)<<16|(ofs)))
#endif

// BIOS_KBF cr‚e un pointeur sur l'indicateur du clavier
#define BIOS_KBF ((unsigned far *) MK_FP(0x40, 0x17))
#define SCRL  16            // Bit Scroll Lock
#define NUML  32            // Bit Num-Lock
#define CAPL  64            // Bit Caps-Lock
#define INS  128            // Bit Insert

void eteint_led(unsigned flag);
void allume_led(unsigned flag);

// Test void main void
//*
void main(void)
{
	allume_led(NUML);
	allume_led(SCRL);
	allume_led(CAPL | SCRL | NUML);
}
//*/
void allume_led( unsigned flag )
{
 union REGS regs;              // M‚morise le contenu des registres
 * BIOS_KBF|= flag;           // Met … 1 les bits indiqu‚s
 regs.h.ah = 1;  			   // Num‚ro de la fonction : caractŠre disponible ?
 int86(0x16, &regs, &regs);    // D‚clenche l'interruption du BIOS
}
void eteint_led(unsigned flag)
{
 union REGS regs;              // M‚morise le contenu des registres
//            ÚÄÄ Chaque bit … 0 est arm‚ (mis … 1) et chaque bit … 1 est mis … 0.
 *BIOS_KBF &= ~flag;           // Met … 0 les bits indiqu‚s
 regs.h.ah = 1;     		   // Num‚ro de la fonction : caractŠre disponible ?
 int86(0x16, &regs, &regs);    // D‚clenche l'interruption du BIOS
}

