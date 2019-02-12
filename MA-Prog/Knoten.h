#ifndef KNOTEN_H
#define KNOTEN_H
#include <utility> 


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

class Kante;
class Graph;
class Hilfsgraph;
class Hilfsknoten;
class Element;


class Knoten
{

	public:
		Knoten(int id, Graph * Haupt);
		Knoten(int id, Knoten * vor, Graph * Haupt);
		
		int ID;
		int Grad;
		int Entf;
		int Bip;
		bool entfernt;

		Knoten * next;
		Knoten * prev;
		Kante * Startkante;
		Kante * Letztekante;
		Element * BankAnker;
		Graph * Hauptgr;
		Hilfsknoten * Hilfskn;
		Hilfsgraph * Hilfsgra;
		bool abgedeckt;
		
		Knoten* GetErstenNachbarn();
		Knoten* GetLetztenNachbarn();
		Knoten* IstTeilVonDreieck();
		Knoten* IstTeilVonDreieck(Knoten * Nachbar);
		Knoten* HatNachbarMitGrad(int GesuchterGrad);
		Knoten* GetNachbarnAusserhalbVon(Hilfsgraph * H);
		bool IstNachbarVon(Knoten * Nachbar);
		void KnotenDrucken();
		void KanteHinzufuegen(Kante * Ziel);
		void KanteLoeschen(Kante * Ziel);
		void AlleKantenLoeschen();
		void AlleKantenLoeschenAbdecken();
		void KnotenLoeschen();
		void KnotenInZielgraph();
		void KnotenAusGraphEntfernen();
		bool KnotenInHilfsliste();
		void Kantenuebertragen(Knoten * Loeschknoten);
		void HoechstesPaarInZielgraph();
		int GetAnzahlNachbarnAusserhalbVon(Hilfsgraph * H);
		void KnotenDeleten();
		
		
	protected:
		void GradReduzieren();
		void GradErhoehen();
};

#endif
