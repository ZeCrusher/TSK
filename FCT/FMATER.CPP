/*
	FMATER ver 1.06

 R�alis� le: 01/06/1995
 D�rni�re modif: 29/06/95
 Programmation & conception: Tsakiropoulos Serge
 Ce PROGRAMME peut �tre utilis� dans un autre programme comme fonction
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
;��������������������������������������������������������������������������Ŀ
;�Detect Sound Card   Detect with the environment variable the sound        �
;�                    card installed                                        �
;�                                                                          �
;�In :                                                                      �
;�        AH = Detect_Sound_Card   > 0x30                                   �
;�        CX = 1  Display result of Searching                               �
;�                                                                          �
;�Out :                                                                     �
;�        AX = 0  No_Card                                                   �
;�           = 1  Sound Blaster 1.0                                         �
;�           = 2  Sound Blaster 1.5                                         �
;�           = 3  Sound Blaster 2.0                                         �
;�           = 4  Sound Blaster Pro                                         �
;�           = 5  Sound Blaster 16                                          �
;�           = 6  Sound Blaster Awe 32                                      �
;�           = 10h  Gus                                                     �
;�           = 11h  Gus Max                                                 �
;�           = 12h  Gus Ace                                                 �
;�           = 13h  Gus Pnp                                                 �
;�           = 20h  WSS                                                     �
;�        BX = Port                                                         �
;�        CX = Irq                                                          �
;�        DX = Dma                                                          �
;�        SI = Dsp Version (For Sb) ou                                      �
;�             Size of RAM of the Gravis                                    �
;�                                                                          �
;�Other Registers Change : None                                             �
;�                                                                          �
;�                                                                          �
;����������������������������������������������������������������������������
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
