#include "AlgoGrad4_1.h"
#include "Knoten.h"
#include "Kante.h"
#include "Graph.h"
#include "Zielgraph.h"
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


AlgoGrad4_1::AlgoGrad4_1(Graph * Hauptgraph){
	Ziel = Hauptgraph->Ziel;
	D1 = 0;
	D2C1 = 0;
	D2C2 = 0;
	D3C1 = 0;
	D3C2 = 0;
	D3C3 = 0;
	D3C4 = 0;
	D3C5 = 0;
	Lab = 0;
}	
//Ebene 10
void AlgoGrad4_1::HaendleGraph(Graph * Hauptgraph){	
	Knoten * akt = Hauptgraph->Startknoten;
    while(Hauptgraph->Startknoten != nullptr && akt->Grad < 2){
		if(akt->Grad == 0){
			akt->KnotenLoeschen();
			akt = Hauptgraph->Startknoten;	
		}
		else{
			HaendleKnotenGrad1(akt);
			akt = Hauptgraph->Startknoten;				
		}
	}
	int Fall;
	akt = Hauptgraph->Startknoten;
	Knoten * Hilfsknoten;
	while(Hauptgraph->Startknoten != nullptr){
		/*if(Hauptgraph->Grad2 == nullptr && Hauptgraph->Grad3 == nullptr && Bank == 0){
			break;
		}*/
		if(Hauptgraph->Startknoten->Grad == 2){
			HaendleGrad2(Hauptgraph->Startknoten, Hauptgraph);
		}
		else if(Hauptgraph->Startknoten->Grad == 3){
			HaendleGrad3(Hauptgraph->Startknoten);
		}
		else {
			HaendleKnotenAusBank(Hauptgraph);
		}			
	}
	//cout << "Durchlauf erledigt" << endl;
	Hauptgraph->GraphDrucken();
	//cout << "Überdeckung: " << endl;
	Ziel->GraphDrucken();
	cout << " vertices_left: "<< Hauptgraph->KnotenZahl;
	if(Hauptgraph->Bank->StartElement != nullptr){
		cout << " BankNotEmpty ";
		//Hauptgraph->Bank->BankDrucken();
	} 
	//cout << " D1: " << D1 << " D2C1: " << D2C1 << " D2C2: " << D2C2 << " D3C1: " << D3C1 << " D3C2: " << D3C2 << " D3C3: " << D3C3 << " D3C4: " << D3C4 << " D3C5: " << D3C5 << " Label: " << Lab;
	return;
	
}

void AlgoGrad4_1::HaendleGrad2(Knoten * Zielknoten, Graph * Hauptgraph){
	if(Zielknoten->IstTeilVonDreieck(Zielknoten->GetErstenNachbarn()) != nullptr){
		HaendleGrad2Fall2(Zielknoten);
		return;
	}
	Knoten * tmp = Zielknoten->GetErstenNachbarn();
	Knoten * akt = Zielknoten->GetLetztenNachbarn();
	Kante * Akt = tmp->Startkante;
	while(Akt != nullptr){
		if(tmp->Grad == 2 && akt->Grad == 2 && Akt->GetNachbar(tmp) != Zielknoten && Akt->GetNachbar(tmp)->IstNachbarVon(akt) == true){
			HaendleGrad2Fall2(Zielknoten);
			return;
		}
		else if(Akt->GetNachbar(tmp) != Zielknoten && Akt->GetNachbar(tmp)->Grad == 2 && Akt->GetNachbar(tmp)->IstNachbarVon(akt) == true){
			HaendleGrad2Fall2(Zielknoten);
			return;
		}
		else{
			Akt = Akt->GetNextKante(tmp);
		}
	} 
    HaendleGrad2Fall1(Zielknoten, Hauptgraph);
}

