SCREEN 0:CLS:COLOR 12:PRINT "** THOLL **":COLOR 3
IF MARGOVANE$="OUI" THEN 40029
PAR$=COMMAND$
40029 CLOSE:B=LEN(PAR$)
40030 A$=LEFT$(PAR$,3):B$=LEFT$(PAR$,5)
IF A$="/P+" OR A$="/p+" THEN PRINT "Parametres Admis ":PRINT "Parametre  , WK$ *00 , /T+ FICHIER.EXT  , /MEM , /V ":PRINT "les modes d'ecran -> CGA , VGA , MDA , EGA  ":GOSUB 49000
40065 IF A$="/T+" OR A$="/t+" THEN NOM$=RIGHT$(PAR$,B-4):TYN$="ON":HO2$=NOM$:ON ERROR GOTO 0:ON ERROR GOTO 60000:GOTO 10000
IF A$="WK$" OR A$="wk$" THEN WOPY$="OUI":N$=RIGHT$(PAR$,B-4):K800=VAL(N$):PRINT :PRINT "Configuration pour ";K800;" ligne dans la Matrice ":PRINT "Patientez ..":DELAY 2:ON ERROR GOTO 0:ON ERROR GOTO 60000
IF A$="WK$" OR A$="wk$" AND K800>40 THEN 10
IF A$="VGA" OR A$="vga" THEN SCEN=12:CAIN$="OUI"
IF A$="CGA" OR A$="cga" OR A$="MDA" OR A$="mda" THEN SCEN=0:CAIN$="OUI"
IF A$="EGA" OR A$="ega "THEN SCEN=7:CAIN$="OUI"
IF CAIN$="OUI" THEN ON ERROR GOTO 0:ON ERROR GOTO 60000:PRINT "Le Mode choisie est >";A$:GOSUB 49000:GOTO 10000
41000 PRINT:PRINT:PRINT "Parametre ";:COLOR 12:PRINT CHR$(34);:COLOR 14:PRINT PAR$;:COLOR 12:PRINT CHR$(34);:COLOR 3:PRINT " non Conforme aux Normes de l'execution "
41010 PRINT:PRINT "SäRGä TSAKI THOLL ver 5.00 [ 91-92 ]"
COLOR 1,3:LOCATE 8,7:PRINT CHR$(218)+STRING$(62,"Ä")+CHR$(191)
FOR I=1 TO 14:LOCATE 8+I,7:PRINT CHR$(179)+SPACE$(62)+CHR$(179):NEXT I
LOCATE 8+I,7:PRINT CHR$(192)+STRING$(62,"Ä")+CHR$(217):LOCATE 8,10:COLOR 0,1:PRINT " Les Parametres [/P+] ":COLOR 0,3
LOCATE 10,9:PRINT "WK$ *00 permet d'augmenter ou de diminuer le nombre de ligne"
LOCATE 11,9:PRINT "dans la matrice de THOLL , * est un nombre entre 1 et 24 "
LOCATE 12,9:PRINT " Exemple : A>THOLL WK$ 1100"
LOCATE 14,9:PRINT " CGA , VGA , EGA  permet de s'electionner un type d'ecran"
LOCATE 15,9:PRINT " Le mode par defaut est CGA  ; *.*   Fichier a charger "
LOCATE 13,9:PRINT " /MEM pour Taille de la RAM "
LOCATE 17,9:PRINT " /T+ FICHIER.EXT  permet de charger un fichier dans la"
LOCATE 18,9:PRINT " matrice de THOLL ; /MEM stock THOLL en Memoire vive"
LOCATE 20,9:PRINT " /V ou /VIRUS permet de tester si THOLL a ete contamine par"
LOCATE 21,9:PRINT " un virus [ainsi que les 3 fichiers DOS]"
G11:
IF INKEY$="" THEN G11
41011 GOSUB 49000:END
48000 '
48010 GOSUB 65020
IF R$="" THEN R$="ERREUR NON DEFINIE / ou fin du travaille en cour          "
48020 COLOR 12,4:LOCATE 20,1:PRINT "LOCALISATION DE L'ERREUR ":GOSUB 49000:END