S=&HB800:S=S+65535:DEF SEG=S
SCREEN 0,0,0:WIDTH 80:COLOR 15,1:CLS
COLOR 8,3
GOSUB CADRE:GOTO 99
CADRE:
COLOR 8,3:LOCATE 1,1:PRINT CHR$(8)+STRING$(78,"ß")+CHR$(8)
FOR I=1 TO 20
LOCATE 1+I,1:PRINT CHR$(221)+SPACE$(78)+CHR$(222)
NEXT I
LOCATE 1+I,1:PRINT CHR$(8)+STRING$(78,220)+CHR$(8)
LOCATE 1+I,72:COLOR 0,4:PRINT " THOLL ":COLOR 0,3
COLOR 8,3
LOCATE 3,1:PRINT CHR$(219)+STRING$(78,196)+CHR$(219)
:RETURN
99 COLOR 0
   IF B$="1" THEN 1000
1000 COLOR 14,9:LOCATE 2,4:PRINT " PAUSE ";:COLOR 0,3:PRINT "  > interruption du traitement Batch , affichage d'un attente"
     COLOR 0:LOCATE 4,6:PRINT "Syntaxe | > PAUSE <Texte> "
LOCATE 6,3:PRINT "PAUSE sert a interrompre le traitement d'un fichier Batch . Vous pouvez "
LOCATE 7,3:PRINT "employer PAUSE pour permetre par exemple le chagement de diskette ou de "
LOCATE 8,3:PRINT "l'activation de votre imprimante ou de la mise en place du papier       "
LOCATE 9,3:PRINT "Si le label n'existe pas un message d'erreur est affiche et le traitement"
LOCATE 10,3:PRINT "ect .."
LOCATE 12,3:PRINT " Suivant les version de MS-DOS le message peut etre different , mais "
LOCATE 13,3:PRINT "il signifie toujours la meme chose : ";:COLOR 1:PRINT "   Tapez sur une touche ":COLOR 0
LOCATE 14,3:PRINT "Vous pouver presser n'importe quelle touche a l'exception de CTRL-C qui"
LOCATE 15,3:PRINT "interrompt definitivement le traitement"
LOCATE 17,3:PRINT "Exemple : ";:COLOR 1:PRINT "ECHO OFF":LOCATE 18,13:PRINT "PAUSE CHANGEZ DE DISKETTE DANS LE LECTEUR B:

BSAVE "PA285.THL",0,3856
COLOR 7,0:CLS
BLOAD "PA285.THL"
GOSUB 49000
END

49000 IF INKEY$="" THEN 49000 ELSE RETURN

END
