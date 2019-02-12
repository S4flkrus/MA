#include "AlgoGrad4.h"
#include "Knoten.h"
#include "Kante.h"
#include "Graph.h"
#include "Zielgraph.h"
#include "Element.h"
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


AlgoGrad4::AlgoGrad4(Graph * Hauptgraph){
	Ziel = Hauptgraph->Ziel;
	Bank = 0;
	D1C1 = 0;
	D1C2 = 0;
	D1C3 = 0;
	D1C4 = 0;
	D1C5 = 0;
	D1C6 = 0;
	D1C7 = 0;
	D1C8 = 0;	
	D2C1 = 0;
	D2C2 = 0;
	D2C3 = 0;
	D2C4 = 0;
	D2C5 = 0;
	D2C6 = 0;
	D2C7 = 0;
	D2C8 = 0;
	D2C9 = 0;
	D3C1 = 0;
	D3C2 = 0;
	D3C3 = 0;
	D3C4 = 0;
	D4C1 = 0;
	D4C2 = 0;
	AS = 0;
}	
//Ebene 10
void AlgoGrad4::HaendleGraph(Graph * Hauptgraph){	
	Knoten * akt = Hauptgraph->Startknoten;
	Knoten * Hilfsknoten;
	while(Hauptgraph->Startknoten != nullptr){
		/*if(Hauptgraph->Grad2 == nullptr && Hauptgraph->Grad3 == nullptr && Bank == 0){
			break;
		}*/
		if(Hauptgraph->Startknoten->Grad == 0){
			akt->KnotenLoeschen();
			akt = Hauptgraph->Startknoten;
		}
		else if(Hauptgraph->Startknoten->Grad == 1){
			HaendleGrad1(Hauptgraph->Startknoten);
		}
		else if(Hauptgraph->Startknoten->Grad == 2){
			HaendleGrad2(Hauptgraph->Startknoten, Hauptgraph);
		}
		else if(Hauptgraph->Startknoten->Grad == 3){
			HaendleGrad3(Hauptgraph->Startknoten, Hauptgraph);
		}
		else if(Hauptgraph->Startknoten->Grad > 4){
			Ausgleichsschritt(Hauptgraph);
		}
		else {
			HaendleGrad4(Hauptgraph->Startknoten);
		}			
	}
	//cout << "Durchlauf erledigt" << endl;
	//Hauptgraph->GraphDrucken();
	//cout << "Überdeckung: " << endl;
	Ziel->GraphDrucken();
	cout << endl << "Grad 1 Fall 1: " << D1C1 << " Grad 1 Fall 2: " << D1C2 << " Grad 1 Fall 3: " <<  D1C3 << " Grad 1 Fall 4: " << D1C4 << " Grad 1 Fall 5: " << D1C5 << " Grad 1 Fall 6: " << D1C6 << " Grad 1 Fall 7: " << D1C7; 
	cout << " Grad 1 Fall 8: " << D1C8 << endl << "Grad 2 Fall 1: " << D2C1 << " Grad 2 Fall 2: " << D2C2 << " Grad 2 Fall 3: " <<	D2C3 << " Grad 2 Fall 4: " << D2C4 << " Grad 2 Fall 5: " << D2C5 << " Grad 2 Fall 6: " << D2C6 << " Grad 2 Fall 7: " << D2C7; 
	cout << " Grad 2 Fall 8: " << D2C8 << " Grad 2 Fall 9: " << D2C9 << endl << "Grad 3 Fall 1: " << D3C1 << " Grad 3 Fall 2: " << D3C2 << " Grad 3 Fall 3: " << D3C3 << " Grad 3 Fall 3: " << D3C4 << " Grad 4 Fall 1: " << D4C1 << " Grad 4 Fall 2: " << D4C2 << " Ausgleichsschritte: " << AS << endl;
	return;
	
}