void AlgoGrad4_1::HaendleGrad3(Knoten * Zielknoten){
	Knoten * akt = Zielknoten->IstTeilVonDreieck();
	Knoten * tmp;
	Knoten * Tmp;
	Kante * Akt;
	if(akt == nullptr){
		HaendleGrad3Fall4(Zielknoten);
		return;
	}
	tmp = Zielknoten->IstTeilVonDreieck(akt);
	if(akt == Zielknoten->GetErstenNachbarn()){
		if(tmp == Zielknoten->Letztekante->GetNachbar(Zielknoten)){
			Tmp = Zielknoten->Startkante->GetNextKante(Zielknoten)->GetNachbar(Zielknoten);
			if(Tmp->IstNachbarVon(akt) == true || Tmp->IstNachbarVon(tmp) == true){
				HaendleGrad3Fall1(Zielknoten);
				return;
			}
		}
		else{
			Tmp = Zielknoten->Letztekante->GetNachbar(Zielknoten);
			if(Tmp->IstNachbarVon(akt) == true || Tmp->IstNachbarVon(tmp) == true){
				HaendleGrad3Fall1(Zielknoten);
				return;
			}
		}
	}
	if(akt->Grad == 3){
		Akt = akt->Startkante;
		Tmp = Akt->GetNachbar(akt);
		while(Akt != nullptr){
			Tmp = Akt->GetNachbar(akt);
			if(Tmp != tmp && Tmp != Zielknoten && Tmp->IstNachbarVon(tmp) == true){
					HaendleGrad3Fall1(akt);
					return;
			}
			Akt = Akt->GetNextKante(akt);
		}
		HaendleGrad3Fall2(Zielknoten, akt, tmp);
		return;
	}
	if(tmp->Grad == 3){
		Akt = tmp->Startkante;
		Tmp = Akt->GetNachbar(tmp);
		while(Akt != nullptr){
			Tmp = Akt->GetNachbar(tmp);
			if(Tmp != akt && Tmp != Zielknoten && Tmp->IstNachbarVon(akt) == true){
					HaendleGrad3Fall1(tmp);
					return;
			}
			Akt = Akt->GetNextKante(tmp);
		}
		HaendleGrad3Fall2(Zielknoten, akt, tmp);
		return;
	}
	Akt = akt->Startkante;
	Tmp = Akt->GetNachbar(akt);
	while(Akt != nullptr){
		Tmp = Akt->GetNachbar(akt);
		if(Tmp != tmp && Tmp != Zielknoten && Tmp->Grad == 3 && Tmp->IstNachbarVon(tmp) == true){
				HaendleGrad3Fall3(Zielknoten);
				return;
		}
		Akt = Akt->GetNextKante(akt);
	}
	HaendleGrad3Fall2(Zielknoten, akt, tmp);
	return;	
	
}

//Ebene 7
void AlgoGrad4_1::HaendleKnotenGrad1(Knoten * Zielknoten){
	//cout << "Grad1  " << "Fall1" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	Knoten * akt = Zielknoten->GetErstenNachbarn();
	Kante * Akt = akt->Startkante;
	Kante * tmp = nullptr;
	while(Akt->GetNextKante(akt) != nullptr){
		if(Akt->GetNachbar(akt)->Grad == 1){
			tmp = Akt->GetNextKante(akt);
			Akt->GetNachbar(akt)->KnotenLoeschen();
			Akt = tmp;
		}
		else{
			Akt = Akt->GetNextKante(akt);
		}
		
	}
	if(Akt->GetNachbar(akt)->Grad == 1){
		Akt->GetNachbar(akt)->KnotenLoeschen();
	}
	akt->KnotenInZielgraph();
	Bank++;
	Ziel->Approx++;
	Ziel->Exakt++;
	D1++;
	}
