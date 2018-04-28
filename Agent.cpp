#include "Agent.h"
#include <cstring>
#include <cstdlib>

Agent::Agent() {
	hp = 0;
	razaVizibilitate = 0;
	nume = 0;
	pos.x = pos.y = 0;
	inamiciVizibili = 0;
	nrInamiciVizibili = 0;
	switch (rand() % kTipuriArme) {		// atribuim o arma agentului
		case 0:
			try {
				weapon = new Pistol;
			}
			catch (bad_alloc) {
				cout << "Alocare Dinamica Pistol FAILED\n";
			}
			break;
		case 1:
			try {
				weapon = new Shuriken;
			}
			catch (bad_alloc) {
				cout << "Alocare Dinamica Shuriken FAILED\n";
			}
			break;
		case 2:
			try {
				weapon = new Katana;
			}
			catch (bad_alloc) {
				cout << "Alocare Dinamica Katana FAILED\n";
			}
			break;
		default:
			cout << "Nu s-au luat toate cazurile de arme!\n";
			exit(1);
	}
	weapon->setPosesor(this);

	switch (rand() % kTipuriArmuri) {		// atribuim o armura agentului
		case 0:
			try {
				armor = new VestaAntiglont;
			}
			catch (bad_alloc) {
				cout << "Alocare Dinamica VestaAntiglont FAILED\n";
			}
			break;
		case 1:
			try {
				armor = new Camuflaj;
			}
			catch (bad_alloc) {
				cout << "Alocare Dinamica Camuflaj FAILED\n";
			}
			break;
		case 2:
			try {
				armor = new Kimono;
			}
			catch (bad_alloc) {
				cout << "Alocare Dinamica Kimono FAILED\n";
			}
			break;
		default:
			cout << "Nu s-au luat toate cazurile de armuri!\n";
			exit(1);
	}
	armor->setPosesor(this);
}

Agent::~Agent() {
	delete weapon;
	delete[] nume;
	if (inamiciVizibili) {
		delete[] inamiciVizibili;
	}
}

int Agent::getHp() const {
	return hp;
}

void Agent::setHp(int q) {
	hp = q;
}

int Agent::getRazaVizibilitate() const {
	return razaVizibilitate;
}

void Agent::setRazaVizibilitate(int r) {
	razaVizibilitate = r;
}

char *Agent::getNume() const {
	return nume;
}

void Agent::setNume(const char *s) {
	delete[] nume;
	try {
		nume = new char[strlen(s) + 1];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica Set Nume Agent FAILED\n";
	}
	strcpy(nume, s);
}

const Arma* const Agent::getWeapon() const {
	return weapon;
}

const Armura* const Agent::getArmor() const {
	return armor;
}

Pozitie Agent::getPos() const {
	return pos;
}

void Agent::setPos(int y, int x) {
	pos.y = y;
	pos.x = x;
}

void Agent::setPos(Pozitie p) {
	pos = p;
}

Agent** Agent::getInamiciVizibili() const {
	return inamiciVizibili;
}

void Agent::setInamiciVizibili(int nr, Agent* const* const inamici) {
	delete[] inamiciVizibili;

	setNrInamiciVizibili(nr);
	try {
		inamiciVizibili = new Agent*[nr];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica Inamici Vizibili FAILED\n";
	}
	for (int i = 0; i < nr; i++) {
		inamiciVizibili[i] = inamici[i];
	}
}

int Agent::getNrInamiciVizibili() const {
	return nrInamiciVizibili;
}

void Agent::setNrInamiciVizibili(int nr) {
	nrInamiciVizibili = nr;
}

char* Agent::CreeazaNume(const char *s, int n) const {
	char *s2;	// sirul de returnat

	if (!n) {	// n == 0
		try {
			s2 = new char [strlen(s) + 1];
		}
		catch (bad_alloc) {
			cout << "Alocare Dinamica Creeaza Nume Agent n = 0 FAILED\n";
		}
		strcpy(s2, s);
	} else {	// n != 0
		int n2 = n, dim = 0;	// dim == nr cifre ale lui n
		while (n2) {
			n2 /= 10;
			dim++;
		}
		char* nr;
		try {
			nr = new char[dim + 1];	// cifrele + '\0'
		}
		catch (bad_alloc) {
			cout << "Alocare Dinamica Creeaza Nume Agent cifre nr FAILED\n";
		}
		itoa(n, nr, 10);
		try {
			s2 = new char [strlen(s) + strlen(nr) + 1];
		}
		catch (bad_alloc) {
			cout << "Alocare Dinamica Creeaza Nume Agent n != 0 FAILED\n";
		}
		strcpy(s2, s);
		strcat(s2, nr);
		delete[] nr;
	}

	return s2;
}

