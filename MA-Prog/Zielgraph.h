#ifndef ZIELGRAPH_H
#define ZIELGRAPH_H
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

class Zielgraph
{
	public:		
		Zielgraph();
		
		double Faktor;
		int Exakt;
		int Approx;
		Knoten * Startknoten;
		Knoten * Letzterknoten;
		
		void GraphDrucken();
		void ZielGraphEntfernen();
		void FaktorBerechnen();

		
	protected:
};

#endif
