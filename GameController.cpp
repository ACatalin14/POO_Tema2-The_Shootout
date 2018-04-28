#include "GameController.h"
#include <minmax.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

void GameController::InitializeazaSerieAgenti() {
	int numarAgentiTip[kTipuriAgenti] = {0};		// numaram cate obiecte exista din fiecare tip de agenti
	try {
		serieAgenti = new Agent*[nrAgenti];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica FAILED\n";
	}
	for (int i = 0; i < nrAgenti; i++) {
		int tip = rand() % kTipuriAgenti;
		numarAgentiTip[tip]++;
		switch (tip) {					// atribuim tipul agentului
			case 0:
				try {
					serieAgenti[i] = new AgentSecret(numarAgentiTip[0]);
				}
				catch (bad_alloc) {
					cout << "Alocare Dinamica AgentSecret FAILED\n";
				}
				break;
			case 1:
				try {
					serieAgenti[i] = new Ninja(numarAgentiTip[1]);
				}
				catch (bad_alloc) {
					cout << "Alocare Dinamica Ninja FAILED\n";
				}
				break;
			case 2:
				try {
					serieAgenti[i] = new Samurai(numarAgentiTip[2]);
				}
				catch (bad_alloc) {
					cout << "Alocare Dinamica Samurai FAILED\n";
				}
				break;
			default:
				cout << "Nu s-au luat toate cazurile de agenti!\n";
				exit(1);
		}
	}
}

void GameController::PozitioneazaAgenti() {
	for (int i = 0; i < nrAgenti; i++) {
		int x, y;
		bool ocupat;
		do {		// luam o pozitie random si verificam daca este ocupata pana cand gasim una libera
			x = rand() % map.m;
			y = rand() % map.n;
			ocupat = false;
			for (int j = 0; j < i; j++) {
				if (x == serieAgenti[j]->getPos().x && y == serieAgenti[j]->getPos().y) {
					ocupat = true;
				}
			}
		} while (ocupat);
		serieAgenti[i]->setPos(y, x);
		map[y][x] = serieAgenti[i]->getNume()[0];
	}
}

void GameController::AfiseazaSituatieInitiala() {
	cout << "\n";
	for (int i = 1; i <= kIndentMatrice - 6 + map.m; i++) cout << "=";
	cout << " SITUATIA INITIALA ";
	for (int i = 1; i <= kIndentMatrice - 6 + map.m; i++) cout << "=";
	cout << "\n\n";
	for (int i = 0; i < nrAgenti; i++) {
		cout << *serieAgenti[i] << " a primit: [" << serieAgenti[i]->getWeapon()->getNume();
		cout << ", " << serieAgenti[i]->getArmor()->getNume() << "]\n";
	}
}

int* GameController::CreeazaOrdineAgenti() {
	int *ordine;
	try {
		ordine = new int[nrAgenti];					// ordine = 0 1 2 3 4 ... nrAgenti
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica ordine FAILED\n";
	}
	for (int i = 0; i < nrAgenti; i++) {
		ordine[i] = i;
	}
	for (int i = 0; i < nrAgenti - 1; i++) {	// creez o permutare pt ordine
		int j = rand() % (nrAgenti - i) + i;
		swap(ordine[i], ordine[j]);
	}
	return ordine;
}

void GameController::SimuleazaAtac(const Agent* const &jucator, int indexDusman) {
	int* hpSerieAgenti;
	try {
		hpSerieAgenti = new int[nrAgenti];	// vector cu vietile tuturor agentilor
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica hpSerieAgenti FAILED\n";
	}
	for (int i = 0; i < nrAgenti; i++) {
		hpSerieAgenti[i] = serieAgenti[i]->getHp();
	}

	jucator->Ataca(*serieAgenti[indexDusman]);

	for (int i = 0; i < nrAgenti; i++) {	// verific daca cineva a murit dupa atacul jucatorului
		if (!serieAgenti[i]->IsAlive() && hpSerieAgenti[i]) {		// inamicul a murit acum
			cout << *serieAgenti[i] << " a pierdut jocul\n";
			nrAgentiAlive--;
			int x = serieAgenti[i]->getPos().x;
			int y = serieAgenti[i]->getPos().y;
			map[y][x] = '_';
		}
	}

	delete[] hpSerieAgenti;
}

void GameController::SimuleazaDeplasareInteligenta(Agent* const &jucator) {
	Pozitie destinatie;
	// verific scorurile armei si armurii, apoi le compar
	double weaponRanking = (double) jucator->getWeapon()->getDamage() / kHighestDamage;
	double armorRanking = (double) jucator->getArmor()->getAbsorb() / kHighestAbsorb;

	map[jucator->getPos().y][jucator->getPos().x] = '_';

	if (armorRanking < weaponRanking && weaponRanking < 1) {
		// in felul acesta armura poate influenta agentul cum foloseste arma
		// daca armorRanking este mai mic decat weaponRanking, atunci agentul fuge, nu se avanta in lupta;
		jucator->DeplaseazaPentruFuga(destinatie, map.n, map.m);
	} else {
		// (numai daca nu cumva agentul a primit cea mai puternica arma din joc, atunci nu trebuie sa fuga)
		// daca are in schimb o armura cu un ranking mai bun decat al armei, va avea o tactica ofensiva
		jucator->DeplaseazaPentruAtac(destinatie);
	}
	// am vrut sa fac ca un agent care are arma cea mai puternica/armura cea mai mare sigur sa se avante in lupta;
	// in restul cazurilor se va respecta principiul ranking al armelor si armurilor

	map[destinatie.y][destinatie.x] = jucator->getNume()[0];
}

