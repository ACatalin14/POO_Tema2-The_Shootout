#include "Shuriken.h"
#include <iostream>
#include <minmax.h>

using namespace std;

Shuriken::Shuriken() {
	setNume(kNumeShuriken);
	setDamage(kDamageShuriken);
}

const char* Shuriken::Directie(int dir) const {
	switch (dir) {
		case 0:
			return "Nord";
		case 1:
			return "Est";
		case 2:
			return "Sud";
		case 3:
			return "Vest";
		default:
			return "Directie Inexistenta";
	}
}

void Shuriken::AtacaAgent(Agent &inamic) const {
	cout << "  " << *getPosesor() << " il taie cu un shuriken pe ";
	int hpInamic = inamic.getHp();
	int atacRezultat = damage - inamic.getArmor()->getAbsorb();
	inamic.setHp(hpInamic - atacRezultat);
	if (inamic.getHp() < 0) {
		inamic.setHp(0);
		atacRezultat = hpInamic;
	}
	cout << inamic << " [-" << atacRezultat << "hp]\n";
}

void Shuriken::IncrementeazaTinte(int* nrTinte) const {
	(*nrTinte)++;
}

void Shuriken::ExecutaFunctie(int f, Agent &inamic, int* nrTinte) const {
	switch (f) {
		case 0:
			AtacaAgent(inamic);
			break;
		case 1:
			IncrementeazaTinte(nrTinte);
			break;
	}
}

void Shuriken::ExistaInamicPePozitie(Pozitie loc, bool &exista, Agent* &inamic) const {
	inamic = 0;
	exista = false;
	for (int i = 0; i < nrAgenti; i++) {	// luam fiecare agent de pe harta
		if (serieAgenti[i]->getPos().x == loc.x &&	// si verificam daca se afla in casuta & sa nu fie agentul nostru
			serieAgenti[i]->getPos().y == loc.y &&
			serieAgenti[i] != getPosesor() &&
			serieAgenti[i]->IsAlive()) {
			exista = true;
			inamic = serieAgenti[i];
			break;
		}
	}
}

void Shuriken::ParcurgeDirectie(int f, Pozitie start, int dir, int raza, int* nrTinte) const {
	bool existaAgent; 		// true cand un agent se afla pe o casuta data
	Agent* inamicAtacat;	// inamicul atacat daca este gasit pt f = 0
	Pozitie locatie = start;
	switch(dir) {
		case 0:
			for (int y = start.y; y >= start.y - raza; y--) {	// luam fiecare pozitie
				if (y >= 0) {						// verificam daca nu am iesit din harta
					locatie.y = y;
					ExistaInamicPePozitie(locatie, existaAgent, inamicAtacat);
					if (existaAgent) {	// am gasit un agent, il atacam cu shuriken/numaram
						ExecutaFunctie(f, *inamicAtacat, nrTinte);
					}
				}
			}
			break;
		case 1:
			for (int x = start.x; x <= start.x + raza; x++) {	// luam fiecare pozitie
				if (x < nrColoaneHarta) {			// verificam daca nu am iesit din harta
					locatie.x = x;
					ExistaInamicPePozitie(locatie, existaAgent, inamicAtacat);
					if (existaAgent) {	// am gasit un agent, il atacam cu shuriken
						ExecutaFunctie(f, *inamicAtacat, nrTinte);
					}
				}
			}
			break;
		case 2:
			for (int y = start.y; y <= start.y + raza; y++) {	// luam fiecare pozitie
				if (y < nrLiniiHarta) {				// verificam daca nu am iesit din harta
					locatie.y = y;
					ExistaInamicPePozitie(locatie, existaAgent, inamicAtacat);
					if (existaAgent) {	// am gasit un agent, il atacam cu shuriken
						ExecutaFunctie(f, *inamicAtacat, nrTinte);
					}
				}
			}
			break;
		case 3:
			for (int x = start.x; x >= start.x - raza; x--) {	// luam fiecare pozitie
				if (x >= 0) {						// verificam daca nu am iesit din harta
					locatie.x = x;
					ExistaInamicPePozitie(locatie, existaAgent, inamicAtacat);
					if (existaAgent) {	// am gasit un agent, il atacam cu shuriken
						ExecutaFunctie(f, *inamicAtacat, nrTinte);
					}
				}
			}
			break;
		default:
			cout << "Nu s-au luat toate directiile pt atac/numarat!\n";
	}
}

void Shuriken::SchimbaColt(int dir, int raza, Pozitie &colt) const {
	switch (dir) {
		case 0:	// NORD
			colt.y -= raza;
			break;
		case 1:	// EST
			colt.x += raza;
			break;
		case 2:	// SUD
			colt.y += raza;
			break;
		case 3:	// VEST
			colt.x -= raza;
			break;
	}
}

