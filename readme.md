# Anleitung Schiffe Versenken

Bei diesem Projekt handelt es sich um ein Hochschulprojekt, welches im Rahmen einer C++ Vorlesung benotet werden soll.

## Legende: 

■ (blau) : Meer, verdecktes Feld
■ (weiß) : Schiff (nur auf dem eigenen Feld zu sehen)
O (weiß) : Schuss ins Meer, kein Treffer
X (rot)  : Treffer, Schiff noch nicht versenkt
X (grau) : Treffer, Schiff versenkt


Dieses Programm lässt sich mit "make" kompilieren und starten. 
Sollte make nicht installiert sein, lässt sich der Code manuell über 

g++ -g -o SchiffeVersenken main.cpp Field.cpp Computer.cpp Save.cpp CppRandom.cpp

kompilieren und über

./SchiffeVersenken

starten.

