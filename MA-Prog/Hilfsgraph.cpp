#include "Hilfsgraph.h"
#include "Kante.h"
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

Hilfsgraph::Hilfsgraph(int id){
	Startknoten = nullptr;

	iD = id;
}

//Ebene 0
void Hilfsgraph::HilfsDrucken(){
	Hilfsknoten * akt = Startknoten;
	while(akt != Endknoten){
		cout << akt->Speicher->ID << endl;
		akt = akt->Next;
	}
	cout << akt->Speicher->ID << endl;
}
//Ebene 0
void Hilfsgraph::NeuerHilfsknoten(Knoten * Zielknoten){
	if(Startknoten == nullptr){
		Startknoten = new Hilfsknoten(Zielknoten);
		Zielknoten->Hilfsgra = this;
		Endknoten = Startknoten;
	}
	else{
		Endknoten->Next = new Hilfsknoten(Zielknoten);
		Zielknoten->Hilfsgra = this;
		Endknoten = Endknoten->Next;
	}
}
//Ebene 7	
void Hilfsgraph::AlleKnotenInZielgraph(){
	if(Startknoten == nullptr){
		return;
	}
	Hilfsknoten * akt = Startknoten;
	Hilfsknoten * tmp = Startknoten;
	while(akt != Endknoten){
		tmp = akt->Next;
		akt->KnotenInZielgraph();
		akt = tmp;
	}
	akt->KnotenInZielgraph();
	delete(this);
}
//Ebene 7	
void Hilfsgraph::AlleKnotenLoeschen(){
	if(Startknoten == nullptr){
		return;
	}
	Hilfsknoten * akt = Startknoten;
	Hilfsknoten * tmp = Startknoten;
	while(akt != Endknoten){
		tmp = akt->Next;
		akt->Speicher->KnotenLoeschen();
		akt = tmp;
	}
	akt->Speicher->KnotenLoeschen();
	delete(this);
}
//Ebene 2	
void Hilfsgraph::SErweitern(Hilfsgraph * T){
	Hilfsknoten * akt = Startknoten;
	Kante * Akt;
	bool done = false;
	while(akt != nullptr){
		done = false;
		Akt = akt->Speicher->Startkante;
		while(Akt != nullptr && done == false){
			if(Akt->GetNachbar(akt->Speicher)->Hilfsgra == nullptr && Akt->GetNachbar(akt->Speicher)->GetAnzahlNachbarnAusserhalbVon(this) == 1){
				this->NeuerHilfsknoten(Akt->GetNachbar(akt->Speicher)->GetNachbarnAusserhalbVon(this));
				T->NeuerHilfsknoten(Akt->GetNachbar(akt->Speicher));
				done = true;
				}
			else{
				Akt = Akt->GetNextKante(akt->Speicher);
			}
		}
		if(done == true){
			akt = Startknoten;
		}
		else{
			akt = akt->Next;
		}
	}
}
//Ebene 2
void Hilfsgraph::TErweitern(Hilfsgraph * T){
	Hilfsknoten * akt = Startknoten;
	while(akt != nullptr){
		Kante * Akt = akt->Speicher->Startkante;
		while(Akt != nullptr){
			if(Akt->GetNachbar(akt->Speicher)->Hilfsgra == nullptr && Akt->GetNachbar(akt->Speicher)->GetAnzahlNachbarnAusserhalbVon(this) == 0){			
				T->NeuerHilfsknoten(Akt->GetNachbar(akt->Speicher));
			}
			else{
				Akt = Akt->GetNextKante(akt->Speicher);
			}
		}
		akt = akt->Next;
	}
}
//Ebene 0
int Hilfsgraph::GetGroesse(){
	int g = 0;
	if(Startknoten == nullptr){
		return g;
	}
	g++;
	if(Startknoten == Endknoten){
		return g;
	}
	Hilfsknoten * akt = Startknoten;
	while(akt != Endknoten){
		g++;
		akt = akt->Next;
	} 
	return g;
}



