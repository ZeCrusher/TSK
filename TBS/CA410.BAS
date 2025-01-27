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
1000 COLOR 14,9:LOCATE 2,4:PRINT " CALL ";:COLOR 0,3:PRINT "  > Appelle un fichier de commandes a partir d'un autre fichier" "

COLOR 0:LOCATE 4,6:PRINT "Syntaxe | CALL [unite:][chemin]FICHIER[parametre]
LOCATE 6,3:PRINT "[unite:][chemin]FICHIER  precise l'emplacement et le nom du fichier de "
LOCATE 7,3:PRINT "commandes … appeler. Le fichier doit porter l'‚xtention .BAT"
LOCATE 8,3:PRINT "[parametre] Pr‚cise toute information de la lignes de commandes requise"
LOCATE 9,3:PRINT "par le fichier de commandes. "
LOCATE 10,3:PRINT "  Remarque : le parametre peut contenir toute information qui peut etre "
LOCATE 11,3:PRINT "pass‚e … un fichier de commandes, y compris les commutateurs, les noms de
LOCATE 12,3:PRINT "fichier, les parametres rempla‡ables de %1 … %9"
LOCATE 14,3:PRINT " Exemple : ";:COLOR 1:PRINT "ECHO OFF"
LOCATE 15,14:PRINT "ECHO TEXTE DU FICHIER [ 1 ]"
LOCATE 16,14:PRINT "CALL TESTCALL         ";:COLOR 12:PRINT "   "+CHR$(16)+"ÄÄÄÄ  Execute TESTCALL Ä¿":COLOR 1
LOCATE 17,14:PRINT "ECHO FIN DU TEST "
LOCATE 19,14:PRINT "ECHO OFF";:COLOR 14:PRINT "  <ÄÄÄÄ  Debut de fichier 2 TESTCALL  ":COLOR 1
LOCATE 20,14:PRINT "ECHO TEXTE DE FICHIER [ 2 ]    TESTCALL "
LOCATE 21,14:PRINT "ECHO PUIS RETOUR A FICHIER PRINCIPALE ":COLOR 12
LOCATE 18,11:PRINT "Ú"+STRING$(52,"Ä")+"Ù":LOCATE 19,11:PRINT "ÀÄ"+CHR$(16):LOCATE 17,64:PRINT "³"
LOCATE 21,8:PRINT "ÀÄÄÄÄ":FOR I=1 TO 3:LOCATE 17+I,8:PRINT "³":NEXT I:LOCATE 17,8:PRINT "ÚÄÄÄ"+CHR$(16)

BSAVE "CA410.THL",0,3856
COLOR 7,0:CLS
BLOAD "CA410.THL"
GOSUB 49000
END

49000 IF INKEY$="" THEN 49000 ELSE RETURN

END
