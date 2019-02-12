#ifndef ALGOGRAD4_H
#define ALGOGRAD4_H
#include <utility> 
#include "Knoten.h"
#include "Kante.h"
#include "Graph.h"
#include "Zielgraph.h"
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

struct Graphen{
	Graph * Startgraph;
	Zielgraph * Ziel;
};



class AlgoGrad4
{
	public:
		AlgoGrad4(Graph * Hauptgraph);
		
		//Graph * Hauptgraph;
		Zielgraph * Ziel;
		double	Bank;
		int D1C1;
		int D1C2;
		int D1C3;
		int D1C4;
		int D1C5;
		int D1C6;
		int D1C7;
		int D1C8;	
		int D2C1;
		int D2C2;
		int D2C3;
		int D2C4;
		int D2C5;
		int D2C6;
		int D2C7;
		int D2C8;
		int D2C9;
		int D3C1;
		int D3C2;
		int D3C3;
		int D3C4;
		int D4C1;
		int D4C2;
		int AS;
		
		void HaendleGraph(Graph * Hauptgraph);
						
	protected:
		void HaendleGrad1(Knoten * Zielknoten);
		void HaendleGrad2(Knoten * Zielknoten, Graph * Hauptgraph);
		void HaendleGrad3(Knoten * Zielknoten, Graph * Hauptgraph);
		void HaendleGrad4(Knoten * Zielknoten);
		void Ausgleichsschritt(Graph * Hauptgraph);
};

#endif
