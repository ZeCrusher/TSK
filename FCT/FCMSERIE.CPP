/*   FCMSERIE version 1.00
 R‚alis‚ le: 21/06/1996
 DŠrniŠre modif: 21/06/96
 Programmation & conception: Matheis , Tsakiropoulos Serge
 Ce PROGRAMME peut ˆtre utilis‚ dans un autre programme comme fonction
TOUT DROIT RESERVER
*/

typedef unsigned int byte;

byte ADR_COM1=0;       //Adresse du COM1
byte ADR_COM2=0;       //Adresse du COM2
byte ADR_COM3=0;       //Adresse du COM3
byte ADR_COM4=0;       //Adresse du COM4

int detect_com(void);//d‚tecte les COM valides et le nombre de COM d‚tect‚s


int detect_com(void)
{
	asm mov NB_COM,0                //NB_COM=0
	asm mov ax,0x40                 //AX=$40 segment
	asm mov es,ax                   //ES=$40 segment d' es:di
	asm mov di,0                    //DI=0 ofset
	asm mov ax,word ptr es:[di]     //R‚cupŠre adresse du COM1 en [0040:0000]
	asm mov ADR_COM1,ax             //Ecrit ADR_COM1
	asm mov ax,word ptr es:[di+2]   //R‚cupŠre adresse du COM2 en [0040:0002]
	asm mov ADR_COM2,ax             //Ecrit ADR_COM2
	asm mov ax,word ptr es:[di+4]   //R‚cupŠre adresse du COM3 en [0040:0004]
	asm mov ADR_COM3,ax             //Ecrit ADR_COM3
	asm mov ax,word ptr es:[di+6]   //R‚cupŠre adresse du COM4 en [0040:0006]
	asm mov ADR_COM4,ax             //Ecrit ADR_COM4
	asm xor dx,dx                   //DX=0
	asm mov ax,2                    //AX=2 incr‚ment
	asm mov cx,4                    //CX=4 4 it‚rations car 4 COM
	boucle:
	asm mov bx,word ptr es:[di]     //AX=adresse du COM point‚e par es:di
	asm and bx,bx                   //test … 0
	asm jz suite                    //si BX=0 alors saute l'incr‚mentation
	asm inc dx                      //sinon incr‚mente le nombre de COM d‚tect‚s
	suite:
	asm add di,ax                   //inc‚mentation pour sauter de word en word
	asm loop boucle                 //bouclage
	asm mov NB_COM,dl               //NB_COM=nombre de COMs pr‚sents

	return(NB_COM);
}