void AlgoGrad4::HaendleGrad1(Knoten * Zielknoten){
	if (Zielknoten->GetErstenNachbarn()->Grad == 1){
		if(Zielknoten->abgedeckt == true){
			Zielknoten->GetErstenNachbarn()->KnotenLoeschen();
			Zielknoten->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Exakt++;
			Bank = Bank + 2;
			D1C1++;
			return;
		}
		else if(Zielknoten->GetErstenNachbarn()->abgedeckt == true){
			Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			Zielknoten->KnotenLoeschen();
			Ziel->Approx++;
			Ziel->Exakt++;
			Bank = Bank + 2;
			D1C1++;
			return;
		}
		else{
			Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			Zielknoten->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			D1C3++;
			return;
		}
	}
	if(Zielknoten->GetErstenNachbarn()->abgedeckt == true){
			Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			Zielknoten->KnotenLoeschen();
			Ziel->Approx++;
			Ziel->Exakt++;
			Bank = Bank + 2;
			D1C2++;
			return;
	}
	if(Zielknoten->GetErstenNachbarn()->IstTeilVonDreieck() != nullptr){
		Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
		Zielknoten->KnotenLoeschen();
		Ziel->Approx++;
		Ziel->Exakt++;
		Bank = Bank + 2;
		D1C5++;
		return;
	}
	Knoten * akt = nullptr;
	if(Zielknoten->GetErstenNachbarn()->Grad == 2){
		akt = Zielknoten->GetErstenNachbarn()->GetErstenNachbarn();
		if(akt != Zielknoten){
			Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			D1C6++;
			return;
		}
		else{
			akt = Zielknoten->GetErstenNachbarn()->GetLetztenNachbarn();
			Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			D1C6++;
			return;
		}
	}
	akt = nullptr;
	Kante * tmp = Zielknoten->GetErstenNachbarn()->Startkante;
	bool zwei = false;
	while(tmp != nullptr){
		if(tmp->GetNachbar(Zielknoten->GetErstenNachbarn())->Grad > 1){
			if (akt = nullptr){
				akt = tmp->GetNachbar(Zielknoten->GetErstenNachbarn());
			}
			else{
				zwei = true;
				break;
			}
		}
		tmp = tmp->GetNextKante(Zielknoten->GetErstenNachbarn());
	}
	if(zwei == false && akt != nullptr){
		Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			D1C6++;
			return;
	}
	else if(akt != nullptr){
		Zielknoten->GetErstenNachbarn()->KnotenInZielgraph();
			Zielknoten->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			D1C4++;
			return;
	}
	else{
		bool help = Zielknoten->KnotenInHilfsliste();
		if(help == true){
			D1C7++;
			Bank = Bank + 0.5;
		}
		else{
			D1C8++;
			Bank = Bank + 0.5;
		}
	}
	
}

