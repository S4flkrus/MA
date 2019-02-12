#include "Zielgraph.h"
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

Zielgraph::Zielgraph(){
	Faktor = 1.0;
	Exakt = 0;
	Approx = 0;
	Startknoten = nullptr;
	Letzterknoten = nullptr;
}
//Ebene 2
void Zielgraph::GraphDrucken(){
	if(Startknoten != nullptr){
		//Startknoten->KnotenDrucken();
		cout << "vertices_in_the_cover: " << Approx;
		FaktorBerechnen();
		cout << " faktor: " << Faktor;
	}
	else{
		cout << "cover empty " << endl;
	}
}
//Ebene 1
void Zielgraph::ZielGraphEntfernen(){
	Startknoten->KnotenDeleten();
	delete(this);
}
//Ebene 0
void Zielgraph::FaktorBerechnen(){
	double a = (double )Approx;
	double e = (double) Exakt;
	Faktor = a/e;
}


