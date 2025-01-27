5055 DIM ALGO$(K800):
FOR I=1 TO K800
ALGO$(I)="ณ"
NEXT I
5056 ALGO$(1)="_________"
5057 ALGO$(2)="(__DEBUT__)"
5058 ALGO$(3)=" ณ "
5059 ALGO$(4)=" ณ "
5060 PAS=4:DEKA=0
A=5:B=4:X1=72:X3=14:GOSUB 6000
COLOR A14,A1:LOCATE 5,15:PRINT " Algorithme "
FOR I=DDBK TO FDBK
AWK$=LEFT$(WK$(I,PG),80)
X$=AWK$+SPACE$(80-LEN(AWK$))
V$=LEFT$(X$,8)
IF V$="ECHO OFF" OR V$="echo off" THEN PAS=PAS+1:ALGO$(PAS)="_____ณ_____":PAS=PAS+1:ALGO$(PAS)= "/   Echo.   \":PAS=PAS+1:ALGO$(PAS)= "\ Mode  OFF /":GOTO FINPOURERR
IF V$="ECHO ON " THEN PAS=PAS+1:ALGO$(PAS)="_____ณ_____":PAS=PAS+1:ALGO$(PAS)= "/   Echo.   \":PAS=PAS+1:ALGO$(PAS)= "\ Mode  ON  /":GOTO FINPOURERR
V$=LEFT$(X$,60)
IF V$="ECHO"+SPACE$(56) THEN PAS=PAS+1:ALGO$(PAS)="_________ณ_________":PAS=PAS+1:ALGO$(PAS)="/Affiche le mode de \":PAS=PAS+1:ALGO$(PAS)="\ la commande ECHO  /":PAS=PAS+1:ALGO$(PAS)= " ณ ":PAS=PAS+1:GOTO FINPOURERR
IF V$="Goto"+SPACE$(56) OR V$="GOTO"+SPACE$(56) OR V$="goto"+SPACE$(56) THEN PAS=PAS+1:ALGO$(PAS)="ษออออออออออฯออออออออออป":PAS=PAS+1:ALGO$(PAS)="  บ GOTO SANS ETIQUETTE วฤ>":PAS=PAS+1:ALGO$(PAS)="ศออออออออออัออออออออออผ":PAS=PAS+1:GOTO FINPOURERR
IF V$="For"+SPACE$(57) OR V$="FOR"+SPACE$(57) OR V$="for"+SPACE$(57) THEN PAS=PAS+1:ALGO$(PAS)="ษออออออออออฯออออออออออป":PAS=PAS+1:ALGO$(PAS)="บ  FOR est INCOMPLET  บ":PAS=PAS+1:ALGO$(PAS)="ศออออออออออัออออออออออผ":PAS=PAS+1:GOTO FINPOURERR
IF V$="DEL"+SPACE$(57) OR V$="del"+SPACE$(57) OR V$="Del"+SPACE$(57) THEN PAS=PAS+1:ALGO$(PAS)="ษออออออออออฯออออออออออป":PAS=PAS+1:ALGO$(PAS)="บ Del sans Parametres บ":PAS=PAS+1:ALGO$(PAS)="ศออออออออออัออออออออออผ":PAS=PAS+1:GOTO FINPOURERR
IF V$="ERASE "+SPACE$(54) OR V$="ERASE "+SPACE$(54) THEN PAS=PAS+1:ALGO$(PAS)="ษอออออออออออฯอออออออออออป":PAS=PAS+1:ALGO$(PAS)="บ Erase  sans Parametre บ":PAS=PAS+1:ALGO$(PAS)="ศอออออออออออัอออออออออออผ":PAS=PAS+1:GOTO FINPOURERR
IF V$="If"+SPACE$(58) OR V$="IF"+SPACE$(58) OR V$="if"+SPACE$(58) THEN PAS=PAS+1:ALGO$(PAS)="ษออออออออออฯออออออออออป":PAS=PAS+1:ALGO$(PAS)="บ  IF  est INCOMPLET  บ":PAS=PAS+1:ALGO$(PAS)="ศออออออออออัออออออออออผ":PAS=PAS+1:GOTO FINPOURERR
V$=LEFT$(X$,3)
IF V$="IF " OR V$="if " THEN PAS=PAS+1:ALGO$(PAS)="_ณ_":PAS=PAS+1:ALGO$(PAS)= " /   \ ":PAS=PAS+1:ALGO$(PAS)="    / IF  \ฤฤฤฤ":PAS=PAS+1:ALGO$(PAS)="    \     / Oui":PAS=PAS+1:ALGO$(PAS)="\___/":PAS=PAS+1:ALGO$(PAS)= "Non ณ  "
V$=LEFT$(X$,4)
IF V$="For " OR V$="FOR " OR V$="for " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Traitement  FOR ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤู"
IF V$="DIR " OR V$="dir " OR V$="Dir " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Directorie  DIR ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤู"
V$=LEFT$(X$,5)
IF V$="Goto " OR V$="GOTO " OR V$="goto " THEN PAS=PAS+1:ALGO$(PAS)="ษอออออออออฯอออออออออป":PAS=PAS+1:ALGO$(PAS)="      บ Branchement  GOTO วฤฤฤฤฤ>":PAS=PAS+1:ALGO$(PAS)="ศอออออออออัอออออออออผ"
IF V$="TIME " OR V$="time " OR V$="Time " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Affiche L'heure , Entrer nouvelle Heure ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู"
IF V$="ECHO " OR V$="Echo " OR V$="echo " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Affiche un Texte a l'ecran <ECHO TEXTE> ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู"
IF V$="Date " OR V$="date " OR V$="DATE " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Affiche La Date , Entrer nouvelle date  ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู"
IF V$="PAUSE" OR V$="pause" OR V$="Pause" THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤมฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ PAUSE ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤยฤฤฤู"
IF V$="PAUSE" OR V$="pause" OR V$="Pause" OR V$="Date " OR V$="date " OR V$="DATE " OR V$="ECHO " OR V$="Echo " OR V$="echo" OR V$="TIME " OR V$="time " OR V$="Time " OR V$="Goto " OR V$="GOTO " OR V$="goto " THEN PAS=PAS+1
V$=LEFT$(X$,6)
IF V$="MOUSE " OR V$="mouse " OR V$="Mouse " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Charge la sourie  ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤู"
IF V$="ERASE " OR V$="erase " OR V$="Erase " THEN PAS=PAS+1:ALGO$(PAS)="ฺฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฟ":PAS=PAS+1:ALGO$(PAS)="ณ Effacement  Fichier ณ":PAS=PAS+1:ALGO$(PAS)="ภฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤู"
FINPOURERR:
PAS=PAS+1:ALGO$(PAS+1)="ณ"
NEXT I
ALGO$(PAS)=" ณ "
ALGO$(PAS+1)=" ____ณ____ "
ALGO$(PAS+2)="(___FIN___)"
ALGO$(PAS+3)="":ALGO$(PAS+3)=""
FOR I=PAS+3 TO K800:ALGO$(I)="":NEXT I
TRAVAUX:
5061 FOR I=1 TO 14:COLOR A0,A3
5062 LOCATE 5+I,5:PRINT SPACE$(72)
5063 NEXT I
5064 FOR I=1 TO 14:TABLEAU=72
5065 B=LEN(ALGO$(I+DEKA)):MARGE=(TABLEAU-B)\2
5066 COLOR A0,A3:LOCATE 5+I,4+MARGE:PRINT ALGO$(I+DEKA)
5067 NEXT I
ATTENTE:
5068 X$=INKEY$:IF X$="" THEN ATTENTE
5069 IF X$="2" THEN DEKA=DEKA+1:IF DEKA>K800 THEN DEKA=K800-1
5070 IF X$="8" THEN DEKA=DEKA-1:IF DEKA<0 THEN DEKA=1
5071 IF X$=CHR$(27) THEN ERASE ALGO$:GOTO 20010
GOTO TRAVAUX