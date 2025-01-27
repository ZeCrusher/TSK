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
1000 COLOR 14,9:LOCATE 2,4:PRINT " SHIFT ";:COLOR 0,3:PRINT "  > Decalage de la liste des parametres batch"

     COLOR 0:LOCATE 4,6:PRINT "Syntaxe | SHIFT
LOCATE 6,3:PRINT "Normalement , on peut envoyer jusqu'a 9 parametres a un fichier batch . La"
LOCATE 7,3:PRINT "commande SHIFT permet d'etentre ce nombre au dela de 9.On n'est plus limite"
LOCATE 8,3:PRINT "que par la longueur d'un ligne DOS. Les 9 premiers parametres sont
LOCATE 9,3:PRINT "accessibles directement sous les descriptions %1 a %9 , %0 represente "
LOCATE 10,3:PRINT "le nom du fichier batch.Si on execute SHIFT,la list des parametres"
LOCATE 11,3:PRINT "est decalee d'un place vers la gauche : en clair %1 devient %0"
LOCATE 12,3:PRINT " %2 devient %1 ect ... cela signifie que vous perdez le parametre %0"
LOCATE 13,3:PRINT "et que vous avez un nouveau parametre %9
LOCATE 15,3:PRINT " Exemple : ";:COLOR 1:PRINT "ECHO OFF"
LOCATE 17,14:PRINT "IF %1 /==/ GOTO AUCUN ";:COLOR 12:PRINT " <ÄÄÄÄ Test si il vous reste des parametres":COLOR 1
LOCATE 16,14:PRINT "SUITE:"
LOCATE 18,14:PRINT "ECHO "+CHR$(34)+"%1"+CHR$(34)+"";:COLOR 12:PRINT "   <ÄÄÄÄÄÄ affiche le parametre %1":COLOR 1
LOCATE 19,14:PRINT "SHIFT";:COLOR 12:PRINT "   <ÄÄÄÄ  decale les parametres ":COLOR 1
LOCATE 20,14:PRINT "GOTO SUITE"
LOCATE 21,14:PRINT "AUCUN:"
BSAVE "SH287.THL",0,3856
COLOR 7,0:CLS
BLOAD "SH287.THL"
GOSUB 49000
END

49000 IF INKEY$="" THEN 49000 ELSE RETURN

END
