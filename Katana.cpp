#include "Katana.h"
#include <minmax.h>

Katana::Katana() {
	setNume(kNumeKatana);
	setDamage(kDamageKatana);
}

void Katana::Ataca(Agent &inamic) const {
	cout << *getPosesor() << " il feliaza cu katana pe ";
	int hpInamic = inamic.getHp();
	int atacRezultat = damage - inamic.getArmor()->getAbsorb();
	inamic.setHp(hpInamic - atacRezultat);
	if (inamic.getHp() < 0) {
		inamic.setHp(0);
		atacRezultat = hpInamic;
	}
	cout << inamic << " [-" << atacRezultat << "hp]\n";
}

int Katana::AlegeActiune(int nrInamici, Agent** &inamici, int nrLinii, int nrColoane) {
	int nrInamiciKatana = 0;	// numaram inamicii vizibili agentului care se afla in raza atac a katanei
	int deltaX, deltaY;			// diferenta dintre pozitiile posesorului si inamicului

	for (int i = 0; i < getPosesor()->getNrInamiciVizibili(); i++) {
		deltaX = abs( getPosesor()->getPos().x - getPosesor()->getInamiciVizibili()[i]->getPos().x );
		deltaY = abs( getPosesor()->getPos().y - getPosesor()->getInamiciVizibili()[i]->getPos().y );
		if (deltaX <= razaAtac && deltaY <= razaAtac)  {	// am gasit un agent in raza de atac
			nrInamiciKatana++;
		}
	}

	if (!nrInamiciKatana)	return -1;	// daca nu exista inamici in raza de atac, se deplaseaza

	// are cel putin un agent in raza de atac, deci il va ataca pe cel mai slab
	Agent* inamicSlab = 0;
	int viata, minViata = 999999999;

	// caut agentul cel mai slab din cei aflati in aria de vizibilitate si in aria de atac
	for (int i = 0; i < getPosesor()->getNrInamiciVizibili(); i++) {
		Agent* inamic = getPosesor()->getInamiciVizibili()[i];
		deltaX = abs( getPosesor()->getPos().x - inamic->getPos().x );
		deltaY = abs( getPosesor()->getPos().y - inamic->getPos().y );
		if (deltaX <= razaAtac && deltaY <= razaAtac) {
			viata = inamic->getHp() + inamic->getArmor()->getAbsorb();
			if (viata < minViata) {
				minViata = viata;
				inamicSlab = inamic;
			}
		}
	}

	// acum cautam inamiculSlab in vectorul de inamici dat pt a returna indexul cautat
	for (int i = 0; i < nrInamici; i++) {
		if (inamici[i] == inamicSlab) {
			return i;
		}
	}
}

void Katana::Deplaseaza(Pozitie &destinatie) const {
	Agent* inamic = getPosesor()->CelMaiSlabInamic();
	int x = getPosesor()->getPos().x;
	int y = getPosesor()->getPos().y;
	int xInamic = inamic->getPos().x;
	int yInamic = inamic->getPos().y;
	int diferentaX = xInamic - x;
	int diferentaY = yInamic - y;
	int deltaX = abs(diferentaX);
	int deltaY = abs(diferentaY);
	int deplasare = (int)( kIndiceDeplasare * getPosesor()->getRazaVizibilitate() );

	// vrem sa ne deplasam cat mai aproape de inamic, de aceea ne vom misca pe directiile
	// care au delta CEL MAI MARE; trebuie tratate si cazurile cu aceeasi linie/coloana

	if (deltaX == 0) {	// agentii se afla pe aceeasi coloana, ne deplasam pe verticala
		destinatie.x = x;
		if (diferentaY < 0) {		// inamicul este sus
			destinatie.y = max(y - deplasare, yInamic + 1);
		} else {					// inamicul este jos
			destinatie.y = min(y + deplasare, yInamic - 1);
		}
	} else if (deltaY == 0) {	// agentii se afla pe aceeasi linie
		destinatie.y = y;
		if (diferentaX > 0) {		// inamicul este in dreapta
			destinatie.x = min(x + deplasare, xInamic - 1);
		} else {					// inamicul este in stanga
			destinatie.x = max(x - deplasare, xInamic + 1);
		}
	} else if (deltaX >= deltaY) {	// ne deplasam pe orizontala
		destinatie.y = y;
		if (diferentaX > 0) {		// inamicul este in dreapta
			destinatie.x = min(x + deplasare, xInamic);
		} else {					// inamicul este in stanga
			destinatie.x = max(x - deplasare, xInamic);
		}
	} else {					// ne deplasam pe verticala
		destinatie.x = x;
		if (diferentaY < 0) {		// inamicul este sus
			destinatie.y = max(y - deplasare, yInamic);
		} else {					// inamicul este jos
			destinatie.y = min(y + deplasare, yInamic);
		}
	}

	getPosesor()->Deplaseaza(destinatie);
}
