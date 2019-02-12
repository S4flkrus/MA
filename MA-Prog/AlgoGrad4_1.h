#ifndef ALGOGRAD4_1_H
#define ALGOGRAD4_1_H
#include <utility> 
#include "Knoten.h"
#include "Kante.h"
#include "Graph.h"
#include "Zielgraph.h"

/*
Masterarbeit 

Autor:
Florian Kruschewski-Kursawe 
Universität Trier  
Fachbereich 4 Informatik 
Matrikelnummer 1023615  
s4flkrus@uni-trier.de 
*/
/*
struct Graphen{
	Graph * Startgraph;
	Zielgraph * Ziel;
};

*/

class AlgoGrad4_1
{
	public:
		AlgoGrad4_1(Graph * Hauptgraph);
		
		//Graph * Hauptgraph;
		Zielgraph * Ziel;
		int Bank;
		int D1;
		int D2C1;
		int D2C2;
		int D3C1;
		int D3C2;
		int D3C3;
		int D3C4;
		int D3C5;
		int Lab;

		
		void HaendleGraph(Graph * Hauptgraph);
						
	protected:
		void HaendleGrad2(Knoten * Zielknoten, Graph * Hauptgraph);
		void HaendleGrad3(Knoten * Zielknoten);
		/*
		bool GiltGrad2Fall1(Knoten * Zielknoten);
		bool GiltGrad3Fall1(Knoten * Zielknoten);
		bool GiltGrad3Fall2(Knoten * Zielknoten);
		bool GiltGrad3Fall3(Knoten * Zielknoten);
		bool GiltGrad3Fall4(Knoten * Zielknoten);*/
		
		void HaendleKnotenGrad1(Knoten * Zielknoten);
		void HaendleGrad2Fall1(Knoten * Zielknoten, Graph * Hauptgraph);
		void HaendleGrad2Fall2(Knoten * Zielknoten);
		void HaendleGrad3Fall1(Knoten * Zielknoten);
		void HaendleGrad3Fall2(Knoten * Zielknoten, Knoten * u, Knoten * w);
		void HaendleGrad3Fall3(Knoten * Zielknoten);
		void HaendleGrad3Fall4(Knoten * Zielknoten);
		void HaendleGrad3Fall5(Knoten * Zielknoten);
		void HaendleKnotenAusBank(Graph * Hauptgraph);
};

#endif

