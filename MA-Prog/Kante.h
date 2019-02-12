#ifndef KANTE_H
#define KANTE_H
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

using namespace std;

class Kante
{
	public:
		Kante(Knoten * KnotenStart, Knoten * KnotenEnd);
		
		Knoten * Knoten1;
		Knoten * Knoten2;
		Kante * Knoten1next;
		Kante * Knoten2next;
			
		Knoten * GetNachbar(Knoten * Ausgangsknoten);
		Kante * GetNextKante(Knoten * Ausgangsknoten);
		bool IstNachbar(Knoten * Ausgangsknoten,Knoten * Nachbar);
		void SetNextKante(Knoten * knoten,Kante * Ziel);
		void NachbarDrucken(Knoten * start);
		void KanteEntfernen(Knoten * Loeschknoten);
		void Nachbaruebertragen(Knoten * Ursprung, Knoten * Neu);
		void KnotenAbdecken();
		
	protected:
};

#endif
