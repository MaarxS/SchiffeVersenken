# Anleitung Schiffe Versenken

Bei diesem Projekt handelt es sich um ein Hochschulprojekt, welches im Rahmen einer C++ Vorlesung benotet werden soll.
Da es sich hier um ein Konsolenpogramm mit Farbausgabe handelt, wird empfohlen, eine Konsole zu verwenden, die escape- character 
unterstützt. Das fertige Programm zur Bewertung beschränkt sich auf den Main-Branch. Die anderen Branches sind unvollständig und noch in Entwicklung.


## Legende: 

■ (blau) : Meer, verdecktes Feld

■ (weiß) : Schiff (nur auf dem eigenen Feld zu sehen)

O (weiß) : Schuss ins Meer, kein Treffer

X (rot) : Treffer, Schiff noch nicht versenkt

X (grau) : Treffer, Schiff versenkt

## Compile:

Dieses Programm lässt sich mit "make" kompilieren und starten. 
Sollte make nicht installiert sein, lässt sich der Code manuell über 

g++ -g -o SchiffeVersenken Field.cpp Computer.cpp Save.cpp CppRandom.cpp Console.cpp Controller.cpp

kompilieren und über

./SchiffeVersenken

starten. Zum Kompilieren wurde g++ ab v8.3.0 verwendet.
