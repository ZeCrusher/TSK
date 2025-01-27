// Logging des ‚xecutions de programmes
#include <dos.h>

void interrupt new_int_14(unsigned bp,unsigned di,unsigned si,unsigned ds,unsigned es,unsigned dx,unsigned cx, unsigned bx,unsigned ax);
void creer_fichier(void);
void numero_suivant(void);
void log_infos(void);
extern unsigned _stklen=800;
extern unsigned _heaplen=10;

	unsigned image_ss,image_sp,logexec_ss,logexec_sp;

char far *pfc;
unsigned far *pfu;
int nf;
struct INFO {
	unsigned int heures,
			 intervalles;
	char nom_prog[81];
}	info;
int cur_psp;
char nom_fich_log[]="\\LOGINTSk.000";
void interrupt (* old_int_21)();

void main()
{
	creer_fichier();
	disable();
		logexec_sp=_SP;
		logexec_ss=_SS;
	enable();

	old_int_21 = getvect(0x21);
	setvect(0x21, new_int_21);
	pfu = MK_FP (_psp - 1,3);
	bdos(0x31,*pfu,0);
}

void interrupt new_int_21(unsigned bp,unsigned di,unsigned si,unsigned ds,unsigned es,unsigned dx,unsigned cx, unsigned bx,unsigned ax)
{
	static char *pc;
		enable();
		if (ax==0x4B00)  {
			pfc = MK_FP(ds,dx);
			for (pc=info.nom_prog;*pfc;) *pc++=*pfc++;
			*pc=0;
			disable();
			image_ss = _SS; image_sp = _SP;
			_SS = logexec_ss; _SP = logexec_sp;
			enable();
			log_infos();
			disable();
			_SS = image_ss;
			_SP = image_sp;
			enable();
		}
   _chain_intr(old_int_21);
}
void log_infos(void)
{
	pfu= 0x0000046E;
	info.heures= *pfu;
	pfu= 0x0000046C;
	info.intervalles= *pfu;

 _AH=0x62;
 old_int_21();
 cur_psp = _BX;

 _BX = _psp;
 _AH= 0x50;
 old_int_21();

 _CX= sizeof(struct INFO);
 _DX = &info;
 _BX=nf;
 _AH=0x40;
 old_int_21();

 _BX=nf;
 _AH=0x68;
  old_int_21();

 _BX=cur_psp;
 _AH=0x50;
  old_int_21();
}
void creer_fichier(void)
{
	static struct {
		unsigned ans,mois,jour,heure,minutes;
	}	date_heure;

	do
	{
	 numero_suivant();
	 _DX=nom_fich_log;
	 _AX=0x3D00;
	 geninterrupt(0x21);
		if (!(_FLAGS&1))	 {
			_BX=_AX;
			_AH=0x3E;
			geninterrupt(0x21);
		}
	 } while(!(_FLAGS&1));

_CX=0;
_DX=nom_fich_log;
_AH=0x3C;
geninterrupt(0x21);
_BX=_AX;
_AH=0x3E;
geninterrupt(0x21);

_DX = nom_fich_log;
_AX = 0x3D21;
geninterrupt(0x21);
nf = _AX;

	_AH= 0x2A;
	geninterrupt(0x21);
	date_heure.ans=_CX;
	date_heure.mois=_DH;
	date_heure.jour=_DL;
	_AH=0x2C;
	geninterrupt(0x21);
	date_heure.heure=_CH;
	date_heure.minutes=_CL;

	_BX=nf;
	_CX=sizeof(date_heure);
	_DX=&date_heure;
	_AH=0x40;
	geninterrupt(0x21);
	_BX=nf;
	_AH=0x68;
	geninterrupt(0x21);
}

void numero_suivant(void)
{
	int nb_car;

	nb_car=strlen(nom_fich_log);
	nom_fich_log[nb_car-1] += 1;
		if (nom_fich_log[nb_car-1] > '9')
		{
			nom_fich_log[nb_car-1]='0';
			nom_fich_log[nb_car-2]+='1';
			if (nom_fich_log[nb_car-2] > '9')
			{
				nom_fich_log[nb_car-2]='0';
				nom_fich_log[nb_car-3]+='1';
			}
		}
}