void AlgoGrad4::HaendleGrad2(Knoten * Zielknoten, Graph * Hauptgraph){
	Knoten * tmp = Zielknoten->IstTeilVonDreieck();
	Knoten * akt = nullptr;
	if(tmp != nullptr){
		akt = Zielknoten->IstTeilVonDreieck(tmp);
		if(Zielknoten->Hilfskn != nullptr){
			Zielknoten->KnotenInZielgraph();
			tmp->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank++;
			D2C2++;
			return;
		}
		else{
			tmp->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			D2C1++;
			return;
		}
	}
	tmp = Zielknoten->GetErstenNachbarn();
	akt = Zielknoten->GetLetztenNachbarn();
	Knoten * vier = nullptr;
	Knoten * zwil = nullptr;
	Kante * Akt = tmp->Startkante;
	while(Akt != nullptr){
		if(Akt->GetNachbar(tmp) != Zielknoten && Akt->GetNachbar(tmp)->IstNachbarVon(akt) == true){
			if(vier == nullptr){
				vier = Akt->GetNachbar(tmp);
			}
			else if(zwil == nullptr){
				zwil = Akt->GetNachbar(tmp);
			}
			else{
				if(Akt->GetNachbar(tmp)->Grad > zwil->Grad){
					zwil = Akt->GetNachbar(tmp);
				}
			}
		}
		Akt = Akt->GetNextKante(tmp);
	} 
	if(vier == nullptr){
		if(Zielknoten->abgedeckt == true){
	//		cout << tmp->ID << "add  " ;
			Element * Ele = new Element(tmp, Zielknoten, akt);
			if(tmp->BankAnker == nullptr){
				tmp->BankAnker = Ele;
			}
			else{
				Ele->NaechstesElement = tmp->BankAnker;
				tmp->BankAnker = Ele;
			}
			tmp->Bip++;
		//	Ele->ElementDrucken(); 
		//	if(Ele->NaechstesElement == nullptr){
		//		cout << "end" << endl;
		//	}
			tmp->Kantenuebertragen(akt);
			akt->AlleKantenLoeschen();		
			akt->KnotenAusGraphEntfernen();
			Zielknoten->AlleKantenLoeschen();
			Zielknoten->KnotenAusGraphEntfernen();
			Bank++;
			D2C3++;
			return;
		}
		else{
			Zielknoten->KnotenInZielgraph();
			tmp->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank++;
			D2C4++;
			return;	
		}
	}
	if(zwil == nullptr && akt->Grad == 2 && tmp->Grad == 2){
		D2C5++;
		if(vier->abgedeckt == true && Zielknoten->abgedeckt == true){
			vier->KnotenInZielgraph();
			Zielknoten->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			return;
		}
		else if(vier->Grad == 2){
			if(tmp->abgedeckt == true && akt->abgedeckt == true){
				tmp->KnotenInZielgraph();
				akt->KnotenInZielgraph();
				Ziel->Approx++;
				Ziel->Approx++;
				Ziel->Exakt++;
				Ziel->Exakt++;
				Bank = Bank + 4;
				return;
			}
			else{
				tmp->KnotenInZielgraph();
				vier->KnotenInZielgraph();
				akt->KnotenInZielgraph();
				Ziel->Approx++;
				Ziel->Approx++;
				Ziel->Approx++;
				Ziel->Exakt++;
				Ziel->Exakt++;
				Ziel->Exakt++;
				Bank = Bank + 6;
				return;	
			}
		}
		else if(vier->Grad == 3 && Zielknoten->abgedeckt == true){
			Kante * Help = vier->Startkante;
			while(Help != nullptr){
				if(Help->GetNachbar(vier) == akt || Help->GetNachbar(vier) == tmp){
					Help->GetNextKante(vier);
				}
				else{
					zwil == Help->GetNachbar(vier);
					break;
				}
			}
			zwil->KnotenInZielgraph();
			vier->KnotenInZielgraph();
			Zielknoten->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 6;
			return;	
		}
		else if(Zielknoten->abgedeckt == true){
			Zielknoten->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Exakt++;
			Bank = Bank + 2;
			return;	
		}
		else if(tmp->abgedeckt == true && akt->abgedeckt == true){
			tmp->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 4;
			return;
		}
		else{
			tmp->KnotenInZielgraph();
			vier->KnotenInZielgraph();
			akt->KnotenInZielgraph();
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Approx++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Ziel->Exakt++;
			Bank = Bank + 6;
			return;	
		}
	}
	if(zwil == nullptr && tmp->abgedeckt == true && akt->abgedeckt == true){
		tmp->KnotenInZielgraph();
		akt->KnotenInZielgraph();
		Ziel->Approx++;
		Ziel->Approx++;
		Ziel->Exakt++;
		Ziel->Exakt++;
		Bank = Bank + 4;
		D2C7++;
		return;
	}
	if(zwil == nullptr && Zielknoten->abgedeckt == true && vier->abgedeckt == true){
		vier->KnotenInZielgraph();
		Zielknoten->KnotenInZielgraph();
		Ziel->Approx++;
		Ziel->Approx++;
		Ziel->Exakt++;
		Ziel->Exakt++;
		Bank = Bank + 4;
		D2C6++;
		return;
	}
	if(zwil != nullptr && zwil->Grad > vier->Grad){
		zwil->KnotenInZielgraph();
	}
	else{
		vier->KnotenInZielgraph();
	}
	tmp->KnotenInZielgraph();
	akt->KnotenInZielgraph();
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	Ziel->Exakt++;
	Bank++;
	D2C9++;
	return;	
}
		