void Shuriken::ParcurgeTraiectorie(int f, Pozitie start, int dir, int raza, int* nrTinte) const {
	Pozitie coltPatrat = start;

	ParcurgeDirectie(f, coltPatrat, dir, raza - 1, nrTinte);
	SchimbaColt(dir, raza, coltPatrat);

	ParcurgeDirectie(f, coltPatrat, (dir + 1) % 4, raza - 1, nrTinte);
	SchimbaColt((dir + 1) % 4, raza, coltPatrat);

	ParcurgeDirectie(f, coltPatrat, (dir + 2) % 4, raza - 1, nrTinte);
	SchimbaColt((dir + 2) % 4, raza, coltPatrat);

	ParcurgeDirectie(f, coltPatrat, (dir + 3) % 4, raza - 1, nrTinte);
}

void Shuriken::Ataca(Agent &inamic) const {
	cout << *getPosesor() << " arunca un shuriken spre " << Directie(directieAruncare) << " ";
	cout << "pe o raza de " << razaAruncare << " metri:\n";
	ParcurgeTraiectorie(0, getPosesor()->getPos(), directieAruncare, razaAruncare);
}

int Shuriken::NumaraTinte(Pozitie start, int dir, int raza) const {
	int tinte = 0;
	ParcurgeTraiectorie(1, start, dir, raza, &tinte);
	return tinte;
}

bool Shuriken::ModificaMaxTinte(int directie, int raza, bool &primaVarianta, int &maxTinte) {
	if (primaVarianta) {
		maxTinte = NumaraTinte(getPosesor()->getPos(), directie, raza);
		directieAruncare = directie;
		razaAruncare = raza;
		primaVarianta = false;
		return true;
	} else {
		int tinte = NumaraTinte(getPosesor()->getPos(), directie, raza);
		if (tinte > maxTinte) {
			maxTinte = tinte;
			directieAruncare = directie;
			razaAruncare = raza;
			return true;
		}
	}
	return false;
}

int Shuriken::AlegeActiune(int nrInamici, Agent** &inamici, int nrLinii, int nrColoane) {
	int nrInamiciShuriken = 0;	// numaram inamicii vizibili agentului care se afla in raza de actiune a shuriken-ului
	int deltaX, deltaY;

	nrLiniiHarta = nrLinii;
	nrColoaneHarta = nrColoane;
	serieAgenti = inamici;
	nrAgenti = nrInamici;

	for (int i = 0; i < getPosesor()->getNrInamiciVizibili(); i++) {
		deltaX = abs( getPosesor()->getPos().x - getPosesor()->getInamiciVizibili()[i]->getPos().x );
		deltaY = abs( getPosesor()->getPos().y - getPosesor()->getInamiciVizibili()[i]->getPos().y );
		if (deltaX <= razaAtac && deltaY <= razaAtac)  {	// am gasit un agent in raza de atac
			nrInamiciShuriken++;
		}
	}

	if (!nrInamiciShuriken)	return -1;	// daca nu exista inamici in raza de atac, se deplaseaza

	int maxTinte = 0;
	int indexInamicPrincipal = 0;	// indexul inamicului de atacat in raport cu vectorul dat prin parametrii
	bool primaVarianta = true;	// true cand nu am facut inca prima varianta de atac

	for (int i = 0; i < getPosesor()->getNrInamiciVizibili(); i++) {	// luam fiecare agent vizibil
		int x = getPosesor()->getPos().x;
		int y = getPosesor()->getPos().y;
		int xInamic = getPosesor()->getInamiciVizibili()[i]->getPos().x;
		int yInamic = getPosesor()->getInamiciVizibili()[i]->getPos().y;

		deltaX = abs( x - xInamic );
		deltaY = abs( y - yInamic );
		if (deltaX <= razaAtac && deltaY <= razaAtac)  {	// am gasit un agent in raza de atac
			int diferentaX = xInamic - x;
			int diferentaY = yInamic - y;
			int directie, raza;				// raza si directie de aruncare pt o varianta de atac

			if (x != xInamic && y != yInamic) {		// daca se afla pe coordonate total diferite, avem o unica traiectorie
				raza = max(deltaX, deltaY);

				if (diferentaX > 0) {	// inamicul este in dreapta
					if (diferentaY < 0) {	// inamicul este in dreapta-sus
						directie = 0;
					} else {	// inamicul este in dreapta-jos
						directie = 1;
					}
				} else {	// inamicul este in stanga
					if (diferentaY < 0) {	// inamicul este in stanga-sus
						directie = 3;
					} else {	// inamicul este in stanga-jos
						directie = 2;
					}
				}

				if (ModificaMaxTinte(directie, raza, primaVarianta, maxTinte) ) {
					indexInamicPrincipal = i;
				}
			} else if (x == xInamic) {	// se afla pe aceeasi coloana, exista 2 directii valide
				int* directiiValide;
				try {
					directiiValide = new int[2];
				}
				catch (bad_alloc) {
					cout << "Alocare Dinamica directiiValide X in Shuriken::AlegeActiune() FAILED\n";
				}
				if (diferentaY < 0) {	// inamicul este sus
					directiiValide[0] = 0;
					directiiValide[1] = 3;
				} else {	// inamicul este jos
					directiiValide[0] = 2;
					directiiValide[1] = 1;
				}

				// acum probam toate traiectoriile posibile care trec prin inamicul ales pt prima si a doua directie
				for (int j = 0; j < 2; j++) {
					for (raza = razaAtac; raza >= deltaY; raza--) {
						if (ModificaMaxTinte(directiiValide[j], raza, primaVarianta, maxTinte) ) {
							indexInamicPrincipal = i;
						}
					}
				}

				delete[] directiiValide;
			} else {	// adica y == yInamic, cei 2 agenti se afla pe aceeasi linie
				int* directiiValide;
				try {
					directiiValide = new int[2];
				}
				catch (bad_alloc) {
					cout << "Alocare Dinamica directiiValide Y in Shuriken::AlegeActiune() FAILED\n";
				}
				if (diferentaX > 0) {	// inamicul este in dreapta
					directiiValide[0] = 1;
					directiiValide[1] = 0;
				} else {	// inamicul este in stanga
					directiiValide[0] = 3;
					directiiValide[1] = 2;
				}

				// acum probam toate traiectoriile posibile care trec prin inamicul ales pt prima si a doua directie
				for (int j = 0; j < 2; j++) {
					for (raza = razaAtac; raza >= deltaX; raza--) {
						if ( ModificaMaxTinte(directiiValide[j], raza, primaVarianta, maxTinte) ) {
							indexInamicPrincipal = i;
						}
					}
				}

				delete[] directiiValide;
			}
		}
	}

	// acum avem indexul inamicului principal dar in raport cu vectorul de inamici vizibili, deci il schimbam
	for (int i = 0; i < nrInamici; i++) {	// luam fiecare inamic din cei dati si verificam daca este inamicul vizibil
		if (inamici[i] == getPosesor()->getInamiciVizibili()[indexInamicPrincipal]) {	// pe care l-am gasit inainte
			indexInamicPrincipal = i;
			break;
		}
	}

	return indexInamicPrincipal;
}

