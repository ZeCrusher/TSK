5055 DIM ALGO$(K800):
FOR I=1 TO K800
ALGO$(I)="�"
NEXT I
5056 ALGO$(1)="_________"
5057 ALGO$(2)="(__DEBUT__)"
5058 ALGO$(3)=" � "
5059 ALGO$(4)=" � "
5060 PAS=4:DEKA=0
A=5:B=4:X1=72:X3=14:GOSUB 6000
COLOR A14,A1:LOCATE 5,15:PRINT " Algorithme "
FOR I=DDBK TO FDBK
AWK$=LEFT$(WK$(I,PG),80)
X$=AWK$+SPACE$(80-LEN(AWK$))
V$=LEFT$(X$,8)
IF V$="ECHO OFF" OR V$="echo off" THEN PAS=PAS+1:ALGO$(PAS)="_____�_____":PAS=PAS+1:ALGO$(PAS)= "/   Echo.   \":PAS=PAS+1:ALGO$(PAS)= "\ Mode  OFF /":GOTO FINPOURERR
IF V$="ECHO ON " THEN PAS=PAS+1:ALGO$(PAS)="_____�_____":PAS=PAS+1:ALGO$(PAS)= "/   Echo.   \":PAS=PAS+1:ALGO$(PAS)= "\ Mode  ON  /":GOTO FINPOURERR
V$=LEFT$(X$,60)
IF V$="ECHO"+SPACE$(56) THEN PAS=PAS+1:ALGO$(PAS)="_________�_________":PAS=PAS+1:ALGO$(PAS)="/Affiche le mode de \":PAS=PAS+1:ALGO$(PAS)="\ la commande ECHO  /":PAS=PAS+1:ALGO$(PAS)= " � ":PAS=PAS+1:GOTO FINPOURERR
IF V$="Goto"+SPACE$(56) OR V$="GOTO"+SPACE$(56) OR V$="goto"+SPACE$(56) THEN PAS=PAS+1:ALGO$(PAS)="���������������������ͻ":PAS=PAS+1:ALGO$(PAS)="  � GOTO SANS ETIQUETTE ��>":PAS=PAS+1:ALGO$(PAS)="���������������������ͼ":PAS=PAS+1:GOTO FINPOURERR
IF V$="For"+SPACE$(57) OR V$="FOR"+SPACE$(57) OR V$="for"+SPACE$(57) THEN PAS=PAS+1:ALGO$(PAS)="���������������������ͻ":PAS=PAS+1:ALGO$(PAS)="�  FOR est INCOMPLET  �":PAS=PAS+1:ALGO$(PAS)="���������������������ͼ":PAS=PAS+1:GOTO FINPOURERR
IF V$="DEL"+SPACE$(57) OR V$="del"+SPACE$(57) OR V$="Del"+SPACE$(57) THEN PAS=PAS+1:ALGO$(PAS)="���������������������ͻ":PAS=PAS+1:ALGO$(PAS)="� Del sans Parametres �":PAS=PAS+1:ALGO$(PAS)="���������������������ͼ":PAS=PAS+1:GOTO FINPOURERR
IF V$="ERASE "+SPACE$(54) OR V$="ERASE "+SPACE$(54) THEN PAS=PAS+1:ALGO$(PAS)="�����������������������ͻ":PAS=PAS+1:ALGO$(PAS)="� Erase  sans Parametre �":PAS=PAS+1:ALGO$(PAS)="�����������������������ͼ":PAS=PAS+1:GOTO FINPOURERR
IF V$="If"+SPACE$(58) OR V$="IF"+SPACE$(58) OR V$="if"+SPACE$(58) THEN PAS=PAS+1:ALGO$(PAS)="���������������������ͻ":PAS=PAS+1:ALGO$(PAS)="�  IF  est INCOMPLET  �":PAS=PAS+1:ALGO$(PAS)="���������������������ͼ":PAS=PAS+1:GOTO FINPOURERR
V$=LEFT$(X$,3)
IF V$="IF " OR V$="if " THEN PAS=PAS+1:ALGO$(PAS)="_�_":PAS=PAS+1:ALGO$(PAS)= " /   \ ":PAS=PAS+1:ALGO$(PAS)="    / IF  \����":PAS=PAS+1:ALGO$(PAS)="    \     / Oui":PAS=PAS+1:ALGO$(PAS)="\___/":PAS=PAS+1:ALGO$(PAS)= "Non �  "
V$=LEFT$(X$,4)
IF V$="For " OR V$="FOR " OR V$="for " THEN PAS=PAS+1:ALGO$(PAS)="�����������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Traitement  FOR �":PAS=PAS+1:ALGO$(PAS)="�������������������"
IF V$="DIR " OR V$="dir " OR V$="Dir " THEN PAS=PAS+1:ALGO$(PAS)="�����������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Directorie  DIR �":PAS=PAS+1:ALGO$(PAS)="�������������������"
V$=LEFT$(X$,5)
IF V$="Goto " OR V$="GOTO " OR V$="goto " THEN PAS=PAS+1:ALGO$(PAS)="�������������������ͻ":PAS=PAS+1:ALGO$(PAS)="      � Branchement  GOTO ������>":PAS=PAS+1:ALGO$(PAS)="�������������������ͼ"
IF V$="TIME " OR V$="time " OR V$="Time " THEN PAS=PAS+1:ALGO$(PAS)="�����������������������������������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Affiche L'heure , Entrer nouvelle Heure �":PAS=PAS+1:ALGO$(PAS)="�������������������������������������������"
IF V$="ECHO " OR V$="Echo " OR V$="echo " THEN PAS=PAS+1:ALGO$(PAS)="�����������������������������������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Affiche un Texte a l'ecran <ECHO TEXTE> �":PAS=PAS+1:ALGO$(PAS)="�������������������������������������������"
IF V$="Date " OR V$="date " OR V$="DATE " THEN PAS=PAS+1:ALGO$(PAS)="�����������������������������������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Affiche La Date , Entrer nouvelle date  �":PAS=PAS+1:ALGO$(PAS)="�������������������������������������������"
IF V$="PAUSE" OR V$="pause" OR V$="Pause" THEN PAS=PAS+1:ALGO$(PAS)="�������Ŀ":PAS=PAS+1:ALGO$(PAS)="� PAUSE �":PAS=PAS+1:ALGO$(PAS)="���������"
IF V$="PAUSE" OR V$="pause" OR V$="Pause" OR V$="Date " OR V$="date " OR V$="DATE " OR V$="ECHO " OR V$="Echo " OR V$="echo" OR V$="TIME " OR V$="time " OR V$="Time " OR V$="Goto " OR V$="GOTO " OR V$="goto " THEN PAS=PAS+1
V$=LEFT$(X$,6)
IF V$="MOUSE " OR V$="mouse " OR V$="Mouse " THEN PAS=PAS+1:ALGO$(PAS)="�������������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Charge la sourie  �":PAS=PAS+1:ALGO$(PAS)="���������������������"
IF V$="ERASE " OR V$="erase " OR V$="Erase " THEN PAS=PAS+1:ALGO$(PAS)="���������������������Ŀ":PAS=PAS+1:ALGO$(PAS)="� Effacement  Fichier �":PAS=PAS+1:ALGO$(PAS)="�����������������������"
FINPOURERR:
PAS=PAS+1:ALGO$(PAS+1)="�"
NEXT I
ALGO$(PAS)=" � "
ALGO$(PAS+1)=" ____�____ "
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