void Agent::Ataca(Agent &inamic) const {	// in functie de tipul armei agentul ataca diferit
	weapon->Ataca(inamic);
}

void Agent::Deplaseaza(int y, int x) {
	cout << *this << " se deplaseaza la pozitia ";
	pos.y = y;
	pos.x = x;
	cout << "[" << pos.y + 1 << "," << pos.x + 1 << "]\n";
}

void Agent::Deplaseaza(Pozitie p) {
	cout << *this << " se deplaseaza la pozitia ";
	pos = p;
	cout << "[" << pos.y + 1 << "," << pos.x + 1 << "]\n";
}

bool Agent::IsAlive() const {
	return hp > 0;
}

int Agent::AlegeActiune(int nrInamici, Agent**&inamici, int nrLinii, int nrColoane) {
	return weapon->AlegeActiune(nrInamici, inamici, nrLinii, nrColoane);
}

void Agent::CreeazaInamiciVizibili(int nrInamici, Agent* const* const &inamici) {
	int auxNrInamiciVizibili = 0;				// numaram inamicii vizibli care sunt in viata

	for (int i = 0; i < nrInamici; i++) {
		if (inamici[i]->IsAlive() && inamici[i] != this) {
			int deltaX = abs( this->pos.x - inamici[i]->pos.x );
			int deltaY = abs( this->pos.y - inamici[i]->pos.y );
			if (deltaX <= this->razaVizibilitate && deltaY <= this->razaVizibilitate)  {
				auxNrInamiciVizibili++;
			}
		}
	}

	if (!auxNrInamiciVizibili) {
		setInamiciVizibili(0, 0);
		return;
	}

	// daca exista inamici vizibli ii punem in vectorul de pointeri auxInamiciVizibili
	// ca apoi sa il copiez in vectorul inamiciVizibili din clasa
	Agent** auxInamiciVizibili;
	try {
		auxInamiciVizibili = new Agent*[auxNrInamiciVizibili];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica auxInamiciVizibili FAILED\n";
	}

	auxNrInamiciVizibili = 0;
	for (int i = 0; i < nrInamici; i++) {
		if (inamici[i]->IsAlive() && inamici[i] != this) {
			int deltaX = abs( this->pos.x - inamici[i]->pos.x );
			int deltaY = abs( this->pos.y - inamici[i]->pos.y );
			if (deltaX <= this->razaVizibilitate && deltaY <= this->razaVizibilitate)  {
				auxInamiciVizibili[auxNrInamiciVizibili++] = inamici[i];
			}
		}
	}

	setInamiciVizibili(auxNrInamiciVizibili, auxInamiciVizibili);

	delete[] auxInamiciVizibili;
}

void Agent::NormalizeazaPozitieValida(Pozitie &p, int dir, int frontieraNord, int frontieraEst, int frontieraSud,
									  int frontieraVest) const {
	bool outOfBounds;	// true cand pozitia aleasa este in afara hartii
	bool casutaOcupata;	// true cand pozitia aleasa este deja rezervata altui agent

	do {	// cat timp pozitia aleasa nu e buna, ma retrag inapoi cu o casuta
		outOfBounds = casutaOcupata = false;

		switch (dir) {	// verific daca este outOfBounds
			case 0:
				if (p.y < frontieraNord) {
					outOfBounds = true;
				}
				break;
			case 1:
				if (p.x > frontieraEst) {
					outOfBounds = true;
				}
				break;
			case 2:
				if (p.y > frontieraSud) {
					outOfBounds = true;
				}
				break;
			case 3:
				if (p.x < frontieraVest) {
					outOfBounds = true;
				}
				break;
		}

		for (int i = 0; i < nrInamiciVizibili; i++) {
			if (inamiciVizibili[i]->pos.x == p.x &&
				inamiciVizibili[i]->pos.y == p.y) {
				casutaOcupata = true;
				break;	// nu mai verific restul agentilor
			}
		}

		if (outOfBounds || casutaOcupata) {
			switch (dir) {
				case 0:
					p.y++;
					break;
				case 1:
					p.x--;
					break;
				case 2:
					p.y--;
					break;
				case 3:
					p.x++;
					break;
			}
		}
	} while(outOfBounds || casutaOcupata);
}

