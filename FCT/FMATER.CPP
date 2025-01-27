/*
	FMATER ver 1.06

 R‚alis‚ le: 01/06/1995
 DŠrniŠre modif: 29/06/95
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme comme fonction
*/

#if !defined( __BIOS_H )
#include <bios.h>
#define __BIOS_H
#endif

unsigned int taille_cluster(void);
char co_pro(void);
int ram_conv(void);
int Detect_Carte_Son(void);

void main(void)
{
	Detect_Carte_Son();
}

/*
;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³Detect Sound Card   Detect with the environment variable the sound        ³
;³                    card installed                                        ³
;³                                                                          ³
;³In :                                                                      ³
;³        AH = Detect_Sound_Card   > 0x30                                   ³
;³        CX = 1  Display result of Searching                               ³
;³                                                                          ³
;³Out :                                                                     ³
;³        AX = 0  No_Card                                                   ³
;³           = 1  Sound Blaster 1.0                                         ³
;³           = 2  Sound Blaster 1.5                                         ³
;³           = 3  Sound Blaster 2.0                                         ³
;³           = 4  Sound Blaster Pro                                         ³
;³           = 5  Sound Blaster 16                                          ³
;³           = 6  Sound Blaster Awe 32                                      ³
;³           = 10h  Gus                                                     ³
;³           = 11h  Gus Max                                                 ³
;³           = 12h  Gus Ace                                                 ³
;³           = 13h  Gus Pnp                                                 ³
;³           = 20h  WSS                                                     ³
;³        BX = Port                                                         ³
;³        CX = Irq                                                          ³
;³        DX = Dma                                                          ³
;³        SI = Dsp Version (For Sb) ou                                      ³
;³             Size of RAM of the Gravis                                    ³
;³                                                                          ³
;³Other Registers Change : None                                             ³
;³                                                                          ³
;³                                                                          ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
*/
int Detect_Carte_Son(void)
{
	union REGS regs;

	regs.h.ah = 0x30;
	regs.x.cx = 0x01;

	int86(, &regs, &regs);

	printf(" type %d ",regs.x.ax);
	printf(" Port %d ",regs.x.bx);
	printf(" irq  %d ",regs.x.cx);

	return(0);

}

char co_pro(void)
{
		equip_check = biosequip();

		if (equip_check&0x0002 )  // 0x0002 => CO_PRO
		{
			return(1); // present
		}
		else
		{
			return(-1);
		}
}
int ram_conv(void)
{
   return( biosmemory() );
}
unsigned int taille_cluster(void)
{
	unsigned int SecteursParCluster;
	unsigned int BytesParSecteur;

	/* Obtient la taille des clusters */
	asm {
		mov ah, 36h
		int 21h
		mov SecteursParCluster, ax
		mov BytesParSecteur, cx
	}

	return(SecteursParCluster* BytesParSecteur);
}
