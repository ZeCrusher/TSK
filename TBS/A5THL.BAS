IF NOT V=19 THEN 20003
FOR I=0 TO 18:W$=WK$(LIG-I,PG)+SPACE$(80)
LOCATE 22-I,1,0:PRINT SPACE$(80):EDF$=LEFT$(W$,80)
IF (LIG-I)>DDB0-1 AND (LIG-I)<FDB0+1 AND PG=0 THEN COLOR A0,A3:GOTO A5 ELSE COLOR EE,FE
IF (LIG-I)>DDB1-1 AND (LIG-I)<FDB1+1 AND PG=1 THEN COLOR A0,A2:GOTO A5 ELSE COLOR EE,FE
IF (LIG-I)>DDB2-1 AND (LIG-I)<FDB2+1 AND PG=2 THEN COLOR A0,A7:GOTO A5 ELSE COLOR EE,FE
A5:
LOCATE 22-I,1,0:PRINT EDF$
NEXT I
20003 GOSUB 10060