//Ebene 7
void AlgoGrad4_1::HaendleGrad2Fall1(Knoten * Zielknoten, Graph * Hauptgraph){
	//cout << "Grad2  " << "Fall1" << endl; 
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	Hauptgraph->Bank->NeuesElement(Zielknoten->GetErstenNachbarn(), Zielknoten, Zielknoten->GetLetztenNachbarn());
	Zielknoten->GetErstenNachbarn()->Kantenuebertragen(Zielknoten->GetLetztenNachbarn());
	Knoten * tmp = Zielknoten->GetLetztenNachbarn();
	tmp->AlleKantenLoeschen();		
	tmp->KnotenAusGraphEntfernen();
	Zielknoten->AlleKantenLoeschen();
	Zielknoten->KnotenAusGraphEntfernen();
	Bank++;
	D2C1++;
}
//Ebene 8
void AlgoGrad4_1::HaendleGrad2Fall2(Knoten * Zielknoten){
	//cout << "Grad2  " << "Fall2" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	if(Zielknoten->GetErstenNachbarn()->Grad == 2 && Zielknoten->GetLetztenNachbarn()->Grad == 2){
		if(Zielknoten->GetErstenNachbarn()->GetErstenNachbarn() != Zielknoten){
			if(Zielknoten->GetErstenNachbarn()->GetErstenNachbarn()->Grad > 2 && Zielknoten->GetErstenNachbarn()->GetErstenNachbarn()->IstNachbarVon(Zielknoten->GetLetztenNachbarn()) == true){
				HaendleGrad2Fall2(Zielknoten->GetErstenNachbarn());
				return;
			}
		}
		else{
			if(Zielknoten->GetErstenNachbarn()->GetLetztenNachbarn()->Grad > 2 && Zielknoten->GetErstenNachbarn()->GetLetztenNachbarn()->IstNachbarVon(Zielknoten->GetLetztenNachbarn()) == true){
				HaendleGrad2Fall2(Zielknoten->GetErstenNachbarn());
				return;
			}
		}
	}
	Hilfsgraph * S = new Hilfsgraph(1);
	Hilfsgraph * T = new Hilfsgraph(2);
	S->NeuerHilfsknoten(Zielknoten->GetErstenNachbarn());
	S->NeuerHilfsknoten(Zielknoten->GetLetztenNachbarn());
	Knoten * tmp = Zielknoten->GetErstenNachbarn();
	Kante * akt = tmp->Startkante;
	while(akt != tmp->Letztekante){
		if(akt->GetNachbar(tmp)->Grad == 2 && akt->GetNachbar(tmp)->IstNachbarVon(Zielknoten->GetLetztenNachbarn()) == true){
			T->NeuerHilfsknoten(akt->GetNachbar(tmp));
		} 
		akt = akt->GetNextKante(tmp);
	}
	if(akt->GetNachbar(tmp)->Grad == 2 && akt->GetNachbar(tmp)->IstNachbarVon(Zielknoten->GetLetztenNachbarn()) == true){
			T->NeuerHilfsknoten(akt->GetNachbar(tmp));
	} 
	S->SErweitern(T);
	S->TErweitern(T);
	int x = S->GetGroesse();
	Bank = Bank + x;
	Ziel->Approx = Ziel->Approx + x;
	Ziel->Exakt = Ziel->Exakt +x;
	T->AlleKnotenLoeschen();
	S->AlleKnotenInZielgraph();
	D2C2++;


}
//Ebene 7
void AlgoGrad4_1::HaendleGrad3Fall1(Knoten * Zielknoten){
	//cout << "Grad3  " << "Fall1" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	if(Zielknoten->GetErstenNachbarn()->IstNachbarVon(Zielknoten->Startkante->GetNextKante(Zielknoten)->GetNachbar(Zielknoten)) == true &&
	Zielknoten->GetErstenNachbarn()->IstNachbarVon(Zielknoten->GetLetztenNachbarn()) == true){
		Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();		
	}
	else if(Zielknoten->Startkante->GetNextKante(Zielknoten)->GetNachbar(Zielknoten)->IstNachbarVon(Zielknoten->GetLetztenNachbarn()) == true &&
	Zielknoten->GetErstenNachbarn()->IstNachbarVon(Zielknoten->Startkante->GetNextKante(Zielknoten)->GetNachbar(Zielknoten)) == true){
		Zielknoten->Startkante->GetNextKante(Zielknoten)->GetNachbar(Zielknoten)->KnotenInZielgraph();
	}
	else {
		Zielknoten->GetLetztenNachbarn()->KnotenInZielgraph();
	}
	Bank++;
	Ziel->Approx++;
	Ziel->Exakt++;	
	D3C1++;
}
//Ebene 7
void AlgoGrad4_1::HaendleGrad3Fall2(Knoten * Zielknoten, Knoten * u, Knoten * w){
	//cout << "Grad3  " << "Fall2" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	Knoten * akt = u;
	Knoten * tmp = w;
	Zielknoten->KnotenInZielgraph();
	tmp->KnotenInZielgraph();
	akt->KnotenInZielgraph();
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	Ziel->Exakt++;
	D3C2++;
}