void Agent::CreeazaPozitiiValide(int frontieraSud, int frontieraEst, Pozitie* pozitiiValide) const {
	Pozitie pozitieAleasa;
	// NORD
	// calculez pozitia din nord daca agentul s-ar deplasa cu pasul sau obisnuit spre nord
	pozitieAleasa.x = pos.x;
	pozitieAleasa.y = pos.y - (int)(kIndiceDeplasare * razaVizibilitate);
	NormalizeazaPozitieValida(pozitieAleasa, 0, 0, frontieraEst - 1, frontieraSud - 1, 0);
	pozitiiValide[0] = pozitieAleasa;

	// EST
	pozitieAleasa.x = pos.x + (int)(kIndiceDeplasare * razaVizibilitate);
	pozitieAleasa.y = pos.y;
	NormalizeazaPozitieValida(pozitieAleasa, 1, 0, frontieraEst - 1, frontieraSud - 1, 0);
	pozitiiValide[1] = pozitieAleasa;

	// SUD
	pozitieAleasa.x = pos.x;
	pozitieAleasa.y = pos.y + (int)(kIndiceDeplasare * razaVizibilitate);
	NormalizeazaPozitieValida(pozitieAleasa, 2, 0, frontieraEst - 1, frontieraSud - 1, 0);
	pozitiiValide[2] = pozitieAleasa;

	// VEST
	pozitieAleasa.x = pos.x - (int)(kIndiceDeplasare * razaVizibilitate);
	pozitieAleasa.y = pos.y;
	NormalizeazaPozitieValida(pozitieAleasa, 3, 0, frontieraEst - 1, frontieraSud - 1, 0);
	pozitiiValide[3] = pozitieAleasa;
}

void Agent::DeplaseazaPentruAtac(Pozitie &destinatie) {
	weapon->Deplaseaza(destinatie);
}

void Agent::DeplaseazaPentruFuga(Pozitie &destinatie, int frontieraSud, int frontieraEst) {
	Pozitie* pozitiiValide;
	try {
		pozitiiValide = new Pozitie[4];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica pozitiiValide in Agent::DeplaseazaPentruFuga() FAILED\n";
	}
	CreeazaPozitiiValide(frontieraSud, frontieraEst, pozitiiValide);

	int nrDeplasariValide = 0;	// o deplasare valida inseamna sa isi schimbe pozitia actuala, nu sa ramana pe loc
	int* deplasariValide;	// vector ce contine indecsi (0-3) pt deplasarile valide

	for (int i = 0; i < 4; i++) {
		if (pozitiiValide[i].x != pos.x || pozitiiValide[i].y != pos.y) {
			nrDeplasariValide++;
		};
	}
	try {
		deplasariValide = new int[nrDeplasariValide];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica deplasariValide in Agent::DeplaseazaPentruFuga() FAILED\n";
	}
	nrDeplasariValide = 0;
	for (int i = 0; i < 4; i++) {
		if (pozitiiValide[i].x != pos.x || pozitiiValide[i].y != pos.y) {
			deplasariValide[nrDeplasariValide++] = i;
		};
	}

	int* scorDeplasariValide;
	try {
		scorDeplasariValide = new int[nrDeplasariValide]();
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica scorDeplasariValide in Agent::DeplaseazaPentruFuga() FAILED\n";
	}
	// fiecare din cele cel mult 4 pozitii va avea cate un scor, pe baza caruia agentul va alege incotro se deplaseaza

	for (int i = 0; i < getNrInamiciVizibili(); i++) {	// luam fiecare inamic
		for (int j = 0; j < nrDeplasariValide; j++) {	// si pt fiecare pozitie ferita de inamic, dam un punct pozitiei respective
			int x = pozitiiValide[ deplasariValide[j] ].x;
			int y = pozitiiValide[ deplasariValide[j] ].y;
			int xInamic = getInamiciVizibili()[i]->getPos().x;
			int yInamic = getInamiciVizibili()[i]->getPos().y;
			int raza = getInamiciVizibili()[i]->getRazaVizibilitate();

			if ( !( x >= xInamic - raza && x <= xInamic + raza && y >= yInamic - raza && y <= yInamic + raza ) ) {
				// daca pozitia nu apartine ariei de viziblitate a inamicului, crestem scorul pozitiei
				scorDeplasariValide[ deplasariValide[j] ]++;
			}
		}
	}

	// acum ca avem scorurile ramane sa alegem deplasarea cu cel mai mare scor
	int maxScor = scorDeplasariValide[0];
	int deplasareDecisa = 0;
	for (int i = 1; i < 4; i++) {
		if (scorDeplasariValide[i] > maxScor) {
			maxScor = scorDeplasariValide[i];
			deplasareDecisa = i;
		}
	}

	destinatie = pozitiiValide[deplasareDecisa];
	Deplaseaza(destinatie);

	delete[] scorDeplasariValide;
}

