#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <utility> 
#include <fstream> 
#include "Knoten.h"
#include "Kante.h"
#include "Graph.h"
#include "AlgoGrad4.h"
#include "AlgoGrad4_1.h"
//#include "AlgoGrad4_2.h"
#include "Element.h"
#include <sys/time.h>
#include <chrono>

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
/*
array<vector<int>, 4000> v{

};
*/
vector<vector<int>> v{};
	
vector<Knoten *> Help{};

vector<Knoten *> Help_1{};

vector<Knoten *> Help_2{};

vector<int> dvec;
	
int RNr();
	
int main(int argc, char** argv) {
	
  	dvec.push_back(0); 
  /*	ifstream input("120cell_graph.txt"); 

    if(!input) { 
        cerr << "Data not found." << endl; 
        return EXIT_FAILURE; 
    } 
    int wert; 
  
    while(input >> wert){ 

        dvec.push_back(wert); 

 	}
  	
  	v.resize(dvec[0]);
  	
  	for(int i = 2; i < dvec.size(); i = i+2){
  		v[dvec[i]].push_back(dvec[i+1]);
  	}
  	int Kantenziel = dvec[1];
  	double DG = 2*(dvec[1]/dvec[0]);
 */ 	
  	
/*
	ifstream input("60cell_graph.txt"); 

    if(!input) { 
        cerr << "Data not found." << endl; 
        return EXIT_FAILURE; 
    } 
    int wert; 
  
    while(input >> wert){ 

        dvec.push_back(wert); 

 	}
  	
  	v.resize(dvec[0]);
  	
  	for(int i = 2; i < dvec.size(); i = i+2){
  		v[dvec[i]].push_back(dvec[i+1]);
  	}
  	
  	
  	int Kantenziel = dvec[1];

	double DG = 2*(dvec[1]/dvec[0]);
 */ 	
 	for(int f = 16; f <= 21; f++){
	for(int za = 2; za <= 2; za++){
		//cout << "Graph_Nr: " << za << ": ";
		dvec[0] = pow(2, f);
	//const int Knot = 250000;
	//vector<vector<int>> v{
	//};
	//for(int k = 0; k < Knot; k++){
		
	//}
    v.resize(dvec[0]);
	int a;
    time_t t;

    time(&t);
    srand((unsigned int)t*za); 
	
	//int KantZu = rand() % 10;
	//int KantZu = za % 10;
	
	int Kantenanzahl = 0;
	//int Kantenziel = 37500 + (KantZu * 12500);
	double Ziel = (1 + za/2.0) * dvec[0];
	int Kantenziel = (int)Ziel;
	//int Kantenziel = 53;
	
	double KnotenZahl = (double )dvec[0];
	double KantenZahl = (double)Kantenziel;
	double DG = KantenZahl / KnotenZahl * 2.0;
	
	for(int l = 0; l < v.size(); l++){
		int r = RNr() % dvec[0];	
		if(r < l){
			if(find(v[r].begin(), v[r].end(), l) == v[r].end()){
			Kantenanzahl++;
			v[r].push_back(l);
			}
		}
		else if(r > l){
			if(find(v[l].begin(), v[l].end(), r) == v[l].end()){
			Kantenanzahl++;	
			v[l].push_back(r);
			}
		}
		
	}
		
	while(Kantenanzahl < Kantenziel){
		int r = RNr() % dvec[0];
		int l = RNr() % dvec[0];
			if(r < l){	
				if(find(v[r].begin(), v[r].end(), l) == v[r].end()){
					Kantenanzahl++;
					v[r].push_back(l);
				}
			}
			else if(r > l){
				if(find(v[l].begin(), v[l].end(), r) == v[l].end()){
					Kantenanzahl++;
					v[l].push_back(r);
				}
			}
	}
	

	
/*
	//Testgraph
	v.resize(53);
	v[0].resize(5);
	v[0] = {1,2,4,6,19};
	v[1].resize(4);
	v[1] = {3,5,7,24};
	v[2].resize(5);
	v[2] = {3,4,6,12,19};
	v[3].resize(3);
	v[3] = {5,7,21};
	v[4].resize(5);
	v[4] = {5,6,11,14,22};
	v[5].resize(3);
	v[5] = {7,14,22};
	v[6].resize(1);
	v[6] = {7};
	v[7].resize(1);
	v[7] = {25};
	v[8].resize(1);
	v[8] = {9};
	v[9].resize(1);
	v[9] = {10};
	v[10].resize(2);
	v[10] = {11,12};
	v[11].resize(2);
	v[11] = {12,13};
	v[13].resize(1);
	v[13] = {14};
	v[15].resize(2);
	v[15] = {16,17};
	v[16].resize(2);
	v[16] = {17,18};
	v[17].resize(1);
	v[17] = {18};
	v[18].resize(1);
	v[18] = {19};
	v[20].resize(4);
	v[20] = {21,23,24,25};
	v[21].resize(2);
	v[21] = {22,23};
	v[22].resize(1);
	v[22] = {23};
	v[24].resize(1);
	v[24] = {25};
	v[26].resize(5);
	v[26] = {27,29,31,33,34};
	v[27].resize(3);
	v[27] = {30,31,33};
	v[28].resize(4);
	v[28] = {29,30,31,32};
	v[29].resize(2);
	v[29] = {30,32};
	v[30].resize(2);
	v[30] = {32,34};
	v[31].resize(2);
	v[31] = {33,35};
	v[32].resize(2);
	v[32] = {33,35};
	v[34].resize(1);
	v[34] = {35};
	v[36].resize(3);
	v[36] = {37,38,44};
	v[37].resize(4);
	v[37] = {38,39,41,43};
	v[38].resize(2);
	v[38] = {40,43};
	v[39].resize(3);
	v[39] = {40,42,44};
	v[40].resize(2);
	v[40] = {42,44};
	v[41].resize(2);
	v[41] = {42,43};
	v[42].resize(1);
	v[42] = {44};
	v[43].resize(1);
	v[43] = {44};
	v[45].resize(3);
	v[45] = {46,48,51};
	v[46].resize(2);
	v[46] = {47,49};
	v[47].resize(2);
	v[47] = {48,50};
	v[48].resize(1);
	v[48] = {52};
	v[49].resize(2);
	v[49] = {50,51};
	v[50].resize(1);
	v[50] = {52};
	v[51].resize(1);
	v[51] = {52};
*/

	//Erzeugen des Graphen	 
	Zielgraph * ziel = new Zielgraph();
	Graph * Hauptgr = new Graph(ziel);
	
	Knoten * knoten = new Knoten(0, Hauptgr);
	
	Help.resize(dvec[0]);
	Help[0] = knoten;
	
	Hauptgr->Startknoten = knoten;
	Hauptgr->Endknoten = knoten;
	Hauptgr->KnotenZahl++;
	Knoten * tmp = knoten;
	Knoten * Start = knoten; 
	Knoten * akt;
	
	Zielgraph * ziel_1 = new Zielgraph();
	Graph * Hauptgr_1 = new Graph(ziel_1);
	
	Knoten * knoten_1 = new Knoten(0, Hauptgr_1);
	
	Help_1.resize(dvec[0]);
	Help_1[0] = knoten_1;
	
	Hauptgr_1->Startknoten = knoten_1;
	Hauptgr_1->Endknoten = knoten_1;
	Hauptgr_1->KnotenZahl++;
	Knoten * tmp_1 = knoten_1;
	Knoten * Start_1 = knoten_1; 
	Knoten * akt_1;
	
	Zielgraph * ziel_2 = new Zielgraph();
	Graph * Hauptgr_2 = new Graph(ziel_2);
	
	Knoten * knoten_2 = new Knoten(0, Hauptgr_2);
	
	Help_2.resize(dvec[0]);
	Help_2[0] = knoten_2;
	
	Hauptgr_2->Startknoten = knoten_2;
	Hauptgr_2->Endknoten = knoten_2;
	Hauptgr_2->KnotenZahl++;
	Knoten * tmp_2 = knoten_2;
	Knoten * Start_2 = knoten_2; 
	Knoten * akt_2;
	
	for(int i = 1; i < v.size(); i++){
		knoten = new Knoten(i, tmp, Hauptgr);
		Hauptgr->Endknoten = knoten;
		tmp->next = knoten;
		tmp = knoten;
		Hauptgr->KnotenZahl++;
		Help[i] = knoten;
		
		knoten_1 = new Knoten(i, tmp_1, Hauptgr_1);
		Hauptgr_1->Endknoten = knoten_1;
		tmp_1->next = knoten_1;
		tmp_1 = knoten_1;
		Hauptgr_1->KnotenZahl++;
		Help_1[i] = knoten_1;
		
		knoten_2 = new Knoten(i, tmp_2, Hauptgr_2);
		Hauptgr_2->Endknoten = knoten_2;
		tmp_2->next = knoten_2;
		tmp_2 = knoten_2;
		Hauptgr_2->KnotenZahl++;
		Help_2[i] = knoten_2;
	}
	tmp = Start;
	akt = Start->next;
	
	tmp_1 = Start_1;
	akt_1 = Start_1->next;
	
	tmp_2 = Start_2;
	akt_2 = Start_2->next;
	int Kant = 0;
	
	for(int i = 0; i < v.size(); i++){
		akt = Help[i];
		tmp = nullptr;
		
		akt_1 = Help_1[i];
		tmp_1 = nullptr;
		
		akt_2 = Help_2[i];
		tmp_2 = nullptr;
		
			
		for(int j =0; j < v[i].size(); j++){
			tmp = Help[v[i][j]];
			
			tmp_1 = Help_1[v[i][j]];
			
			tmp_2 = Help_2[v[i][j]];
				
			if(tmp!=nullptr && tmp_1!=nullptr){
				Kant++;
				Kante * kante = new Kante(tmp, akt);
				tmp->KanteHinzufuegen(kante);
				akt->KanteHinzufuegen(kante);
				
				Kante * kante_1 = new Kante(tmp_1, akt_1);
				tmp_1->KanteHinzufuegen(kante_1);
				akt_1->KanteHinzufuegen(kante_1);
				
				Kante * kante_2 = new Kante(tmp_2, akt_2);
				tmp_2->KanteHinzufuegen(kante_2);
				akt_2->KanteHinzufuegen(kante_2);
			}
		}
	}

	
	cout << "vertices: " << dvec[0] << " ";
	cout << "edges: " << Kantenziel << " ";
	cout << "average degree: " << DG << " " << endl;
	
//	cout << "Erzeugt" << endl;
	/*
	for(int i = 0; i < v.size(); i++){
		akt = Hauptgr->Startknoten;
			while(akt->ID != i){
				akt = akt->next;
			}
		for(int j =0; j < v[i].size(); j++){
			tmp = Hauptgr->Startknoten;
			while(tmp!=nullptr && tmp->ID != v[i][j]){
				tmp = tmp->next;
			}
			if(tmp!=nullptr){
				Kante * kante = new Kante(tmp, akt);
				tmp->KanteHinzufuegen(kante);
				akt->KanteHinzufuegen(kante);
			}
		}
	}
	
	*/
	
	//cout << " Graph erstellt ";
	//cout << endl;
	//Hauptgr->Startknoten->KnotenDrucken();
	
	//Bearbeiten des Graphen
	long int AlgTime;
	
	//gettimeofday(&AlgStart, 0);
	auto begin = chrono::high_resolution_clock::now();   
	AlgoGrad4 * Algo = new AlgoGrad4(Hauptgr);
	Algo->HaendleGraph(Hauptgr);
	//gettimeofday(&AlgEnd, 0);
	auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	//AlgEnd.tv_sec-AlgStart.tv_sec;
	cout << " Runtime1: " << ms << "ms";
	
/*	gettimeofday(&AlgStart, 0);
	AlgoGrad4_1 * Algo_1 = new AlgoGrad4_1(Hauptgr_1);
	Algo_1->HaendleGraph(Hauptgr_1);
	gettimeofday(&AlgEnd, 0);
	AlgTime = AlgEnd.tv_sec-AlgStart.tv_sec;
	cout << " Runtime2: " << AlgTime << "s";
	
	gettimeofday(&AlgStart, 0);
	AlgoGrad4_2 * Algo_2 = new AlgoGrad4_2(Hauptgr_2);
	Algo_2->HaendleGraph(Hauptgr_2);
	gettimeofday(&AlgEnd, 0);
	AlgTime = AlgEnd.tv_sec-AlgStart.tv_sec;
	cout << " Runtime: " << AlgTime << "s";
*/	
	
	/*
	//TestBeginn
	
	Zielgraph * zielTest = new Zielgraph();
	Graph * Testgr = new Graph(zielTest);
	
	Knoten * Testknoten = new Knoten(0, Testgr);
	
	Testgr->Startknoten = Testknoten;
	Testgr->Endknoten = Testknoten;
	Testgr->KnotenZahl++;
	tmp = Testknoten;
	Start = Testknoten; 
	akt;
	for(int i = 1; i < v.size(); i++){
		Testknoten = new Knoten(i, tmp, Testgr);
		Testgr->Endknoten = Testknoten;
		tmp->next = Testknoten;
		tmp = Testknoten;
		Testgr->KnotenZahl++;
	}
	tmp = Start;
	akt = Start->next;
	
	for(int i = 0; i < v.size(); i++){
		akt = Testgr->Startknoten;
			while(akt->ID != i){
				akt = akt->next;
			}
		for(int j =0; j < v[i].size(); j++){
			tmp = Testgr->Startknoten;
			while(tmp->ID != v[i][j]){
				tmp = tmp->next;
			}
			Kante * Testkante = new Kante(tmp, akt);
			tmp->KanteHinzufuegen(Testkante);
			akt->KanteHinzufuegen(Testkante);
		}
	}
	akt = Hauptgr->Startknoten;
	tmp = Testgr->Startknoten;
	Knoten * help = nullptr;
	while(akt != nullptr){
		while(tmp != nullptr){
			if(tmp->ID == akt->ID){
				help = tmp->next;
				tmp->KnotenLoeschen();
				tmp = help;
			}
			else{
				tmp = tmp->next;
			}	
		}
		tmp = Testgr->Startknoten;
		akt = akt->next;
	}
	//cout << " Test1 ";
	akt = Hauptgr->Ziel->Startknoten;
	tmp = Testgr->Startknoten;
	help = nullptr;
	while(akt != nullptr){
		while(tmp != nullptr){
			if(tmp->ID == akt->ID){
				help = tmp->next;
				tmp->KnotenLoeschen();
				tmp = help;
			}
			else{
				tmp = tmp->next;
			}	
		}
		tmp = Testgr->Startknoten;
		akt = akt->next;
	}
	//cout << "Test2 ";	
	Element * Akt = Hauptgr->Bank->StartElement;
	tmp = Testgr->Startknoten;
	help = nullptr;
	while(Akt != nullptr){
		while(tmp != nullptr){
			if(tmp->ID == Akt->Speicher1->ID){
				help = tmp->next;
				tmp->KnotenLoeschen();
				tmp = help;
			}
			else if(tmp->ID == Akt->Speicher2->ID){
				help = tmp->next;
				tmp->KnotenLoeschen();
				tmp = help;
			}
			else{
				tmp = tmp->next;
			}	
		}
		tmp = Testgr->Startknoten;
		Akt = Akt->NaechstesElement;
	}
	//cout << "Test3 ";
	tmp = Testgr->Startknoten;
	while(Testgr->Startknoten != Testgr->Endknoten && tmp != nullptr){
		if(tmp->Grad == 0){
			tmp->KnotenLoeschen();
			tmp = Testgr->Startknoten;
		}
		else{
			tmp = tmp->next;
		}
	}
	//cout << "Test4 ";
	if(Testgr->Startknoten == Testgr->Endknoten && Testgr->Startknoten != nullptr){
		Testgr->Startknoten->KnotenLoeschen();
	}
	if(Testgr->Startknoten == nullptr){
		cout << " Valid";
	}
	else{
		cout << " Invalid";
		//Testgr->GraphDrucken();
	}
	*/
	//EndTest
	cout << endl;
	//Dekonstruktor 
	
	v.resize(0); 
	Help.resize(0);
	Help_1.resize(0);
	Help_2.resize(0);
	}
	}
	return 0;
	
}


int RNr(){
	int a = rand();
	if(rand() % 2 == 1){
		a = a + pow(2, 15);
	}
	if(rand() % 2 == 1){
		a = a + pow(2, 16);
	}
	if(rand() % 2 == 1){
		a = a + pow(2, 17);
	}
	if(rand() % 2 == 1){
		a = a + pow(2, 18);
	}
	if(rand() % 2 == 1){
		a = a + pow(2, 19);
	}
	if(rand() % 2 == 1){
		a = a + pow(2, 20);
	}
	if(rand() % 2 == 1){
		a = a + pow(2, 21);
	}
	return a;
}
