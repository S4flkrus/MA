#include "Knoten.h"
#include "Kante.h"
#include "Graph.h"
#include <utility> 
#include <iostream>
#include <windows.h>

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

Knoten::Knoten(int id, Graph * Haupt){
	ID = id;
	Grad = 0;
	Entf = -1;
	Bip = 0;
	entfernt = false;
	next = nullptr;
	prev = nullptr;
	Startkante = nullptr;
	Letztekante = nullptr;
	BankAnker = nullptr;
	Hauptgr = Haupt;
	Hilfsgra = nullptr;
	Hilfskn = nullptr;
	abgedeckt = false;
}

Knoten::Knoten(int id, Knoten * vor, Graph * Haupt){
	ID = id;
	Grad = 0;
	Entf = -1;
	Bip = -1;
	entfernt = false;
	next = nullptr;
	prev = vor;
	Startkante = nullptr;
	Letztekante = nullptr;
	BankAnker = nullptr;
	Hauptgr = Haupt;
	Hilfsgra = nullptr;
	Hilfskn = nullptr;
	abgedeckt = false;
}
//Ebene 0
Knoten* Knoten::GetErstenNachbarn(){
	return Startkante->GetNachbar(this);
}
//Ebene 0	
Knoten* Knoten::GetLetztenNachbarn(){
	return Letztekante->GetNachbar(this);
}
//Ebene 2
Knoten * Knoten::IstTeilVonDreieck(){
	Kante * akt = Startkante;
	Kante * tmp;
	Knoten * Akt = akt->GetNachbar(this);
	while(akt->GetNextKante(this) != nullptr ){
		tmp = akt->GetNextKante(this);
		Akt = akt->GetNachbar(this);
		while(tmp->GetNextKante(this) != nullptr){
			if(Akt->IstNachbarVon(tmp->GetNachbar(this)) == true){
				return Akt;
			}
			else{
				tmp = tmp->GetNextKante(this);
			}
		}
		if(Akt->IstNachbarVon(tmp->GetNachbar(this)) == true){
			return Akt;
		}
		else{
			akt = akt->GetNextKante(this);
		}
		
	}
	
}
//Ebene 2	
Knoten* Knoten::IstTeilVonDreieck(Knoten * Nachbar){
	Kante * akt = Startkante;
	while(akt->GetNextKante(this) != nullptr){
		if(Nachbar != akt->GetNachbar(this) && Nachbar->IstNachbarVon(akt->GetNachbar(this)) == true){
			return akt->GetNachbar(this);
		}
		else{
			akt = akt->GetNextKante(this);
		}
	}
	if(Nachbar != akt->GetNachbar(this) && Nachbar->IstNachbarVon(akt->GetNachbar(this)) == true){
		return akt->GetNachbar(this);
	}
	else{
		return nullptr;
	}
}
//Ebene 1	
Knoten* Knoten::HatNachbarMitGrad(int GesuchterGrad){
	Kante * akt = Startkante;
	while(akt->GetNextKante(this) != nullptr){
		if(akt->GetNachbar(this)->Grad == GesuchterGrad){
			return akt->GetNachbar(this);
		}
	}
	return nullptr;
}
//Ebene 1

Knoten* Knoten::GetNachbarnAusserhalbVon(Hilfsgraph * H){
	Kante * akt = Startkante;
	while(akt != nullptr){
		if(akt->GetNachbar(this)->Hilfsgra == nullptr){
				return akt->GetNachbar(this);
		}
		akt = akt->GetNextKante(this);
	}
	return nullptr;
}