void AlgoGrad4_1::HaendleGrad3Fall3(Knoten * Zielknoten){
	//cout << "Grad3  " << "Fall3" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	Knoten * akt = nullptr;
	Knoten * tmp = nullptr;
	akt = Zielknoten->IstTeilVonDreieck();
	tmp = Zielknoten->IstTeilVonDreieck(akt);
	Kante * Akt = akt->Startkante;
	bool erledigt = false;
	while(Akt != nullptr && erledigt == false){
		if(Akt->GetNachbar(akt) != Zielknoten && Akt->GetNachbar(akt) != tmp){
			Kante * Tmp = Akt->GetNachbar(akt)->Startkante;
			while(Tmp != nullptr){
				if(Tmp->GetNachbar(Akt->GetNachbar(akt))->Grad == 3 && Tmp->GetNachbar(Akt->GetNachbar(akt))->IstNachbarVon(akt) == true){
					Akt = Akt->GetNextKante(akt);
					break;
				}
				else{
					Tmp = Tmp->GetNextKante(Akt->GetNachbar(akt));
				}
			}
			if(Tmp == nullptr){
				Akt->GetNachbar(akt)->KnotenInZielgraph();
				akt->KnotenInZielgraph();
				erledigt = true;
			}
		}
		else{
			Akt = Akt->GetNextKante(akt);
		}
	}	
	Akt = tmp->Startkante;
	while(Akt != nullptr && erledigt == false){
		if(Akt->GetNachbar(tmp) != Zielknoten && Akt->GetNachbar(tmp) != tmp){
			Kante * Tmp = Akt->GetNachbar(tmp)->Startkante;
			while(Tmp != nullptr){
				if(Tmp->GetNachbar(Akt->GetNachbar(tmp))->Grad == 3 && Tmp->GetNachbar(Akt->GetNachbar(tmp))->IstNachbarVon(tmp) == true){
					Akt = Akt->GetNextKante(tmp);
					break;
				}
				else{
					Tmp = Tmp->GetNextKante(Akt->GetNachbar(tmp));
				}
			}
			if(Tmp == nullptr){
				Akt->GetNachbar(tmp)->KnotenInZielgraph();
				tmp->KnotenInZielgraph();
				erledigt = true;
			}
		}
		else{
			Akt = Akt->GetNextKante(tmp);
		}
	}	
	if(erledigt == false){
		Zielknoten->KnotenInZielgraph();
		akt->KnotenInZielgraph();
	}
	Bank--;
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	D3C3++;
}

void AlgoGrad4_1::HaendleGrad3Fall4(Knoten * Zielknoten){
	//cout << "Grad3  " << "Fall4" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	Kante * tmp = Zielknoten->Startkante;
	Knoten * akt = tmp->GetNachbar(Zielknoten);
	int max = akt->Grad;
	while( tmp != nullptr){
		if(tmp->GetNachbar(Zielknoten)->Grad > max){
			akt = tmp->GetNachbar(Zielknoten);
			max = akt->Grad;
		}
		tmp = tmp->GetNextKante(Zielknoten);
	}
	Knoten * Akt = nullptr;
	if(akt->GetErstenNachbarn() != Zielknoten){
		Akt = akt->GetErstenNachbarn();
	}
	else{
		Akt = akt->Startkante->GetNextKante(akt)->GetNachbar(akt);
	}
	max = Akt->Grad;
	tmp = akt->Startkante;
	while( tmp != nullptr){
		if(tmp->GetNachbar(akt)->Grad > max && tmp->GetNachbar(akt) != Zielknoten){
			Akt = tmp->GetNachbar(akt);
			max = Akt->Grad;
		}
		tmp = tmp->GetNextKante(akt);
	}	
	
	//Änderung:
	//Akt->KnotenDrucken();
	//akt->KnotenDrucken();
	Kante * Tmp = Akt->Startkante;
	/*while(Tmp != nullptr){
		Tmp->GetNachbar(Akt)->KnotenDrucken();
		Tmp = Tmp->GetNextKante(Akt);
	}
	Tmp = akt->Startkante;
	while(Tmp != nullptr){
		Tmp->GetNachbar(akt)->KnotenDrucken();
		Tmp = Tmp->GetNextKante(akt);
	}
	*/
	
	while(Tmp != nullptr){
		if(Tmp->GetNachbar(Akt)->Grad == 3 && Tmp->GetNachbar(Akt)->IstNachbarVon(akt) == true){
			this->HaendleGrad3(Tmp->GetNachbar(Akt));
			return;
		}	
		Tmp = Tmp->GetNextKante(Akt);	
	}	
	//ENDE
	
	Akt->KnotenInZielgraph();
	akt->KnotenInZielgraph();	
	Bank--;
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	D3C4++;
}
//Ebene 7
void AlgoGrad4_1::HaendleGrad3Fall5(Knoten * Zielknoten){
	//cout << "Grad3  " << "Fall5" << endl;
	//cout << "ZielknotenID: " << Zielknoten->ID << endl;
	Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
	Zielknoten->KnotenInZielgraph();
	Bank--;	
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	D3C5++;
}
//Ebene 8	
void AlgoGrad4_1::HaendleKnotenAusBank(Graph * Hauptgraph){
	//cout << "Grad4  " << "Fall1" << endl;
	if(Hauptgraph->Gradge5 != nullptr){
		Knoten * akt = Hauptgraph->Gradge5;
		Knoten * tmp = Hauptgraph->Gradge5;
		int max = tmp->Grad;
		while(akt != nullptr){
			if(akt->Grad > max){
				max = akt->Grad;
				tmp = akt;
			}
			akt = akt->next;
		}
		tmp->HoechstesPaarInZielgraph();
	}
	else{
		Knoten * akt = Hauptgraph->Startknoten;
		akt->HoechstesPaarInZielgraph();
	}
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	Bank--;
	Lab++;
}


