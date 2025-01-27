/*
void interrupt new_int_09(__CPPARGS)
{
	static byte cara;


	byte far *pf=(char far *)0x00000417L; // etat des touches Alt et Ctrl et Del

	if ((*pf & 0x0C)==0x0C) // Test Alt et ctrl
	{
		disable();

		cara=inportb(0x60);

		switch(cara)	{
			case CODE_DEL:  // pression sur del

			case CODE_DEL + 0x80: // relachement de la touche del
				cara=inportb(0x61);  // Çliminer le caractäre de l Çlectronique
				outportb(0x61,cara|0x80);  // fin de interrupt
				outportb(0x61,cara);
				outportb(0x20,0x20);
				enable();
			return; // Il ne faut pas faire l ancienne fonction
		}
	}
	_chain_intr(old_int_09);
}
//*/
