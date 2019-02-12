#include "Element.h"
#include "Graph.h"
#include <iostream>

/*
Masterarbeit 

Autor:
Florian Kruschewski-Kursawe 
Universität Trier  
Fachbereich 4 Informatik 
Matrikelnummer 1023615  
s4flkrus@uni-trier.de 
*/

Element::Element(Knoten * Haendeln, Knoten * u, Knoten * w){
	Anker = Haendeln;
	Speicher1 = u;
	Speicher2 = w;
	NaechstesElement = nullptr;
}
//Ebene 0
void Element::ElementDrucken(){
	cout << "Anker: " << Anker->ID << " u: " << Speicher1->ID << " w: " << Speicher2->ID << endl;
	if(NaechstesElement != nullptr){
		NaechstesElement->ElementDrucken();
	}
}
//Ebene 6
void Element::LoescheAnker(){
	Speicher1->KnotenInZielgraph();
	Speicher2->KnotenLoeschen();
	Anker->Hauptgr->Ziel->Approx++;
    Anker->Hauptgr->Ziel->Exakt++;
    Anker->Hauptgr->Bank++;	
	delete(this);
}
//Ebene 6
void Element::AnkerInZielgraph(){
	Speicher2->KnotenInZielgraph();
    Speicher1->KnotenInZielgraph();
    Anker->Hauptgr->Ziel->Approx++;
	Anker->Hauptgr->Ziel->Approx++;
	Anker->Hauptgr->Ziel->Exakt++;
	Anker->Hauptgr->Bank++;	
	delete(this);
}
