#ifndef HILFSKNOTEN_H
#define HILFSKNOTEN_H
#include "Knoten.h"


/*
Masterarbeit 

Autor:
Florian Kruschewski-Kursawe 
Universität Trier  
Fachbereich 4 Informatik 
Matrikelnummer 1023615  
s4flkrus@uni-trier.de 
*/


class Hilfsknoten
{
	public:
		Hilfsknoten(Knoten * knoten);
		
		Knoten * Speicher;
		Hilfsknoten * Next;
		Hilfsknoten * Prev;
		Hilfsknoten * Nachbarn;
		Hilfsknoten * LetzterNachbar;
		bool versorgt;
		
		void LoescheKnoten();
		void KnotenInZielgraph();
		void EntferneNachbar(Knoten * Nach);
		
	protected:
};

#endif
