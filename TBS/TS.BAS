cls
SCREEN 0
c$=command$
final$="dir "+c$+"\ /s /b >c"+CHR$(58)+"\tempo.thl"
color 0,7
print " Clean disque ver 1.0 "
color
shell final$
Open "c:\tempo.thl" for input as #1
input