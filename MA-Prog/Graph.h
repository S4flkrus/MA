#ifndef GRAPH_H
#define GRAPH_H
#include "zielgraph.h"
#include "Hilfsgraph.h"
#include "Hilfsliste.h"
#include "Knotenbank.h"
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

class Graph
{
	public:
		Graph(Zielgraph * ziel);
		
		int KnotenZahl;
		Knoten * Startknoten;
		Knoten * Endknoten;
		Knoten * Grad1;
		Knoten * Grad2;
		Knoten * Grad3;
		Knoten * Grad4;
		Knoten * Gradge5;
		Zielgraph * Ziel;
		Knotenbank * Bank;
		Hilfsliste * Hilf;
		
		void GraphDrucken();
		void KnotenEntfernen(Knoten * knoten);
		void KnotenEinsortieren(Knoten * knoten);	
		void GraphEntfernen();
		//void GraphPruefen();
		//void GraphTeilen();
		
	protected:
		
		
};

#endif
