S=&HB800:S=S+65535:DEF SEG=S
SCREEN 0,0,0:WIDTH 80:COLOR 15,1:CLS
COLOR 8,3
GOSUB CADRE:GOTO 99
CADRE:
COLOR 8,3:LOCATE 1,1:PRINT CHR$(8)+STRING$(78,"ъ")+CHR$(8)
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
1000 COLOR 14,9:LOCATE 2,4:PRINT " GOTO ";:COLOR 0,3:PRINT "  > Branchement direct a un label dans le fichier Batch"

     COLOR 0:LOCATE 4,6:PRINT "Syntaxe | > GOTO <Label> "
LOCATE 6,3:PRINT "GOTO vous offre la possibilite de traiter une pile de commande autrement"
LOCATE 7,3:PRINT "qu'en sequentiel (une commande apres l'autre dans l'ordre).Vous pouvez"
LOCATE 8,3:PRINT "ainsi vous brancher aussi bien en arriere qu'en avant dans le fichier batch"
LOCATE 10,3:PRINT "Si le label n'existe pas un message d'erreur est affiche et le traitement"
LOCATE 11,3:PRINT "est interrompu."
LOCATE 12,3:PRINT "On peut employer autant de caracteres que l'on veut pour le nom du Label"
LOCATE 13,3:PRINT "mais seul les 8 premiers sont significatifs ."
LOCATE 15,3:PRINT " Le LABEL est suivi d'un double point "+CHR$(34)+" : "+CHR$(34)
LOCATE 17,15:PRINT " Exemple ->     ";:COLOR 1:PRINT "ECHO OFF"
LOCATE 18,31:PRINT "RETOUR:";:COLOR 12:PRINT "      "+CHR$(17)+"ддддд le LABEL RETOUR":COLOR 1
LOCATE 19,31:PRINT "ECHO Test de la command GOTO,Fin Ctrl C"
LOCATE 20,31:PRINT "GOTO RETOUR ";:COLOR 14,3:PRINT "ддддддддддддддддддддддддддддддддды":LOCATE 19,76:PRINT "Ё":LOCATE 18,68:PRINT CHR$(17)+"ддддддд©"



BSAVE "GO279.THL",0,3856
COLOR 7,0:CLS
BLOAD "GO279.THL"
GOSUB 49000
END

49000 IF INKEY$="" THEN 49000 ELSE RETURN

END
