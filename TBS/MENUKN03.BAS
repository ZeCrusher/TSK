IF J=1 THEN AI$="Recherche un mot ou caractere ASCII dans le texte et affiche les lignes":GOSUB 2100
IF J=2 THEN AI$="Remplace un mot par un autre avec ou sans confirmation":GOSUB 2100
IF J=3 THEN AI$="Definit la barre (þþþþ) en plusieur variable graduer":GOSUB 2100
IF J=4 THEN AI$="Recherche un mot ou un caractere sur un Fichier disque":GOSUB 2100
IF J=5 THEN AI$="Place une page tout les 50 lignes ":GOSUB 2100
IF J>5 AND J<14 THEN AI$="Les Tableaux sont selectionn‚ avec Alt C pour le debut et Alt K pour la fin":GOSUB 2100
IF J=14 THEN AI$="Centrer / marge / fichier Aide des fonctions BATCH":GOSUB 2100