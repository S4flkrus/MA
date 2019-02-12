#include "Kante.h"
#include "Knoten.h"
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

using namespace std;

Kante::Kante(Knoten * KnotenStart, Knoten * KnotenEnd){
	Knoten1 = KnotenStart;
	Knoten2 = KnotenEnd;
	Knoten1next = nullptr;
	Knoten2next = nullptr;
}
//Ebene 0
Knoten * Kante::GetNachbar(Knoten * Ausgangsknoten){
	if(Ausgangsknoten == Knoten1){
		return Knoten2;
	}
	if(Ausgangsknoten == Knoten2){
		return Knoten1;
	}
	else{
		return nullptr;
	}
}
//Ebene 0
Kante * Kante::GetNextKante(Knoten * Ausgangsknoten){
	if(Ausgangsknoten == Knoten1){
		return Knoten1next;
	}
	if(Ausgangsknoten == Knoten2){
		return Knoten2next ;
	}
	else{
		return nullptr;
	}		
}
//Ebene 0
bool Kante::IstNachbar(Knoten * Ausgangsknoten,Knoten * Nachbar){
	if(Ausgangsknoten == Knoten1 && Nachbar == Knoten2){
		return true;
	}
	if(Ausgangsknoten == Knoten2 && Nachbar == Knoten1){
		return true;
	}
	else{
		return false;
	}
}
//Ebene 0
void Kante::SetNextKante(Knoten * knoten,Kante * Ziel){
	if(knoten == Knoten1){
		Knoten1next = Ziel;
	}
	else if(knoten == Knoten2){
		Knoten2next = Ziel;
	}
}
//Ebene 0
void Kante::NachbarDrucken(Knoten * start){
	if(start == Knoten1){
		cout << Knoten2->ID << " ";
	}
	else if(start == Knoten2){
		cout << Knoten1->ID << " ";
	}
	if(start == Knoten1 && Knoten1next != nullptr){
		Knoten1next->NachbarDrucken(start);
	}
	else if(start == Knoten2 && Knoten2next != nullptr){
		Knoten2next->NachbarDrucken(start);
	}	
}
//Ebene 4
void Kante::KanteEntfernen(Knoten * Loeschknoten){
	if(Loeschknoten == Knoten1){
		Knoten2->KanteLoeschen(this);
	}	
	else{	
		Knoten1->KanteLoeschen(this);
	}
	delete(this);
}
//Ebene 0
void Kante::Nachbaruebertragen(Knoten * Ursprung, Knoten * Neu){
	if(Knoten1 == Ursprung){
		Knoten1next = nullptr;
		Knoten1 = Neu;
	}
	if(Knoten2 == Ursprung){
		Knoten2next = nullptr;
		Knoten2 = Neu;
	}
}

void Kante::KnotenAbdecken(){
	Knoten1->abgedeckt = true;
	Knoten2->abgedeckt = true;
}





	
