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
1000 COLOR 14,9:LOCATE 2,4:PRINT " ECHO ";:COLOR 0,3:PRINT "  > Mise en place du mode ECHO ou Affichage de texte "

     COLOR 0:LOCATE 4,6:PRINT "Syntaxe | > ECHO {[ ON ³ OFF ]}
             LOCATE 5,16:PRINT "> ECHO <Texte>"

LOCATE 7,5:PRINT "Si vous voulez activer l'etat ECHO , employez la premiere commande sinon
LOCATE 8,5:PRINT "utilisez la seconde commande qui le desactive { ECHO ON } { ECHO OFF }"
LOCATE 10,5:PRINT "ECHO est normalement utilisee pour afficher du texte sur l'ecran "
LOCATE 11,7:PRINT " L'exemple qui suit vous montre cela clairement"
LOCATE 13,5:PRINT "ECHO OFF";:COLOR 1:PRINT "     <ÄÄÄÄÄÄ  desactive l'etat ECHO"
COLOR 0:LOCATE 14,5:PRINT "ECHO ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»";:COLOR 12:PRINT "    <ÄÄÄÄÄÄÄ¿"
COLOR 0:LOCATE 15,5:PRINT "ECHO º BONJOUR ...!! º";:COLOR 12:PRINT "     <ÄÄÄÄÄÄÁÂÄÄÄ  affiche le texte encadre"
COLOR 0:LOCATE 16,5:PRINT "ECHO ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼";:COLOR 12:PRINT "      <ÄÄÄÄÄÄÙ"


BSAVE "EC70.THL",0,3856
COLOR 7,0:CLS
BLOAD "EC70.THL"
GOSUB 49000
END

49000 IF INKEY$="" THEN 49000 ELSE RETURN

END
