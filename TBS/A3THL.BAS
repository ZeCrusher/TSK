AA=0:COLOR EE,FE:AA=LIG-V
FOR I=0 TO 18:BB=LEN(WK$(AA+I+1,PG))
20012 IF NOT BB<80 THEN C$=LEFT$(WK$(AA+I+1,PG),80):ZZT=0 ELSE ZZT=80-BB:C$=WK$(AA+I+1,PG)
20013 IF WK$(AA+I+1,PG)="" THEN C$="":ZZT=80
20014 IF (AA+I+1)>DDB0-1 AND (AA+I+1)<FDB0+1 AND PG=0 THEN COLOR A0,A3:GOTO A3 ELSE COLOR EE,FE
IF (AA+I+1)>DDB1-1 AND (AA+I+1)<FDB1+1 AND PG=1 THEN COLOR A0,A2:GOTO A3 ELSE COLOR EE,FE
IF (AA+I+1)>DDB2-1 AND (AA+I+1)<FDB2+1 AND PG=2 THEN COLOR A0,A7:GOTO A3 ELSE COLOR EE,FE
A3:
LOCATE 4+I,1,0:PRINT C$+space$(ZZT):COLOR A15,A1
SAUT2:
COLOR EE,FE
NEXT I:LOCATE 4,1:COLOR A8,A3