Agent* Agent::CelMaiApropiatInamic() const {
	Agent* inamic;					// cel mai apropiat inamic
	int deltaX, deltaY, distanta;
	int minDist;					// distanta MANHATTAN (pe componente) cea mai mica fata de un agent
	int x, y, xInamic, yInamic;		// coordonatele agentului si unui inamic
	x = pos.x;
	y = pos.y;

	if (!nrInamiciVizibili) return 0;

	// in aria de vizibilitate a agentului exista macar un alt agent
	inamic = inamiciVizibili[0];
	deltaX = abs(x - inamic->pos.x);
	deltaY = abs(y - inamic->pos.y);
	minDist = deltaX + deltaY;

	// calculez cel mai apropiat agent dintre toti cei vizibili
	for (int i = 1; i < nrInamiciVizibili; i++) {
		xInamic = inamiciVizibili[i]->pos.x;
		yInamic = inamiciVizibili[i]->pos.y;
		deltaX = abs(x - xInamic);
		deltaY = abs(y - yInamic);
		distanta = deltaX + deltaY;
		if (distanta < minDist) {
			minDist = distanta;
			inamic = inamiciVizibili[i];
		}
	}

	return inamic;
}

Agent* Agent::CelMaiSlabInamic() const {
	Agent* inamic;			// cel mai slab inamic
	int minViata, viata;	// viata = hp + armor
	int deltaX, deltaY, xInamic, yInamic;
	int minDist, distanta;	// distante MANHATTAN (pe componente)
	int x = pos.x;
	int y = pos.y;

	if (!nrInamiciVizibili) return 0;

	// in aria de vizibilitate a agentului exista macar un alt agent
	inamic = inamiciVizibili[0];
	minViata = inamic->hp + inamic->getArmor()->getAbsorb();
	deltaX = abs(x - inamic->pos.x);
	deltaY = abs(y - inamic->pos.y);
	minDist = deltaX + deltaY;

	// calculam cel mai slab si apropiat inamic dintre toti cei vizibili
	for (int i = 1; i < nrInamiciVizibili; i++) {
		viata = inamiciVizibili[i]->hp + inamiciVizibili[i]->getArmor()->getAbsorb();
		xInamic = inamiciVizibili[i]->pos.x;
		yInamic = inamiciVizibili[i]->pos.y;
		deltaX = abs(x - xInamic);
		deltaY = abs(y - yInamic);
		distanta = deltaX + deltaY;

		if (viata < minViata) {
			minViata = viata;
			inamic = inamiciVizibili[i];
			minDist = distanta;
		} else if (viata == minViata) {	// dintre 2 agenti la fel de slabi, il alegem pe cel care e mai aproape
			if (distanta < minDist) {
				inamic = inamiciVizibili[i];
				minDist = distanta;
			}
		}
	}

	return inamic;
}

ostream& operator<<(ostream& flux, const Agent& a) {
	flux << "[" << a.pos.y + 1 << "," << a.pos.x + 1 << "]:" << a.nume << "(" << a.hp << ")";

	// 		Ninja8(200):[14,8] foloseste shuriken asupra lui AgentSecret4(100):[7,5]
	//		(200)Ninja8:[14,8] foloseste shuriken asupra lui (100)AgentSecret4:[7,5]
	//		[14,8]:Ninja8(200) foloseste shuriken asupra lui [7,5]:AgentSecret4(100)	<-----

	return flux;
}


