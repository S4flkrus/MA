#include "Knotenbank.h"
#include "Graph.h"
#include <iostream>
#include <utility> 
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

Knotenbank::Knotenbank(){
	StartElement = nullptr;
	EndElement = nullptr;
}
//Ebene 1
void Knotenbank::BankDrucken(){
	if(StartElement != nullptr){
		StartElement->ElementDrucken();
	}
	else{
		cout << "BankEmpty" << endl;
	}
}
//Ebene 0
void Knotenbank::NeuesElement(Knoten * Anker, Knoten * v, Knoten * w){
	if(StartElement == nullptr){
		StartElement = new Element(Anker, v, w);
		EndElement = StartElement;
		//Anker->BankAnker = true;
	}
	else{
		EndElement->NaechstesElement = new Element(Anker, v, w);
		EndElement = EndElement->NaechstesElement;
	//	Anker->BankAnker = true;
	}
	BankDrucken();
}

void Knotenbank::ElementEinfuegen(Element * Ziel){
		if(StartElement == nullptr){
		StartElement = Ziel;
		EndElement = StartElement;
	}
	else{
		EndElement->NaechstesElement = Ziel;
		EndElement = EndElement->NaechstesElement;
	}
	
	
}
//Ebene 6	
void Knotenbank::ElementAnkerInZielgraph(Knoten * Ziel){
	Element * akt = StartElement;
	Element * tmp;
	Knotenbank * Tmp = new Knotenbank;
/*	if(EndElement == StartElement && StartElement->Anker == Ziel){
		//StartElement->LoescheAnker();
		TMP->ElementEinfuegen(akt);
		EndElement = nullptr;
		StartElement = nullptr;
		delete(akt);
	} */
	while(akt != nullptr){
		cout << "step" << endl;
		if(EndElement == StartElement && StartElement->Anker == Ziel){
			//StartElement->AnkerInZielgraph();
			Tmp->ElementEinfuegen(akt);
			EndElement = nullptr;
			StartElement = nullptr;
			akt = nullptr;
		}
		else if(StartElement->Anker == Ziel){
			akt = StartElement;
			StartElement = StartElement->NaechstesElement;
			//akt->AnkerInZielgraph();
			Tmp->ElementEinfuegen(akt);
			akt = StartElement;
		}
		else if(akt->Anker == Ziel && akt == EndElement){
			EndElement = tmp;
			tmp->NaechstesElement = nullptr;
			//akt->AnkerInZielgraph();
			Tmp->ElementEinfuegen(akt);
			akt = nullptr;
		}
		else{
			if(akt->Anker == Ziel){
				tmp->NaechstesElement = akt->NaechstesElement;
				//akt->AnkerInZielgraph();
				Tmp->ElementEinfuegen(akt);
				akt = tmp->NaechstesElement;
			}	
			else{
				tmp = akt;
				akt = akt->NaechstesElement;
			}
		}
	}
	Tmp->ListeInZielgraph();
	BankDrucken();
}
//Ebene 6
void Knotenbank::ElementAnkerLoeschen(Knoten * Ziel){
	Element * akt = StartElement;
	Element * tmp;
	Knotenbank * Tmp = new Knotenbank;
/*	if(EndElement == StartElement && StartElement->Anker == Ziel){
		//StartElement->LoescheAnker();
		TMP->ElementEinfuegen(akt);
		EndElement = nullptr;
		StartElement = nullptr;
		delete(akt);
	} */
	while(akt != nullptr){
		if(EndElement == StartElement && StartElement->Anker == Ziel){
			//StartElement->AnkerInZielgraph();
			Tmp->ElementEinfuegen(akt);
			EndElement = nullptr;
			StartElement = nullptr;
			akt = nullptr;
		}
		else if(StartElement->Anker == Ziel){
			akt = StartElement;
			StartElement = StartElement->NaechstesElement;
			//akt->AnkerInZielgraph();
			Tmp->ElementEinfuegen(akt);
			akt = StartElement;
		}
		else if(akt->Anker == Ziel && akt == EndElement){
			EndElement = tmp;
			tmp->NaechstesElement = nullptr;
			//akt->AnkerInZielgraph();
			Tmp->ElementEinfuegen(akt);
			akt = nullptr;
		}
		else{
			if(akt->Anker == Ziel){
				tmp->NaechstesElement = akt->NaechstesElement;
				//akt->AnkerInZielgraph();
				Tmp->ElementEinfuegen(akt);
				akt = tmp->NaechstesElement;
			}	
			else{
				tmp = akt;
				akt = akt->NaechstesElement;
			}
		}
	}
	Tmp->ListeLoeschen();
	BankDrucken();
}

	
void Knotenbank::ListeInZielgraph(){
	Element * akt = StartElement;
	while(akt != EndElement){
		StartElement = StartElement->NaechstesElement;
		akt->AnkerInZielgraph();		
		akt = StartElement;	
	}
	EndElement->AnkerInZielgraph();
	delete(this);
}

	
	
void Knotenbank::ListeLoeschen(){
	Element * akt = StartElement;
	while(akt != EndElement){
		StartElement = StartElement->NaechstesElement;
		akt->LoescheAnker();		
		akt = StartElement;	
	}
	EndElement->LoescheAnker();
	delete(this);	
}	
	