void AlgoGrad4::HaendleGrad3(Knoten * Zielknoten, Graph * Hauptgraph){
	Knoten * akt = Zielknoten->IstTeilVonDreieck();
	Knoten * tmp = nullptr;
	Knoten * Tmp = nullptr;
	if(akt != nullptr){
		tmp = Zielknoten->IstTeilVonDreieck(akt);
		if(akt == Zielknoten->GetErstenNachbarn()){
			if(tmp == Zielknoten->Letztekante->GetNachbar(Zielknoten)){
				Tmp = Zielknoten->Startkante->GetNextKante(Zielknoten)->GetNachbar(Zielknoten);
				if(Tmp->IstNachbarVon(akt) == true){
					akt->KnotenInZielgraph();
					Ziel->Approx++;
					Ziel->Exakt++;
					Bank = Bank + 2;
					D3C1++;
					return;
				}
				else if (Tmp->IstNachbarVon(tmp) == true){
					tmp->KnotenInZielgraph();
					Ziel->Approx++;
					Ziel->Exakt++;
					Bank = Bank + 2;
					D3C1++;
					return;
				}
				else{
					if(Tmp->abgedeckt == true){
						Tmp->KnotenInZielgraph();
						tmp->KnotenInZielgraph();
						akt->KnotenInZielgraph();
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Bank = Bank + 6;
						D3C2++;
					}
					else{
						Zielknoten->KnotenInZielgraph();
						tmp->KnotenInZielgraph();
						akt->KnotenInZielgraph();
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						D3C3++;
						Bank++;
					}
					return;
				}
			}
			else{
				Tmp = Zielknoten->Letztekante->GetNachbar(Zielknoten);
				if(Tmp->IstNachbarVon(akt) == true){
					akt->KnotenInZielgraph();
					Ziel->Approx++;
					Ziel->Exakt++;
					Bank = Bank + 2;
					D3C1++;
					return;
				}
				else if (Tmp->IstNachbarVon(tmp) == true){
					tmp->KnotenInZielgraph();
					Ziel->Approx++;
					Ziel->Exakt++;
					Bank = Bank + 2;
					D3C1++;
					return;
				}
				else{
					if(Tmp->abgedeckt == true){
						Tmp->KnotenInZielgraph();
						tmp->KnotenInZielgraph();
						akt->KnotenInZielgraph();
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Bank = Bank + 6;
						D3C2++;
					}
					else{
						Zielknoten->KnotenInZielgraph();
						tmp->KnotenInZielgraph();
						akt->KnotenInZielgraph();
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Bank++;
						D3C3++;
					}
					return;
				}
			}	
		}
		else{
			Tmp = Zielknoten->GetErstenNachbarn();
			if(Tmp->abgedeckt == true){
						Tmp->KnotenInZielgraph();
						tmp->KnotenInZielgraph();
						akt->KnotenInZielgraph();
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Bank = Bank + 6;
						D3C2++;
					}
					else{
						Zielknoten->KnotenInZielgraph();
						tmp->KnotenInZielgraph();
						akt->KnotenInZielgraph();
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Approx++;
						Ziel->Exakt++;
						Ziel->Exakt++;
						Bank++;
						D3C3++;
					}
					return;
		}	
	}
	else{
		Kante * Help = Zielknoten->Startkante;
		Tmp = Zielknoten->GetErstenNachbarn();
		while(Help != nullptr){
			tmp = nullptr;
			akt = Help->GetNachbar(Zielknoten);
			tmp = akt->IstTeilVonDreieck();
			if(tmp != nullptr){
				if(akt->Grad == 3){
					HaendleGrad3(akt, Hauptgraph);
					return;
				}
				else{
					Tmp = akt->IstTeilVonDreieck(tmp);
					Tmp->KnotenInZielgraph();
					tmp->KnotenInZielgraph();
					akt->KnotenInZielgraph();
					Ziel->Approx++;
					Ziel->Approx++;
					Ziel->Approx++;
					Ziel->Exakt++;
					Ziel->Exakt++;
					Bank++;
					D3C4++;
					return;
				}
			}
			if(akt->Grad > Tmp->Grad){
				Tmp = akt;
			}
			Help = Help->GetNextKante(Zielknoten);
		}
		Tmp->HoechstesPaarInZielgraph();
		D3C4++;
		return;
	}
}

void AlgoGrad4::HaendleGrad4(Knoten * Zielknoten){
	Knoten * akt = Zielknoten->IstTeilVonDreieck();
	Knoten * tmp = nullptr;
	Knoten * Tmp = nullptr;
	if(akt != nullptr){
		tmp = Zielknoten->IstTeilVonDreieck(akt);
		Zielknoten->KnotenInZielgraph();
		tmp->KnotenInZielgraph();
		akt->KnotenInZielgraph();
		Ziel->Approx++;
		Ziel->Approx++;
		Ziel->Approx++;
		Ziel->Exakt++;
		Ziel->Exakt++;
		Bank++;
		D4C1++;
		return;
	}
	else{
		Kante * Help = Zielknoten->Startkante;
		Tmp = Zielknoten->GetErstenNachbarn();
		while(Help != nullptr){
			tmp = nullptr;
			akt = Help->GetNachbar(Zielknoten);
			tmp = akt->IstTeilVonDreieck();
			if(tmp != nullptr){		
				Tmp = akt->IstTeilVonDreieck(tmp);
				Tmp->KnotenInZielgraph();
				tmp->KnotenInZielgraph();
				akt->KnotenInZielgraph();
				Ziel->Approx++;
				Ziel->Approx++;
				Ziel->Approx++;
				Ziel->Exakt++;
				Ziel->Exakt++;
				Bank++;
				D4C2++;
				return;
			}
			if(akt->Grad > Tmp->Grad){
				Tmp = akt;
			}
			Help = Help->GetNextKante(Zielknoten);
		}
		Tmp->HoechstesPaarInZielgraph();
		D4C2++;
		return;
	}
}

void AlgoGrad4::Ausgleichsschritt(Graph * Hauptgraph){
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
	Ziel->Approx++;
	Ziel->Approx++;
	Ziel->Exakt++;
	Bank--;
	AS++;
}
		

