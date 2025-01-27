SCREEN 0,0,0:PG=1:DDBK=1:FDBK=3
WK$(1,PG)="    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿        "
WK$(2,PG)="    ³                                ³        "
WK$(3,PG)="    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ        "
color 12:FOR I=1 TO 3:PRINT WK$(I,PG):NEXT I
COMPRES$="OUI":VN$=" "  ' VN$ EST LE CODE A COMPACTER '** EXEMPLE CHR$(196) = Ä

N$(1)=SPACE$(80)


6900 FOR I=DDBK TO FDBK
IF COMPRES$="OUI" THEN IF INSTR(WK$(I,PG),VN$)=0 THEN 6950

B=LEN(WK$(I,PG))
FOR AM=1 TO B



next am
6950 NEXT I
COLOR 3:FOR I=1 TO 3:PRINT WK$(I,PG):NEXT I
