#include "Graph.h"
#include "Knoten.h"
#include "AlgoGrad4.h"
#include <iostream>
#include <utility> 
#include <windows.h>
#include <vector>

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
	

Graph::Graph(Zielgraph * ziel){
	KnotenZahl = 0;
	Startknoten = nullptr;
	Endknoten = nullptr;
	Grad1 = nullptr;
	Grad2 = nullptr;
	Grad3 = nullptr;
	Grad4 = nullptr;
	Gradge5 = nullptr;
	Ziel = ziel;
	Bank = new Knotenbank;
	Hilf = new Hilfsliste;		
}
//Ebene 2
void Graph::GraphDrucken(){
	if(Startknoten != nullptr && KnotenZahl > 0){
		//Startknoten->KnotenDrucken();
	}
	else{
		cout << "Graph Empty ";
	}
}
//Ebene 0
void Graph::KnotenEntfernen(Knoten * knoten){
	if(knoten == Grad1){
		if(knoten->next != nullptr && knoten->next->Grad == 1){
			Grad1 = knoten->next;
		}
		else{
			Grad1 = nullptr;
		}
	}
	else if(knoten == Grad2){
		if(knoten->next != nullptr && knoten->next->Grad == 2){
			Grad2 = knoten->next;
		}
		else{
			Grad2 = nullptr;
		}
	}
	else if(knoten == Grad3){
		if(knoten->next != nullptr && knoten->next->Grad == 3){
			Grad3 = knoten->next;
		}
		else{
			Grad3 = nullptr;
		}
	}
	else if(knoten == Grad4){
		if(knoten->next != nullptr && knoten->next->Grad == 4){
			Grad4 = knoten->next;
		}
		else{
			Grad4 = nullptr;
		}
	}
	else if(knoten == Gradge5){
		if(knoten->next != nullptr && knoten->next->Grad >= 5){
			Gradge5 = knoten->next;
		}
		else{
			Gradge5 = nullptr;
		}
	}
	if(knoten == Startknoten && knoten == Endknoten){
		Startknoten = nullptr;
		Endknoten = nullptr;
	}
	else if(knoten->prev == nullptr && knoten->next == nullptr){
	}
	else if(knoten == Startknoten){
		Startknoten = knoten->next;
		Startknoten->prev = nullptr;
		knoten->next = nullptr;
	}
	
	else if(knoten == Endknoten){
		Endknoten = knoten->prev;
		Endknoten->next = nullptr;
		knoten->prev = nullptr;
	}
	else{
		if(knoten->prev != nullptr){
		knoten->prev->next = knoten->next;
		
		}
		if(knoten->next != nullptr){
		knoten->next->prev = knoten->prev;
		
		}
		knoten->prev = nullptr;
		knoten->next = nullptr;
	}
}
//Ebene 1
void Graph::KnotenEinsortieren(Knoten * knoten){
	KnotenEntfernen(knoten);
	if(knoten->Grad == 0){		
		return;
	}
	if(knoten->Grad == 1){
		if(Grad1 == nullptr){
			Grad1 = knoten;
			if(Startknoten->Grad > knoten->Grad){
				knoten->next = Startknoten;
				Startknoten->prev = knoten;
				Startknoten = knoten;
			}
			else if(Endknoten->Grad <= knoten->Grad){
				knoten->prev = Endknoten;
				Endknoten->next = knoten;
				Endknoten = knoten;
			}
		}
		else{
			if(Endknoten->Grad == 1){
				Endknoten->next = knoten;
				knoten->prev = Endknoten;
				Endknoten = knoten;
			}
			else if(Grad2 != nullptr){
				knoten->prev = Grad2->prev;
				knoten->next = Grad2;
				knoten->prev->next = knoten;
				Grad2->prev = knoten;				
			}
			else if(Grad3 != nullptr){
				knoten->prev = Grad3->prev;
				knoten->next = Grad3;
				knoten->prev->next = knoten;
				Grad3->prev = knoten;				
			}
			else if(Grad4 != nullptr){
				knoten->prev = Grad4->prev;
				knoten->next = Grad4;
				knoten->prev->next = knoten;
				Grad4->prev = knoten;				
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				knoten->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
		}
	}
	if(knoten->Grad == 2){
		if(Grad2 == nullptr){
			Grad2 = knoten;
			if(Startknoten->Grad > knoten->Grad){
				knoten->next = Startknoten;
				Startknoten->prev = knoten;
				Startknoten = knoten;
			}
			else if(Endknoten->Grad <= knoten->Grad){
				knoten->prev = Endknoten;
				Endknoten->next = knoten;
				Endknoten = knoten;
			}
			else if(Grad3 != nullptr){
				knoten->prev = Grad3->prev;
				knoten->next = Grad3;	
				Grad3->prev->next = knoten;
				Grad3->prev = knoten;	
						
			}
			else if(Grad4 != nullptr){
				knoten->prev = Grad4->prev;
				knoten->next = Grad4;
				Grad4->prev->next = knoten;
				Grad4->prev = knoten;				
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				Gradge5->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
			
			
		}
		else{
			if(Endknoten->Grad == 2){
				Endknoten->next = knoten;
				knoten->prev = Endknoten;
				Endknoten = knoten;
			}
			else if(Grad3 != nullptr){
				knoten->prev = Grad3->prev;
				knoten->next = Grad3;
				Grad3->prev->next = knoten;
				Grad3->prev = knoten;				
			}
			else if(Grad4 != nullptr){
				knoten->prev = Grad4->prev;
				knoten->next = Grad4;
				Grad4->prev->next = knoten;
				Grad4->prev = knoten;				
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				Gradge5->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
		}
	}
	if(knoten->Grad == 3){
		if(Grad3 == nullptr){
			Grad3 = knoten;
			if(Startknoten->Grad > knoten->Grad){
				knoten->next = Startknoten;
				Startknoten->prev = knoten;
				Startknoten = knoten;
			}
			else if(Endknoten->Grad <= knoten->Grad){
				knoten->prev = Endknoten;
				Endknoten->next = knoten;
				Endknoten = knoten;
			}
			else if(Grad4 != nullptr){
				knoten->prev = Grad4->prev;
				knoten->next = Grad4;
				Grad4->prev->next = knoten;
				Grad4->prev = knoten;				
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				Gradge5->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
		}
		else{
			if(Endknoten->Grad == 3){
				Endknoten->next = knoten;
				knoten->prev = Endknoten;
				Endknoten = knoten;
			}
			else if(Grad4 != nullptr){
				knoten->prev = Grad4->prev;
				knoten->next = Grad4;
				Grad4->prev->next = knoten;
				Grad4->prev = knoten;				
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				Gradge5->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
		}
	}
	if(knoten->Grad == 4){
		if(Grad4 == nullptr){
			Grad4 = knoten;
			if(Startknoten->Grad > knoten->Grad){
				knoten->next = Startknoten;
				Startknoten->prev = knoten;
				Startknoten = knoten;
			}
			else if(Endknoten->Grad <= knoten->Grad){
				knoten->prev = Endknoten;
				Endknoten->next = knoten;
				Endknoten = knoten;
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				Gradge5->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
		}
		else{
			if(Endknoten->Grad == 4){
				Endknoten->next = knoten;
				knoten->prev = Endknoten;
				Endknoten = knoten;
			}
			else if(Gradge5 != nullptr){
				knoten->prev = Gradge5->prev;
				knoten->next = Gradge5;
				Gradge5->prev->next = knoten;
				Gradge5->prev = knoten;				
			}
		}
	}
	if(knoten->Grad == 5){
		if(Gradge5 == nullptr){
			Gradge5 = knoten;
			if(Startknoten->Grad > knoten->Grad){
				knoten->next = Startknoten;
				Startknoten->prev = knoten;
				Startknoten = knoten;
			}
			else if(Endknoten->Grad <= knoten->Grad){
				knoten->prev = Endknoten;
				Endknoten->next = knoten;
				Endknoten = knoten;
			}
		}
		else{
			Endknoten->next = knoten;
			knoten->prev = Endknoten;
			Endknoten = knoten;
		}
	}
	if(knoten->prev == nullptr && knoten != Startknoten){
		Knoten * akt = Startknoten;
		while(akt != nullptr){
			if(akt->next == knoten){
				knoten->prev = akt;
				cout << "TeST" << endl;
			}
			akt = akt->next;
		}
	}
}	
//Ebene 1
void Graph::GraphEntfernen(){
	Startknoten->KnotenDeleten();
	delete(this);
}
/*
void Graph::GraphPruefen(){
	bool done = false;
	bool bipart = true;
	int i = 0;  
	int dis = 0; 
	Knoten * akt = Startknoten;
	Knoten * tmp;
	Kante * Akt; 
	akt->Entf = 0;
	akt->Bip = 0;
	vector<Knoten *> Help{};
	Help.push_back(akt);
	while(i < Help.size()){
		akt = Help[i];
		Akt = akt->Startkante;
		while(Akt->GetNextKante(akt) != nullptr ){
			tmp = Akt->GetNachbar(akt);
			if(tmp->Entf == -1){
				tmp->Entf = akt->Entf + 1;
				if(dis < tmp->Entf){
					dis = tmp->Entf;
				}
				Help.push_back(tmp);
			}
			if(bipart == true ){
				if(tmp->Bip == -1){
					if(akt->Bip == 0){
						tmp->Bip = 1;
					}
					else {
						tmp->Bip = 0;
					}
				}
				else if(tmp->Bip == akt->Bip){
					bipart = false;
				}
			}
			Akt = Akt->GetNextKante(akt);
		}
		i++;
	}
	akt = Startknoten;
	while(akt->next != nullptr){
		if(akt->Entf == -1){
			GraphTeilen();
			GraphPruefen();
			return;
		}
		akt = akt->next;		
	}	
	i = 0;
	while(i < Help.size()){
		Help[i]->Entf = -1;
		Help[i]->Bip = -1;
		i++;
	}
	Help.resize(0);
	akt = Startknoten;
	while(done == false){
		if(akt == Endknoten){
			done = true;
		}
		Help.push_back(akt);
		while(i < Help.size()){
			akt = Help[i];
			Akt = akt->Startkante;
			while(Akt->GetNextKante(akt) != nullptr ){
				tmp = Akt->GetNachbar(akt);
				if(tmp->Entf == -1){
					tmp->Entf = akt->Entf + 1;
					if(dis < tmp->Entf){
						dis = tmp->Entf;
					}
					Help.push_back(tmp);
				}
				if(bipart == true ){
					if(tmp->Bip == -1){
						if(akt->Bip == 0){
							tmp->Bip = 1;
						}
						else {
							tmp->Bip = 0;
						}
					}
					else if(tmp->Bip == akt->Bip){
						bipart = false;
					}
				}
				Akt = Akt->GetNextKante(akt);
			}
			i++;
		}	
		i = 0;
		while(i < Help.size()){
			Help[i]->Entf = -1;
			Help[i]->Bip = -1;
			i++;
		}
		Help.resize(0);	
		akt = akt->next;
	}
	cout << "Durchschnitt: " << dis; 
	if(bipart == true){
		cout << " Bipartit" << endl;
	}
	else{
		cout << endl;
	}
}

void Graph::GraphTeilen(){
	cout << " Split " << endl;
	Zielgraph * zielg = new Zielgraph();
	Graph * Hauptgr = new Graph(zielg);
	Knoten * akt = Startknoten;
	Knoten * tmp = akt->next;
	while(akt->next != nullptr){
		if(akt->Entf == -1){
			KnotenEntfernen(akt);
			Hauptgr->KnotenEinsortieren(akt);
			akt->Hauptgr = Hauptgr;
		}
		akt = tmp;
		tmp = akt->next;
	}
	if(akt->Entf == -1){
		KnotenEntfernen(akt);
		Hauptgr->KnotenEinsortieren(akt);
		akt->Hauptgr = Hauptgr;
	}
	AlgoGrad4_2 * Algo = new AlgoGrad4_2(Hauptgr);
	Algo->HaendleGraph(Hauptgr);
	Ziel->Exakt = Ziel->Exakt + zielg->Exakt;
	Ziel->Approx = Ziel->Approx + zielg->Approx;
	akt = zielg->Startknoten;
	tmp = akt->next;
	while(akt != zielg->Letzterknoten){
		if(this->Ziel->Startknoten != nullptr){
			akt->prev = this->Ziel->Letzterknoten;
			this->Ziel->Letzterknoten->next = akt;
			this->Ziel->Letzterknoten = akt;
			akt->next = nullptr;
		}
		else{
			this->Ziel->Startknoten = akt;
			this->Ziel->Letzterknoten = akt;
			akt->prev = nullptr;
			akt->next = nullptr;
		}
		akt = tmp;
		tmp = akt->next;
	}
	if(this->Ziel->Startknoten != nullptr){
			akt->prev = this->Ziel->Letzterknoten;
			this->Ziel->Letzterknoten->next = akt;
			this->Ziel->Letzterknoten = akt;
			akt->next = nullptr;
		}
		else{
			this->Ziel->Startknoten = akt;
			this->Ziel->Letzterknoten = akt;
			akt->prev = nullptr;
			akt->next = nullptr;
		}
	
}
*/





