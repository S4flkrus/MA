#ifndef ELEMENT_H
#define ELEMENT_H
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

class Element
{
	public:
		Element(Knoten * Haendeln, Knoten * u, Knoten * w);
		
		Knoten * Anker;
		Knoten * Speicher1;
		Knoten * Speicher2;
		Element * NaechstesElement;
		
		void ElementDrucken();
		void LoescheAnker();
		void AnkerInZielgraph();
		
	protected:
};

#endif