//Ebene 1
bool Knoten::IstNachbarVon(Knoten * Nachbar){
	Kante * akt = Startkante;
	while(akt->GetNextKante(this) != nullptr){
		if(akt->IstNachbar(this, Nachbar) == true){
			return true;
		}
		else{
			akt = akt->GetNextKante(this);
		}
	}
	if(akt->IstNachbar(this, Nachbar) == true){
			return true;
	}
	else{
		return false;
	}
}
//Ebene 3
void Knoten::KanteHinzufuegen(Kante * Ziel){
	if(Startkante == nullptr){
		Startkante = Ziel;
		Letztekante = Ziel;
	}
	else{
		Letztekante->SetNextKante(this, Ziel);
		Letztekante = Ziel;
	}
	this->GradErhoehen();
}
//Ebene 1
void Knoten::KnotenDrucken(){
/*	if(this->next != nullptr){
		cout << "KnotenID: " << this->ID << "Next: " << this->next->ID  << " Grad: " << this->Grad << " Nachbarn: ";
	}
	else{
		cout << "KnotenID: " << this->ID << "Next: " << "Ende "  << " Grad: " << this->Grad << " Nachbarn: ";
	}*/
	cout << this->ID << ": ";
	if(Startkante != nullptr){
		Startkante->NachbarDrucken(this);
	}
	cout << endl;
	if(next != nullptr){
		next->KnotenDrucken();
	}		
}
//Ebene 3
void Knoten::KanteLoeschen(Kante * Ziel){
	if(Ziel == Startkante){
		Startkante = Startkante->GetNextKante(this);
		this->GradReduzieren();
		if(Ziel == Letztekante){
			Letztekante = nullptr;
		}
		return;
	}
	Kante * akt = Startkante;
	Kante * tmp = Startkante->GetNextKante(this);
	while(tmp != Ziel){
		akt = tmp;
		tmp = akt->GetNextKante(this);
	}
	if(tmp == Letztekante){
		Letztekante = akt;
	}
	akt->SetNextKante(this, tmp->GetNextKante(this));
	this->GradReduzieren();
}
//Ebene 5
void Knoten::AlleKantenLoeschen(){
	if(Startkante != nullptr){
		Kante * tmp = Startkante;
		while(Startkante != nullptr){
			Startkante = tmp->GetNextKante(this);
			tmp->KanteEntfernen(this);
			tmp = Startkante;
		}
	}	
	Grad = 0;
}

void Knoten::AlleKantenLoeschenAbdecken(){
	if(Startkante != nullptr){
		Kante * tmp = Startkante;
		while(Startkante != nullptr){
			Startkante = tmp->GetNextKante(this);
			tmp->KnotenAbdecken();
			tmp->KanteEntfernen(this);
			tmp = Startkante;
		}
	}	
	Grad = 0;
}
//Ebene 6	
void Knoten::KnotenLoeschen(){
	//cout << "KnotenLoeschen: " << this->ID << endl;
		this->AlleKantenLoeschen();
		Hauptgr->KnotenEntfernen(this);
	if(BankAnker != nullptr){
	//	cout << this->ID << "del" << endl;
		Element * tmp = BankAnker;
		for(int i = 0; i<Bip; i++){
		//	cout << "Test" << endl;
			tmp->LoescheAnker();
			tmp = tmp->NaechstesElement;
		}
	}
	if(Hilfskn != nullptr && Hilfskn->versorgt == false){
		Hilfskn->EntferneNachbar(this);
		Hilfskn = nullptr;
	}
	Hauptgr->KnotenZahl--;
	delete (this);
	}
//Ebene 6	
void Knoten::KnotenInZielgraph(){
	//cout << "KnotenInZielgraph: " << this->ID << endl;
		this->AlleKantenLoeschenAbdecken();
		Hauptgr->KnotenEntfernen(this);
	if(Hauptgr->Ziel->Startknoten != nullptr){
		prev = Hauptgr->Ziel->Letzterknoten;
		Hauptgr->Ziel->Letzterknoten->next = this;
		Hauptgr->Ziel->Letzterknoten = this;
		next = nullptr;
	}
	else{
		Hauptgr->Ziel->Startknoten = this;
		Hauptgr->Ziel->Letzterknoten = this;
		prev = nullptr;
		next = nullptr;
	}
	if(BankAnker != nullptr){
	//	cout << this->ID << "Ziel" << endl;
		Element * tmp = BankAnker;
		for(int i; i<Bip; i++){
		//	cout << "Test1"<< tmp->Anker->ID << endl;
			tmp->AnkerInZielgraph();
			tmp = tmp->NaechstesElement;
		}
	}
	if(Hilfskn != nullptr && Hilfskn->versorgt == false){
		Hilfskn->KnotenInZielgraph();
		Hilfskn = nullptr;
	}
	Hauptgr->KnotenZahl--;
	Hauptgr = nullptr;
}
//Ebene 6
void Knoten::KnotenAusGraphEntfernen(){
	this->AlleKantenLoeschen();
	Hauptgr->KnotenEntfernen(this);
	entfernt = true;
}

