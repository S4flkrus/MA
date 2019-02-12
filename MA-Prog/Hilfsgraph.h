#ifndef HILFSGRAPH_H
#define HILFSGRAPH_H
#include "Hilfsknoten.h"

/*
Masterarbeit 

Autor:
Florian Kruschewski-Kursawe 
Universität Trier  
Fachbereich 4 Informatik 
Matrikelnummer 1023615  
s4flkrus@uni-trier.de 
*/

class Hilfsgraph
{
	public:
		Hilfsgraph(int id);
		
		Hilfsknoten * Startknoten;
		Hilfsknoten * Endknoten;
		int iD;
		
		void HilfsDrucken();
		void NeuerHilfsknoten(Knoten * Zielknoten);
		void AlleKnotenInZielgraph();
		void AlleKnotenLoeschen();
		void SErweitern(Hilfsgraph * T);
		void TErweitern(Hilfsgraph * T);
		int GetGroesse();
		
	protected:
};

#endif
