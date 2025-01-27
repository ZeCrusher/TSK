A=4:B=30:X3=16:X1=36:GOSUB 6020:J=1
K$(1)=" Mode de couleur Normal             "
K$(2)=" Texte de l'Editeur                 "
K$(3)=" Couleurs des fenŠtres des Menus    "
K$(4)=" Fond des Interrogations du clavier "
K$(5)=" Barre de s‚lection des menus       "
K$(6)=" Couleur du texte dans les menus    "
K$(7)=" Ombre des Ecritures des Menus      "
K$(8)=" Couleurs des barres uniques        "
K$(9)=" Couleur du Texte dans l'Editeur    "
K$(10)="                                    "
K$(11)="                                    "
K$(12)="                                    "
K$(13)="                                    "
K$(14)="                                    "
K$(15)="                                    "
K$(16)="                                    "
6301 COLOR ET,FM
FOR I=1 TO 16:LOCATE 4+I,31:PRINT K$(I):NEXT I
COLOR EB,FB:LOCATE 4+J,31:PRINT K$(J)
6302 X$=INKEY$:IF X$="" THEN 6302
IF X$=RZ$+"H" OR X$="8" THEN J=J-1:IF J=0 THEN J=16
IF X$=RZ$+"P" OR X$="2" THEN J=J+1:IF J=17 THEN J=1
IF X$=E27$ THEN 10001
IF X$=E13$ THEN C=0:D=0:E=0:GOSUB 20011:GOTO 6350
GOTO 6301
6350 A=11:B=5:X1=51:X3=9:GOSUB 6020
6351 FOR K=0 TO 7:O=-1:FOR I=1 TO 46 STEP 3:O=O+1:LOCATE 12+K,5+I:COLOR O,K:PRINT " x ":NEXT I:NEXT K
6352 COLOR ET,FM:LOCATE 20,6:PRINT " 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 þ ":FOR I=0 TO 7:LOCATE 12+I,54:PRINT I:NEXT I
COLOR EM,FM:FOR I=1 TO 9:LOCATE 11+I,5:PRINT "³":NEXT I
COLOR 15,0:LOCATE 11+E,6+D:PRINT "ÚÄ¿":LOCATE 13+E,6+D:PRINT "ÀÄÙ"
LOCATE 12+E,6+D:PRINT "³":LOCATE 12+E,8+D:PRINT "³"
COLOR EB,FB:LOCATE 20,6+D:PRINT STR$(C)+" ":LOCATE 12+E,54:PRINT E
6353 X$=INKEY$:IF X$="" THEN 6353
LOCATE 11,6+D:COLOR EM,FM:PRINT "ÄÄÄÄÄ":LOCATE 11,5:PRINT "Ú"
IF E=0 THEN COLOR C,E:LOCATE 12+E,6+D:PRINT " x ":COLOR C,E+1:LOCATE 13+E,6+D:PRINT " x "
IF E>0 AND E<7 THEN COLOR C,E-1:LOCATE 11+E,6+D:PRINT " x ":COLOR C,E:LOCATE 12+E,6+D:PRINT " x ":COLOR C,E+1:LOCATE 13+E,6+D:PRINT " x "
IF E=7 THEN COLOR C,E-1:LOCATE 11+E,6+D:PRINT " x ":COLOR C,E:LOCATE 12+E,6+D:PRINT " x "
IF X$=RZ$+"K" OR X$="4" THEN C=C-1:D=D-3:IF C=-1 THEN C=15:D=45
IF X$=RZ$+"M" OR X$="6" THEN C=C+1:D=D+3:IF C=16 THEN C=0:D=0
IF X$=RZ$+"H" OR X$="8" THEN E=E-1:IF E=-1 THEN E=7
IF X$=RZ$+"P" OR X$="2" THEN E=E+1:IF E=8 THEN E=0
IF X$=E27$ THEN GOSUB 20011:GOTO 610
IF NOT X$=E13$ THEN 6352
IF J=1 THEN EB=15:FB=4:EM=8:FM=3:EI=8:FI=7:EE=15:FE=1:ET=0
IF J=2 THEN EE=C:FE=E:GOSUB 20011:GOTO 6350
IF J=3 THEN EM=C:FM=E:A=11:B=5:X1=51:X3=9:GOSUB 6020
IF J=4 THEN EI=C:FI=E:A=6:B=6:X1=13:X3=1:GOSUB 6010:COLOR ET,FM:LOCATE 7,7:PRINT "Interrogation"
IF J=5 THEN EB=C:FB=E
IF J=6 THEN ET=C
IF J=7 THEN A=A
IF J=8 THEN ES=C:FS=E
FOR K=0 TO 7:O=-1:FOR I=1 TO 46 STEP 3:O=O+1:LOCATE 12+K,5+I:COLOR O,K:PRINT " x ":NEXT I:NEXT K
GOTO 6352
