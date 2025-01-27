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
1000 COLOR 14,9:LOCATE 2,4:PRINT " "+CHR$(34)+"%1"+CHR$(34)+" ";:COLOR 0,3:PRINT "  > valeur d'un parametre d'un fichier batch"
COLOR 0:LOCATE 4,6:PRINT "Syntaxe | > FICHIER parametre1 parametre2 parametre3
LOCATE 6,3:PRINT "vous pouver envoyer des parametres aux fichiers batch.ainsi les programmes"
LOCATE 7,3:PRINT "batch sont extremement souple et universels .Les parametres sont separes"
LOCATE 8,3:PRINT "par des espaces et il faut les saisir a la suite du nom du programme batch :"
LOCATE 9,3:PRINT "Le system d'exploitation envois les parametre au traitement de batch"
LOCATE 10,3:PRINT "par l'intermediaire des variables qui sont prevu pour %1 a %9, %0 "
LOCATE 11,3:PRINT "represente le nom du programme batch"
LOCATE 13,3:PRINT "Exemple :  A>TEST PAR1  ";:COLOR 12:PRINT "le fichier TEST a comme parametre PAR1":COLOR 1
LOCATE 14,16:PRINT "ECHO OFF"
LOCATE 15,16:PRINT "IF %1 /==/ GOTO AUCUN   ";:COLOR 12:PRINT CHR$(17)+"ÄÄ TEST la presence d'un parametre":COLOR 1
LOCATE 16,16:PRINT "ECHO VOUS AVEZ SAISI LE PARAMERTE SUIVANT
LOCATE 17,16:PRINT "ECHO "+CHR$(34)+"%1"+CHR$(34)
LOCATE 18,16:PRINT ":AUCUN"
LOCATE 19,16:PRINT "ECHO FIN DU TRAITEMENT":COLOR 0
LOCATE 20,3:PRINT "vous pouver envoyer un parametre a un commande de DOS "
LOCATE 21,3:PRINT " Exemple -> DIR %1 "
BSAVE "P1289.THL",0,3856
COLOR 7,0:CLS
BLOAD "P1289.THL"
GOSUB 49000
END

49000 IF INKEY$="" THEN 49000 ELSE RETURN

END
