#include "Hilfsknoten.h"
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

Hilfsknoten::Hilfsknoten(Knoten * knoten){
	Speicher = knoten;
	Next = nullptr;
	Prev = nullptr;
	Nachbarn = nullptr;
	LetzterNachbar = nullptr;
	versorgt = false;
}



//Ebene 7
void Hilfsknoten::LoescheKnoten(){
	Speicher->KnotenLoeschen();
}
//Ebene 7
void Hilfsknoten::KnotenInZielgraph(){
	Speicher->KnotenInZielgraph();
	versorgt = true;
}

/*void Hilfsknoten::LoescheHilfsknoten(){
	if(next != nullptr){
		next->loescheHilfsknoten();
	}
	delete(this);
}
*/
void Hilfsknoten::EntferneNachbar(Knoten * Nach){
	Hilfsknoten * akt;
	Hilfsknoten * tmp;
	if(Nachbarn != nullptr){
		akt = Nachbarn;
		tmp = Nachbarn;
		if (akt->Speicher == Nach){
			Nachbarn = akt->Next;
			delete(akt);
			return;
		}
		akt = akt->Next;
		while(akt != nullptr){
			if (akt->Speicher == Nach){
				if(akt == LetzterNachbar){
					LetzterNachbar = tmp;
					tmp->Next = nullptr;
					return;
				}
				tmp->Next = akt->Next;
				return;
			}
			tmp = akt;
			akt = akt->Next;
		}
	}
	if(Nachbarn == LetzterNachbar){
		Nachbarn->KnotenInZielgraph();
		this->KnotenInZielgraph();
	}
}