bool Knoten::KnotenInHilfsliste(){	
	Hilfsknoten * hilfsknoten = new Hilfsknoten(this);
	Hilfsknoten * tmp;
	Kante * akt = this->Startkante;
	while(akt != nullptr){	
		tmp = new Hilfsknoten(akt->GetNachbar(this));
		if(akt->GetNachbar(this)->Hilfskn == nullptr || akt->GetNachbar(this)->Hilfskn->versorgt == true){
			akt->GetNachbar(this)->Hilfskn = hilfsknoten;
		}
		else{
			hilfsknoten->versorgt = true;
			akt->GetNachbar(this)->KnotenInZielgraph();
			this->KnotenInZielgraph();
			return true;
		}
		if(akt->GetNachbar(this)->Hilfskn->Nachbarn == nullptr){
			akt->GetNachbar(this)->Hilfskn->Nachbarn = tmp;
			akt->GetNachbar(this)->Hilfskn->LetzterNachbar = tmp;
		}
		else{
			akt->GetNachbar(this)->Hilfskn->LetzterNachbar->Next = tmp;
			akt->GetNachbar(this)->Hilfskn->LetzterNachbar = tmp;
		}
		akt = akt->GetNextKante(this);
	}
	this->AlleKantenLoeschenAbdecken();
	Hauptgr->KnotenEntfernen(this);
	entfernt = true;
	return false;
}
//Ebene 3
void Knoten::Kantenuebertragen(Knoten * Loeschknoten){
	Kante * akt = Loeschknoten->Startkante;
	Kante * tmp = akt->GetNextKante(Loeschknoten);
	Kante * TMP = nullptr;
	bool set;
	while(akt != nullptr && akt->GetNachbar(Loeschknoten) != this && this->IstNachbarVon(akt->GetNachbar(Loeschknoten)) == false){
		akt->Nachbaruebertragen(Loeschknoten, this);
		Letztekante->SetNextKante(this, akt);
		Letztekante = akt;
		this->GradErhoehen();
		Loeschknoten->GradReduzieren();
		Loeschknoten->Startkante = tmp;
		akt = tmp;
		if(akt != nullptr){
			tmp = akt->GetNextKante(Loeschknoten);	
		}
	}
	TMP = Loeschknoten->Startkante;
	akt = TMP->GetNextKante(Loeschknoten);
	if(akt != nullptr){
		tmp = akt->GetNextKante(Loeschknoten);
		while(akt != nullptr){
			set = false;
			if(akt->GetNachbar(Loeschknoten) != this && this->IstNachbarVon(akt->GetNachbar(Loeschknoten)) == false){
				TMP->SetNextKante(Loeschknoten, tmp);
				set = true;
				akt->Nachbaruebertragen(Loeschknoten, this);
				Letztekante->SetNextKante(this, akt);
				Letztekante = akt;
				this->GradErhoehen();
				Loeschknoten->GradReduzieren();
			}
			akt = tmp;
			if(akt != nullptr){
				tmp = akt->GetNextKante(Loeschknoten);	
			}
			if(set == false){
				TMP = TMP->GetNextKante(Loeschknoten);
			}
		}
	}
}
//Ebene 7	
void Knoten::HoechstesPaarInZielgraph(){
	Kante * akt = Startkante;
	Kante * tmp = Startkante;
	int max = akt->GetNachbar(this)->Grad;
	while(akt != nullptr){
		if(akt->GetNachbar(this)->Grad > max){
			max = akt->GetNachbar(this)->Grad;
			tmp = akt;
		}
		akt = akt->GetNextKante(this);
	}
	tmp->GetNachbar(this)->KnotenInZielgraph();
	this->KnotenInZielgraph();
}
//Ebene 2	
void Knoten::GradReduzieren(){
	Grad--;
	if(Grad < 5){
		Hauptgr->KnotenEinsortieren(this);
	}
}
//Ebene 2		
void Knoten::GradErhoehen(){
	Grad++;
	if(Grad < 6){
		Hauptgr->KnotenEinsortieren(this);
	}
}
//Ebene 1

int Knoten::GetAnzahlNachbarnAusserhalbVon(Hilfsgraph * H){
	Kante * akt = Startkante;
	int Anz = 0;
	int id = H->iD;
	while(akt != nullptr){
		if(akt->GetNachbar(this)->Hilfsgra != nullptr){
			if(akt->GetNachbar(this)->Hilfsgra->iD != H->iD){
				Anz++;
			}
		}
		else{
			Anz++;
		}
		akt = akt->GetNextKante(this);
	}

	return Anz;
}

//Ebene 0
void Knoten::KnotenDeleten(){
	if(next != nullptr){
		next->KnotenDeleten();
	}
	delete(this);
}