void GameController::SimuleazaDeplasareRandom(Agent* const &jucator) {
	Pozitie* pozitiiValide;
	try {
		pozitiiValide = new Pozitie[4];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica pozitiiValide in SimuleazaDeplasareRandom FAILED\n";
	}
	jucator->CreeazaPozitiiValide(map.n, map.m, pozitiiValide);

	int nrDeplasariValide = 0;	// o deplasare valida inseamna sa isi schimbe pozitia actuala, nu sa ramana pe loc
	int* deplasariValide;	// vector ce contine indecsi (0-3) pt deplasarile valide

	for (int i = 0; i < 4; i++) {
		if (pozitiiValide[i].x != jucator->getPos().x || pozitiiValide[i].y != jucator->getPos().y) {
			nrDeplasariValide++;
		};
	}
	deplasariValide = new int[nrDeplasariValide];
	nrDeplasariValide = 0;
	for (int i = 0; i < 4; i++) {
		if (pozitiiValide[i].x != jucator->getPos().x || pozitiiValide[i].y != jucator->getPos().y) {
			deplasariValide[nrDeplasariValide++] = i;
		};
	}

	int directie = deplasariValide[rand() % nrDeplasariValide];

	map[jucator->getPos().y][jucator->getPos().x] = '_';
	jucator->Deplaseaza(pozitiiValide[directie]);
	map[pozitiiValide[directie].y][pozitiiValide[directie].x] = jucator->getNume()[0];

	delete[] deplasariValide;
}

void GameController::SimuleazaActiuniRunda() {
	int *ordine, i;
	ordine = CreeazaOrdineAgenti();
	for (i = 0; i < nrAgenti; i++) {	// este randul lui serieAgenti[ ordine[i] ] sa actioneze
		int tura = ordine[i];
		if (serieAgenti[tura]->IsAlive()) {		// daca agentul a carui tura este acum, este in viata, simuleaza-l
			serieAgenti[tura]->CreeazaInamiciVizibili(nrAgenti, serieAgenti);

			if (serieAgenti[tura]->getNrInamiciVizibili()) {	// daca exista inamici vizibili, agentul isi analizeaza arma
				int alegere = serieAgenti[tura]->AlegeActiune(nrAgenti, serieAgenti, map.n, map.m);
				if (alegere != -1) {	// daca agentul alege sa atace pe cineva, atunci va ataca agentul respectiv
					SimuleazaAtac(serieAgenti[tura], alegere);
				} else {	// altfel, inseamna ca agentul trebuie sa se deplaseze inteligent,
							// pt ca vede alti agenti dar pe care nu ii poate ataca
					SimuleazaDeplasareInteligenta(serieAgenti[tura]);
				}
			} else {
				// daca nu exista inamici in aria de vizibilitate, agentul se deplaseaza random, pt ca nu vede pe nimeni
				SimuleazaDeplasareRandom(serieAgenti[tura]);
			}
		}
	}
	delete[] ordine;
}

void GameController::InitializeazaJoc() {
	srand(time(0));				// genereaza seed-ul pt functiile rand din program, in functie de timpul ceasului
	map.InitializeazaHarta();
	InitializeazaSerieAgenti();
	PozitioneazaAgenti();
	AfiseazaSituatieInitiala();
}

void GameController::SimuleazaRunde(int nrRunde) {
	for (int i = 0; i < nrRunde && !IsOver(); i++) {
		rundaCurenta++;
		cout << "\n";
		for (int j = 1; j <= kIndentMatrice - 1 + map.m; j++) cout << "=";
		cout << " RUNDA " << rundaCurenta << " ";
		for (int j = 1; j <= kIndentMatrice - 1 + map.m; j++) cout << "=";
		cout << "\n\n";
		SimuleazaActiuniRunda();
		cout << "\n Harta la sfarsitul rundei " << rundaCurenta << ": \n";
		cout << map << "\n";
	}
}

bool GameController::IsOver() const {
	return nrAgentiAlive == 1;
}

void GameController::Ending() const {
	for (int i = 0; i < nrAgenti; i++) {
		if (serieAgenti[i]->IsAlive()) {
			for (int j = 1; j <= kIndentMatrice - 1 + map.m; j++) cout << "=";
			cout << " FINAL ";
			for (int j = 1; j <= kIndentMatrice - 1 + map.m; j++) cout << "=";
			cout << "\n\n\t" << *serieAgenti[i] << " a castigat jocul cu [";
			cout << serieAgenti[i]->getWeapon()->getNume() << ", ";
			cout << serieAgenti[i]->getArmor()->getNume() << "]\n\n";
			for (int j = 1; j <= kIndentMatrice - 5 + map.m; j++) cout << "=";
			cout << " SFARSIT DE JOC ";
			for (int j = 1; j <= kIndentMatrice - 5 + map.m; j++) cout << "=";
			cout << "\n";
			break;
		}
	}
}

const Harta& GameController::getMap() const {
	return map;
}

istream& operator>>(istream &flux, GameController &g) {	// nu ar fi aratat prea bine fara niste cout-uri in corpul functiei
	cout << "Dimensiunile hartii:\n Nr Linii: ";
	flux >> g.map.n;
	cout << " Nr Coloane: ";
	flux >> g.map.m;
	do {
		if ( g.nrAgenti > max(g.map.n, g.map.m) ) {		// se pot introduce cel mult max(n,m) agenti
			cout << "Prea multi agenti!\n";
		}
		cout << "Nr. Agenti: ";
		flux >> g.nrAgenti;
		g.nrAgentiAlive = g.nrAgenti;
	} while( g.nrAgenti > max(g.map.n, g.map.m) );
	return flux;
}
