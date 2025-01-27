AI$="Menu Option en cours ":GOSUB 2100
K$(1)=" Atteindre la ligne xxx "
K$(2)=" Aide Mots Clefs        "
K$(3)=" S‚l‚ction du l‚cteur   "
K$(4)=" Code Ascii Clavier     "
K$(5)=" Table des Codes Ascii  "
K$(6)=" M‚moire restante RAM   "
K$(7)=" S‚lŠction d'une Fiche  "
K$(8)=" Fiche en cour          "
K$(9)=" Nom du Fichier en cour "
K$(10)=" R‚duction ‚space droit "
K$(11)=" Voir Page int‚grale    "
K$(12)=" Quitter / Initialiser  "
8220 COLOR ET,FM:FOR I=1 TO 12:LOCATE 4+I,36,0:PRINT K$(I):NEXT I
8222 COLOR EB,FB:LOCATE 4+J,36:PRINT K$(J)
8225 X$=INKEY$:IF X$="" THEN 8225
IF X$=RZ$+"H" OR X$="8" THEN J=J-1:IF J=0 THEN J=12
IF X$=RZ$+"P" OR X$="2" THEN J=J+1:IF J=13 THEN J=1
IF X$="4" OR X$=RZ$+"K" THEN KN=3:GOSUB 20011:GOTO 610
IF X$="6" OR X$=RZ$+"M" THEN KN=5:GOSUB 20011:GOTO 610
IF X$=E27$ THEN 20010
IF NOT X$=E13$ THEN 8220
IF J=1 THEN 8410
IF J=2 THEN 8420
IF J=3 THEN 10001
IF J=4 THEN GOSUB 20011:A=8:B=17:X1=40:X3=7:GOSUB 6000:GOTO 8500
IF J=5 THEN 8170
IF J=6 THEN A=10:B=10:X1=55:X3=4:GOSUB 6000:COLOR ET,FM:LOCATE 11,13:PRINT "Memoire en octect pour THOLL ->";FRE(0)
IF J=6 THEN MX=FRE(0):COLOR CLT,FM:KA=INT((MX*100)/49500):LOCATE 12,13:KB=100-KA:PRINT "Reste ";KA;" % , Utiliser ";KB;" % de Memoire":MA=MX/1024:LOCATE 13,13:COLOR A12,FM:PRINT USING " Valeur Equivalente         ###.### Ko";MA
IF J=6 THEN MX=FRE(-1):MA=MX/1024:LOCATE 14,13:COLOR A12,FM:PRINT USING " Memoire Restante [RAM]     ###.### Ko";MA:GOSUB 49000:GOTO 20010
IF J=7 THEN 20004
IF J=8 THEN A=10:B=10:X1=23:X3=1:GOSUB 6010:LOCATE 11,12:PRINT " Niveau en cour > ";PG:GOSUB 49000:GOTO 20010
IF J=9 THEN A=10:B=10:X1=60:X3=3:GOSUB 6000:FOR I=0 TO 2:COLOR ET,FM:LOCATE 11+I,13:PRINT "Nom en cour > ";:COLOR A1:PRINT NOM$(I):NEXT I:GOSUB 49000:GOTO 20010
IF J=10 THEN GOSUB 20011:COLOR A15,A4:LOCATE 6,6:PRINT "** Patientez Reduction de texte **":GOSUB 9800:GOTO 10001
8223 IF J=11 THEN GOSUB V:GOSUB 49000:GOTO 10001
IF J=12 THEN 8000
