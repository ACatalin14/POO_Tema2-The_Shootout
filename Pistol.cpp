#include "Pistol.h"
#include <iostream>
#include <cmath>

using namespace std;

Pistol::Pistol() {
	setNume(kNumePistol);
	setDamage(kDamagePistol);
}

void Pistol::Ataca(Agent &inamic) const {
	cout << *getPosesor() << " il impusca cu pistolul pe ";
	int hpInamic = inamic.getHp();
	int atacRezultat = damage - inamic.getArmor()->getAbsorb();
	inamic.setHp(hpInamic - atacRezultat);
	if (inamic.getHp() < 0) {
		inamic.setHp(0);
		atacRezultat = hpInamic;
	}
	cout << inamic << " [-" << atacRezultat << "hp]\n";
}

int Pistol::AlegeActiune(int nrInamici, Agent**&inamici, int nrLinii, int nrColoane) {
	int nrInamiciPistol = 0;	// numaram inamicii vizibili agentului care se afla in raza de actiune a pistolului
	int deltaX, deltaY;

	for (int i = 0; i < getPosesor()->getNrInamiciVizibili(); i++) {
		deltaX = abs( getPosesor()->getPos().x - getPosesor()->getInamiciVizibili()[i]->getPos().x );
		deltaY = abs( getPosesor()->getPos().y - getPosesor()->getInamiciVizibili()[i]->getPos().y );
		if (deltaX <= razaAtac && deltaY <= razaAtac)  {	// am gasit un agent in raza de atac
			nrInamiciPistol++;
		}
	}

	if (!nrInamiciPistol)	return -1;	// daca nu exista inamici in raza de atac, se deplaseaza

	int indexInamic = 0;				// indexul (in vectorul de inamici dat ca parametru) inamicului cel mai apropiat
	int minDist = 999999999;			// distanta MANHATTAN (pe componente) cea mai mica fata de un agent
	int distanta;

	for (int i = 0; i < getPosesor()->getNrInamiciVizibili(); i++) {
		deltaX = abs( getPosesor()->getPos().x - getPosesor()->getInamiciVizibili()[i]->getPos().x );
		deltaY = abs( getPosesor()->getPos().y - getPosesor()->getInamiciVizibili()[i]->getPos().y );
		distanta = deltaX + deltaY;
		if (deltaX <= razaAtac && deltaY <= razaAtac)  {	// am gasit un agent in raza de atac
			if (distanta < minDist) {
				minDist = distanta;
				indexInamic = i;		// indexul gasit aici este in raport cu vectorul de inamici vizibili
			}
		}
	}

	for (int i = 0; i < nrInamici; i++) {	// luam fiecare inamic din cei dati si verificam daca este inamicul vizibil
		if (inamici[i] == getPosesor()->getInamiciVizibili()[indexInamic]) {	// pe care l-am gasit inainte
			indexInamic = i;
			break;
		}
	}

	return indexInamic;
}

void Pistol::CeaMaiApropiataPozitieDeAtac(Pozitie &inamic, int dir, int maxDeplasare, Pozitie &destinatie) const {
	bool inamicInRazaAtac = false;		// true cand am gasit inamicul in raza de atac
	destinatie = getPosesor()->getPos();
	switch (dir) {
		case 0:	// spre NORD
			for (int deplasare = 1; deplasare <= maxDeplasare; deplasare++) {	// luam fiecare pozitie in parte
				if (destinatie.y - deplasare - razaAtac == inamic.y) {	// si verificam daca e indeajuns pt a ataca
					destinatie.y -= deplasare;
					inamicInRazaAtac = true;
					break;
				}
			}
			if (!inamicInRazaAtac) {
				destinatie.y -= maxDeplasare;
			}
			break;
		case 1:	// spre EST
			for (int deplasare = 1; deplasare <= maxDeplasare; deplasare++) {
				if (destinatie.x + deplasare + razaAtac == inamic.x) {
					destinatie.x += deplasare;
					inamicInRazaAtac = true;
					break;
				}
			}
			if (!inamicInRazaAtac) {
				destinatie.x += maxDeplasare;
			}
			break;
		case 2:	// spre SUD
			for (int deplasare = 1; deplasare <= maxDeplasare; deplasare++) {
				if (destinatie.y + deplasare + razaAtac == inamic.y) {
					destinatie.y += deplasare;
					inamicInRazaAtac = true;
					break;
				}
			}
			if (!inamicInRazaAtac) {
				destinatie.y += maxDeplasare;
			}
			break;
		case 3:	// spre VEST
			for (int deplasare = 1; deplasare <= maxDeplasare; deplasare++) {
				if (destinatie.x - deplasare - razaAtac == inamic.x) {
					destinatie.x -= deplasare;
					inamicInRazaAtac = true;
					break;
				}
			}
			if (!inamicInRazaAtac) {
				destinatie.x -= maxDeplasare;
			}
			break;
	}
}

void Pistol::Deplaseaza(Pozitie &destinatie) const {
	Pozitie inamicPrincipal;
	int deltaX, deltaY;
	int x, y;
	x = getPosesor()->getPos().x;
	y = getPosesor()->getPos().y;

	inamicPrincipal = getPosesor()->CelMaiApropiatInamic()->getPos();

	// acum trebuie sa ma deplasez spre pozitia inamicului cel mai apropiat
	int diferentaX = inamicPrincipal.x - x;
	int diferentaY = inamicPrincipal.y - y;
	int deplasare = (int)( kIndiceDeplasare * getPosesor()->getRazaVizibilitate() ); // cu cat se deplaseaza agentul
	deltaX = abs(diferentaX);
	deltaY = abs(diferentaY);

	// trebuie sa ne deplasam dupa directia pe care diferenta dintre agenti este mai mare
	if (deltaX >= deltaY) {	// ne deplasam pe orizontala
		if (diferentaX > 0) {	// inamicul se afla in dreapta agentului, ne deplasam spre EST
			CeaMaiApropiataPozitieDeAtac(inamicPrincipal, 1, deplasare, destinatie);
		} else {	// inamicul se alfa in stanga agentului, ne deplasam spre VEST
			CeaMaiApropiataPozitieDeAtac(inamicPrincipal, 3, deplasare, destinatie);
		}
	} else { // ne deplasam pe verticala
		if (diferentaY <= 0) {	// inamicul se afla deasupra agentului, ne deplasam spre NORD
			CeaMaiApropiataPozitieDeAtac(inamicPrincipal, 0, deplasare, destinatie);
		} else {	// inamicul se alfa sub agent, ne deplasam spre SUD
			CeaMaiApropiataPozitieDeAtac(inamicPrincipal, 2, deplasare, destinatie);
		}
	}

	getPosesor()->Deplaseaza(destinatie);
}
