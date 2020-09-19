Dieses Projekt ist im Umfang von #HackTheSummer entstanden:
https://hack-the-summer.de/

Erklärungs Video:
https://youtu.be/IQqjV1YeHMY


#	How To Use


Zum Nutzen der GenderApp muss die GenderApp.exe inklusive des Data Ordners in dasselbe Verzeichnis extrahiert werden. Nach dem Starten der GenderApp verschiebt sich das Programm in den Hintergrund. Zum Korrigieren einer Markierten Textstelle dient die Tastenkombination AltGr+L.
Um das Programm zu beenden kann AltGr+4 benutzt werden.


#	Kompilieren des Source Codes


Zum Kompilieren des Source Codes wird der Tiny C Compiler benötigt inklusiv des WinAPI Pakets https://bellard.org/tcc/

Beispiel zum Kompilieren und starten des Programms:

tcc "Gender App.c" Clipboard.c Utils.c List.c -luser32 -run
