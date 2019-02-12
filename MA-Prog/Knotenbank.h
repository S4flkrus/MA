#ifndef KNOTENBANK_H
#define KNOTENBANK_H
#include "Element.h"

/*
Masterarbeit 

Autor:
Florian Kruschewski-Kursawe 
Universität Trier  
Fachbereich 4 Informatik 
Matrikelnummer 1023615  
s4flkrus@uni-trier.de 
*/

class Knotenbank
{
	public:
		Knotenbank();
		
		Element * StartElement;
		Element * EndElement;
		
		void BankDrucken();
		void NeuesElement(Knoten * Anker, Knoten * v, Knoten * w);
		void ElementEinfuegen(Element * Ziel);
		void ElementAnkerInZielgraph(Knoten * Ziel);
		void ElementAnkerLoeschen(Knoten * Ziel);
		void ListeInZielgraph();
		void ListeLoeschen();
		
	protected:
};

#endif