void Shuriken::Deplaseaza(Pozitie &destinatie) const {
	Pozitie inamic;		// pozitia celui mai apropiat inamic
	inamic = getPosesor()->CelMaiApropiatInamic()->getPos();

	int x = getPosesor()->getPos().x;
	int y = getPosesor()->getPos().y;
	int diferentaX = inamic.x - x;
	int diferentaY = inamic.y - y;
	int deltaX = abs(diferentaX);
	int deltaY = abs(diferentaY);

	// acum trebuie sa ma deplasez spre linia/coloana inamicului cel mai apropiat;
	// pe directia cu delta CEL MAI MIC
	int deplasare = (int)( kIndiceDeplasare * getPosesor()->getRazaVizibilitate() ); // cu cat se deplaseaza agentul

	// trebuie sa ne deplasam dupa directia pe care diferenta dintre agenti este mai mica si nenula

	if (deltaX == 0) {	// agentii se afla pe aceeasi coloana, ne deplasam pe verticala
		destinatie.x = x;
		if (diferentaY < 0) {		// inamicul este sus
			destinatie.y = max(y - deplasare, inamic.y + 1);
		} else {					// inamicul este jos
			destinatie.y = min(y + deplasare, inamic.y - 1);
		}
	} else if (deltaY == 0) {	// agentii se afla pe aceeasi linie
		destinatie.y = y;
		if (diferentaX > 0) {		// inamicul este in dreapta
			destinatie.x = min(x + deplasare, inamic.x - 1);
		} else {					// inamicul este in stanga
			destinatie.x = max(x - deplasare, inamic.x + 1);
		}
	} else if (deltaX <= deltaY) {	// ne deplasam pe orizontala
		destinatie.y = y;
		if (diferentaX > 0) {		// inamicul este in dreapta
			destinatie.x = min(x + deplasare, inamic.x);
		} else {					// inamicul este in stanga
			destinatie.x = max(x - deplasare, inamic.x);
		}
	} else {					// ne deplasam pe verticala
		destinatie.x = x;
		if (diferentaY < 0) {		// inamicul este sus
			destinatie.y = max(y - deplasare, inamic.y);
		} else {					// inamicul este jos
			destinatie.y = min(y + deplasare, inamic.y);
		}
	}

	getPosesor()->Deplaseaza(destinatie);
}
